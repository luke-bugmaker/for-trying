"""
Simple CLI Slot Machine
------------------------
Run with: python slot_machine.py
"""

import random
import time
import sys

# ----------------------------
# Configuration
# ----------------------------

# Each symbol has:
#   weight   -> how likely it is to appear (higher = more common)
#   payout   -> multiplier applied to the bet if you get 3 of this symbol
SYMBOLS = {
    "🍒": {"weight": 30, "payout": 3},
    "🍋": {"weight": 25, "payout": 4},
    "🔔": {"weight": 20, "payout": 6},
    "💎": {"weight": 15, "payout": 10},
    "7️⃣": {"weight": 5,  "payout": 25},
}

TWO_MATCH_PAYOUT = 1.5   # multiplier if exactly 2 reels match
NUM_REELS = 3
STARTING_CREDITS = 100
SPIN_DELAY = 0.25         # seconds between reel reveals, for a bit of drama


# ----------------------------
# Core mechanics
# ----------------------------

def weighted_symbol():
    """Pick one symbol according to its weight."""
    names = list(SYMBOLS.keys())
    weights = [SYMBOLS[s]["weight"] for s in names]
    return random.choices(names, weights=weights, k=1)[0]


def spin_reels():
    return [weighted_symbol() for _ in range(NUM_REELS)]


def evaluate_spin(reels, bet):
    """
    Returns (winnings, message)
    winnings is the amount to ADD to the balance (0 if lost the bet already
    accounted for outside this function).
    """
    counts = {}
    for s in reels:
        counts[s] = counts.get(s, 0) + 1

    # All three match
    for symbol, count in counts.items():
        if count == NUM_REELS:
            payout = SYMBOLS[symbol]["payout"]
            winnings = bet * payout
            return winnings, f"JACKPOT! Three {symbol} — you win {winnings}!"

    # Exactly two match
    for symbol, count in counts.items():
        if count == 2:
            winnings = int(bet * TWO_MATCH_PAYOUT)
            return winnings, f"Two {symbol} — small win, +{winnings}."

    # No match
    return 0, "No match — better luck next spin."


def print_reels(reels):
    row = " | ".join(reels)
    print(f"\n[ {row} ]\n")


def print_paytable():
    print("=" * 40)
    print("PAYTABLE (3 of a kind pays bet x multiplier)")
    for symbol, info in sorted(SYMBOLS.items(), key=lambda kv: kv[1]["payout"]):
        print(f"  {symbol}  x3  ->  bet x{info['payout']}")
    print(f"  any pair (2 matching) -> bet x{TWO_MATCH_PAYOUT}")
    print("=" * 40)


# ----------------------------
# Game loop
# ----------------------------

def get_bet(balance):
    while True:
        raw = input(f"Your balance: {balance}. Enter bet amount (or 'q' to quit): ").strip()
        if raw.lower() in ("q", "quit", "exit"):
            return None
        if not raw.isdigit():
            print("Please enter a whole number, or 'q' to quit.")
            continue
        bet = int(raw)
        if bet <= 0:
            print("Bet must be greater than 0.")
        elif bet > balance:
            print("You can't bet more than your current balance.")
        else:
            return bet


def play():
    print("\n🎰  WELCOME TO THE SLOT MACHINE  🎰\n")
    print_paytable()

    balance = STARTING_CREDITS
    total_spins = 0
    total_wagered = 0
    total_won = 0

    while True:
        if balance <= 0:
            print("\nYou're out of credits. Game over!")
            break

        bet = get_bet(balance)
        if bet is None:
            break

        balance -= bet
        total_wagered += bet
        total_spins += 1

        print("Spinning", end="", flush=True)
        for _ in range(3):
            time.sleep(SPIN_DELAY)
            print(".", end="", flush=True)
        print()

        reels = spin_reels()
        print_reels(reels)

        winnings, message = evaluate_spin(reels, bet)
        balance += winnings
        total_won += winnings
        print(message)

    print("\n" + "=" * 40)
    print("SESSION SUMMARY")
    print(f"  Spins played:   {total_spins}")
    print(f"  Total wagered:  {total_wagered}")
    print(f"  Total won:      {total_won}")
    print(f"  Net:            {total_won - total_wagered}")
    print(f"  Final balance:  {balance}")
    print("=" * 40)
    print("Thanks for playing!\n")


if __name__ == "__main__":
    try:
        play()
    except KeyboardInterrupt:
        print("\n\nInterrupted. Cashing out early — thanks for playing!")
        sys.exit(0)
