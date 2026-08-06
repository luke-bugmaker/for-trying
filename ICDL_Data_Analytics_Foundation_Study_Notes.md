# ICDL Data Analytics – Foundation: Study Notes

*Detailed study notes covering all 13 lessons (pages 1-227) of the ICDL Data Analytics - Foundation course book, written as condensed original study material rather than a reproduction of the source text. Where a section is a long click-by-click software walkthrough, the general workflow is explained and the exact page range in the book is given for the precise sequence of clicks.*

---

## Lesson 1 – Key Concepts (Book pages 1-14)

### 1.1 Types of Data Analytics

Modern organisations collect huge volumes of data from an ever-growing range of sources: mobile devices and apps, online platforms, point-of-sale and payment systems, security cameras, GPS trackers, wireless/IoT sensors, and older "legacy" systems. This data arrives in many formats and from many streams, and the value comes from combining it to find patterns that help meet organisational goals.

Data analytics activities fall into two broad categories:
- **Quantitative analytics** – deals with numeric, measurable data (prices, counts, durations). It uses structured techniques such as surveys, business reports, and statistical methods, and gives objective, generalisable insights.
- **Qualitative analytics** – deals with non-numeric data such as attitudes, opinions and behaviours, gathered through interviews, focus groups, or open-text survey responses. It gives rich, subjective insight but is harder to generalise from.

Within quantitative/qualitative work, four specific types of analytics are used, of increasing sophistication and value:
1. **Descriptive analytics** – answers "what happened in the past?" Uses simple descriptive statistics (mean, median, sums, percentages) on historical data. Lowest complexity, but foundational – you typically need descriptive analytics before you can do the other three.
2. **Diagnostic analytics** – answers "why did it happen?" Takes a deeper look using drill-down, data discovery and correlation techniques to identify root causes and contributing factors.
3. **Predictive analytics** – answers "what is likely to happen next?" Uses findings from descriptive/diagnostic analytics plus statistical or machine-learning models to forecast future outcomes; accuracy depends on the quality of the underlying data.
4. **Prescriptive analytics** – answers "what is the best action to take?" The most advanced and least common type; combines historical and real-time data with business rules, optimisation and simulation to recommend concrete actions (e.g. optimising delivery routes or stock levels).

The book illustrates this with a retail case example (a fashion retailer's use of point-of-sale, RFID, and social-media data to predict demand and manage stock) and asks the reader to classify specific activities (e.g. "compiling and analysing social media mentions" = descriptive; "generating a stock reorder prediction" = predictive).

### 1.2 Business Benefits

Knowing how to interpret data gives businesses four main categories of benefit:
1. **Identifying patterns and trends** – spotting recurring behaviours in large data sets that would be invisible by eye (e.g. loyalty-card purchase patterns, seasonal demand).
2. **Improving efficiency** – e.g. a hotel chain analysing historical occupancy to right-size staffing, or a factory using output data to reduce waste.
3. **Supporting better decision-making** – giving managers access to large volumes of analysed data so choices are based on evidence rather than guesswork (e.g. an HR team forecasting the effect of a new policy before rolling it out).
4. **Presenting information effectively** – using dashboards, charts and tables so that decision-makers can absorb information quickly and act on it.

The book also notes two "newer" business-model benefits: organisations that give away a free service in exchange for user data can monetise that data (e.g. through targeted advertising), and predictive financial analytics can be used to assess loan/credit risk.

### 1.3 Data Analysis Process

Data analysis is best thought of as a repeatable six-phase process rather than a single task:
1. **Business Understanding** – define the business goals, what "success" looks like, and produce a project plan.
2. **Data Understanding** – collect and become familiar with the data, checking its quality.
3. **Data Preparation** – select, clean and transform the raw data into a state ready for modelling (this and Data Understanding are the two phases this Foundation course concentrates on, using Excel and Power BI).
4. **Modelling** – select and apply appropriate analytical/statistical techniques.
5. **Evaluation** – assess whether the results actually meet the original business goals.
6. **Deployment** – roll the results out into the business (reporting, monitoring, and acting on them).

These six phases are cyclical – insights from Evaluation and Deployment often feed back into a refined Business Understanding for the next round of analysis.

### 1.4 Data Protection Considerations

Whenever an analysis involves personal data (any data that identifies a living individual), data protection law applies – the book uses the EU/UK **General Data Protection Regulation (GDPR)**, in force since 25 May 2018, as its example, but notes that regulations vary by jurisdiction and organisations must comply with the law(s) relevant to where they operate.

Core data protection principles to keep in mind during analysis:
- Data must be processed lawfully, fairly, and transparently.
- It must be collected only for specified, explicit purposes.
- It must be adequate, relevant, and limited to what is necessary (data minimisation).
- It must be accurate and kept up to date.
- It must not be kept longer than necessary.
- It must be stored securely.

A common practical technique is **anonymising personal data** – removing direct identifiers (names, exact addresses, dates of birth) or replacing them with less specific values (e.g. age band instead of date of birth) so that individuals can no longer be identified, which reduces compliance risk while still allowing useful analysis.

### 1.5 Review Exercise
Self-test quiz on analytics types, benefits, process phases and data protection (book page 14).

---
## Lesson 2 – Statistical Analysis (Book pages 15-32)

### 2.1 Summary Statistics Introduction

To make sense of large quantitative data sets, you summarise them using statistical techniques rather than trying to read every raw value. There are two families of summary statistic:
- **Measures of central tendency** – describe a "typical"/central value of the data set (mean, median, mode).
- **Measures of variation** – describe how spread out or dispersed the data is around that central value (range, variance, quartiles).

Neither family alone gives the full picture – two data sets can have the same mean but very different spreads, so a good statistical summary should always combine a central-tendency measure with a variation measure.

### 2.2 Measures of Central Tendency

- **Mean** (the arithmetic average): sum of all values divided by the count of values. It uses every value in the calculation, so it is sensitive to outliers – a handful of unusually large or small values can pull the mean away from what "most" data points look like. The book's shoe-size case example asks whether an average shoe-size increase is meaningful or is being skewed by a few outlier measurements.
- **Median**: the middle value once the data is sorted in ascending order. If there is an even number of values, it's the average of the two middle values. Because it only depends on position, not magnitude, the median is far less affected by outliers than the mean, and is often more representative when a data set is skewed (e.g. response times with a few very slow outliers).
- **Mode**: the value that occurs most frequently. It is the only central-tendency measure that works well for purely categorical data (e.g. the most common customer satisfaction rating) and a data set can have no mode, one mode, or several modes (bimodal/multimodal).

Choosing which measure to use depends on the data and the question being asked – e.g. mean gross profit across stores vs. median service response time when a few slow outliers would distort the mean.

### 2.3 Calculating Central Tendency (in Excel)

Excel provides built-in worksheet functions for each measure:
- **AVERAGE(number1, [number2], ...)** – calculates the mean.
- **MEDIAN(number1, [number2], ...)** – calculates the median (no need to manually sort the range first – Excel does this internally).
- **MODE(number1, [number2], ...)** – calculates the (first) mode.

Arguments can be individual numbers or, more commonly, cell/range references. The worked example in the book applies these three functions to a table of order amounts to produce a small "Central Tendency Measures" summary block. Full click-by-click steps are on book pages 22-23.

### 2.4 Measures of Variation

- **Range** = Maximum value − Minimum value. The simplest variation measure, but extremely sensitive to outliers since it only looks at the two extreme values.
- **Variance** – technically, the average of the squared differences between each value and the mean. A larger variance means the individual values are, on average, further from the mean (less consistent); a smaller variance means the values cluster tightly around the mean. The book demonstrates this by comparing three sales representatives with the same mean contract volume (6) but very different variances, showing that low variance = more consistent performance, even though the average looks identical.
- **Quartiles** – divide the ordered data into four equal-sized groups: Q1 (25th percentile / median of the lower half), Q2 (50th percentile, i.e. the median itself), and Q3 (75th percentile / median of the upper half). Quartiles are useful for understanding distribution shape and for spotting how values cluster (e.g. analysing online order-quantity distributions).

### 2.5 Calculating Variation (in Excel)

- **MAX(number1, [number2], ...)** and **MIN(...)** – find the largest/smallest values; Range is then calculated as MAX − MIN.
- **VAR.P(number1, [number2], ...)** – calculates variance for an entire population data set (there is a related VAR.S for a sample).
- **QUARTILE(array, quart)** – returns a chosen quartile from a range, where the "quart" argument is 0 (minimum), 1 (Q1), 2 (median/Q2), 3 (Q3), or 4 (maximum).

The book's worked example builds a small "Variation Measures" summary table (Range, Mean, Variance, Q1-Q3) from an order-amount data set. Full click-by-click steps are on book pages 30-31.

### 2.6 Review Exercise
Practical exercise calculating mean, median, mode, range and quartiles on a credit-card transaction data set (book page 32).

---
## Lesson 3 – Importing Data Sets (Book pages 33-54)

### 3.1 Importing Data Sets Introduction

Before you can analyse a data set in a spreadsheet application, it usually needs to be brought in from somewhere else. Common sources are: plain text files, other spreadsheets, web page tables, and database tables. When importing, you can create either a **static** copy (a one-off snapshot, unaffected by later changes at the source) or a **connected** import (which keeps a live link to the source so the data can be refreshed later to pick up changes). Choosing which to use depends on whether you need the data to stay current.

### 3.2 Importing Data from Text Files

Text files exported from other systems typically come in one of two flavours:
- **CSV (comma-separated values)** – one row of data per line of text, with commas separating each column/field; commas inside a field are usually escaped by surrounding the field in quotes.
- **Delimited text** – similar, but using a different separator character such as a tab, semicolon, or fixed column widths.

In Excel, a text file can be imported permanently (Data tab → Get External Data/Get & Transform → From Text/CSV) which lets you keep the connection live, or opened directly as a one-off file (which makes it static). The **Text Import Wizard** (older Excel) walks through 3 steps: choosing delimited vs fixed width, choosing the delimiter character(s) (e.g. comma), and setting per-column data formats (e.g. marking a phone-number column as text so leading zeros aren't lost, or specifying a date format). Newer Excel/Office 365 versions use a simpler preview-and-load dialog instead. Full click-by-click steps for both versions are on book pages 35-39.

### 3.3 Importing Data from Spreadsheets

You can pull data from one workbook into another while keeping a dynamic (refreshable) connection between them – useful when the source workbook is updated regularly (e.g. a shared "Ticket Sales" workbook). The general workflow: Data tab → Get External Data/Get Data → From File/Existing Connections → browse to and select the source workbook → use the Navigator/Select Table dialog to pick the specific worksheet or named table to import → choose where to place the imported data (existing or new worksheet) → the data is loaded in table format and can later be refreshed with a right-click → Refresh. Full click-by-click steps (covering both the classic and Office 365 versions of this feature) are on book pages 41-43.

### 3.4 Importing Data from Website Tables

Excel's **Web Query / "From Web"** feature scans a web page for HTML tables and lets you choose which one(s) to import (e.g. a currency exchange-rate table). You provide the page's URL, Excel loads a preview of the page, you click the small arrow icon next to the table you want, and then Import. As with other imports, the connection can be a live one that is refreshed later, though web tables often need extra clean-up since web formatting doesn't translate perfectly into spreadsheet formatting. Full click-by-click steps (classic and newer Excel) are on book pages 45-49.

### 3.5 Importing Data from Database Tables

Excel can also connect directly to a database management system (DBMS) such as Microsoft Access, which is useful when large, well-structured data sets are kept in database tables rather than files. Workflow: Data tab → Get External Data → From Database/From Access → browse to and select the database file → the Navigator dialog lists all tables in that database → select the required table(s) → Import → choose placement (existing worksheet, starting cell) → OK. As always, the link can later be refreshed. Full click-by-click steps are on book pages 50-53.

### 3.6 Review Exercise
Practical exercise importing a comma-delimited "Real Estate" CSV file with headers, selectively skipping columns, and saving the result (book page 54).

---
## Lesson 4 – Shaping Data Sets (Book pages 55-70)

### 4.1 Shaping Data Sets Introduction

Imported/raw data is rarely analysis-ready. "Shaping" (also called cleaning/preparing) a data set typically involves: fixing spelling mistakes, removing duplicate records, finding and replacing incorrect values, fixing inconsistent formatting, removing extra/trailing spaces, correcting number/date/time formats, merging or splitting columns, rearranging column order, and reconciling data by cross-checking against another source. It's best practice to keep a backup copy of the original data before cleaning, since cleaning steps like removing duplicates are destructive. Spreadsheet applications include built-in tools for some of this (Spell Checker, Find & Replace, Remove Duplicates); other tasks (like extracting parts of text) require formulas.

### 4.2 Removing Duplicate Data

Duplicate records happen when the same record is entered/merged into a data set more than once. Excel's built-in **Remove Duplicates** tool (Data tab → Data Tools → Remove Duplicates) scans a selected range, lets you choose which columns must all match for a row to count as a duplicate, and permanently deletes the extra copies, keeping only the first occurrence – so it's important to copy the original data to a new location first if you might need it again. After running it, Excel reports how many duplicate values were found/removed and how many unique rows remain. Steps on pages 57-58.

### 4.3 Validating Data Using VLOOKUP

**VLOOKUP(lookup_value, table_array, col_index_num, [range_lookup])** searches for a value in the first column of a reference table and returns a value from a specified column of the matching row:
- **lookup_value** – the value you want to look up.
- **table_array** – the range containing the reference data (lookup column first).
- **col_index_num** – which column (counting from 1 = the first column of table_array) to return.
- **range_lookup** – FALSE for an exact match (most common use case, e.g. validating codes), TRUE/omitted for an approximate match (useful for looking up which "band" a value falls into, e.g. a commission-rate table).

A common use in data validation is cross-checking that values in your working data set (e.g. country codes) actually exist in a trusted reference list – if the code isn't found, VLOOKUP returns a #N/A error, immediately flagging the bad row. Cell references to the reference table are typically made absolute (with $ signs) so the formula can be copied down without the reference range shifting. Full worked example and steps on pages 60-62.

### 4.4 Validating Data Using IF Functions

**IF(logical_test, [value_if_true], [value_if_false])** evaluates a condition and returns one value if it's TRUE and another if it's FALSE – e.g. checking whether a sales value falls inside an allowed minimum/maximum range and returning "Error" if not. Both the true and false results are optional, and either can itself be another formula.

For more complex validation, IF can be combined with **AND()** or **OR()** as the logical test (e.g. "is this value greater than the minimum AND less than the maximum?"), or several IF functions can be **nested** inside one another to test more than two possible outcomes/conditions in a single formula. Full worked example (validating that sales figures for each location fall within a minimum/maximum range, including a nested-IF alternative) is on pages 64-65.

### 4.5 Extracting Values Using Text Functions

Text (string) functions let you pull specific parts out of a combined text field, which is a common cleaning task after importing data where multiple pieces of information have been concatenated into one column:
- **LEFT(text, [num_chars])** – returns a given number of characters from the start (left side) of a string.
- **RIGHT(text, [num_chars])** – returns characters from the end (right side).
- **MID(text, start_num, num_chars)** – returns characters from the middle, starting at a specified position.
- **LEN(text)** – returns the number of characters in a string (often used inside other functions to calculate how many characters to extract, e.g. "everything except the last 2 characters" = LEFT combined with LEN(text)-2).
- **FIND(find_text, within_text, [start_num])** – returns the numeric position of one piece of text within another (useful for locating a delimiter character such as an underscore, so that LEFT/MID/RIGHT know exactly where to cut).

These functions are frequently nested together — e.g. LEFT combined with LEN to strip a fixed suffix, or RIGHT combined with FIND to pull everything after a delimiter regardless of its position. The book's worked example splits an "imported country" field into a clean country name column and a separate country-code column. Full steps on pages 66-68.

### 4.6 Review Exercise
Practical exercise combining duplicate removal, LEN-based text extraction, an IF-based value check, and a VLOOKUP-based commission rate lookup on a shipping data set (book pages 68-69).

---
## Lesson 5 – Filtering Data Sets (Book pages 71-78)

### 5.1 Formatting Data Sets as Tables

Converting a plain range of cells into a proper Excel **Table** (Home tab → Styles group → Format as Table, then confirm the data range and that it has headers) unlocks extra functionality: automatic header-row filter buttons, banded row shading for readability, easy-to-apply table styles, and a foundation for pivot tables and slicers. Before formatting, the data should already be organised with one heading row, one data type per column, and no fully blank rows/columns. Table Style Options (in the Design tab) let you toggle Header Row, Total Row (adds SUM/AVERAGE/COUNT/MIN/MAX subtotal row), Banded Rows/Columns, First/Last Column highlighting, and the Filter Button. Full steps on pages 72-74.

### 5.2 Using Table Slicers

A **slicer** is a floating panel of clickable buttons – one per unique value in a chosen column – that visually filters a table with a single click, making the current filter state obvious at a glance (unlike the small dropdown arrows in header filters). To add one: click any cell in the table → Table Tools/Design → Tools group → Insert Slicer → tick the field(s) you want a slicer for → OK. Multiple slicers can be positioned and resized independently, and multiple items can be selected within one slicer using Ctrl-click (or Shift-click for a contiguous range). A red "Clear Filter" icon on the slicer resets it. Full steps on pages 75-77.

### 5.3 Review Exercise
Practical exercise formatting a regional sales range as a table, adding and repositioning slicers, and filtering by multiple criteria at once (book page 78).

---

## Lesson 6 – Pivot Table Data Aggregation (Book pages 79-96)

### 6.1 Summarising Data Introduction

A **pivot table** is Excel's tool for quickly summarising and cross-tabulating large data sets to answer analytical questions (e.g. "which store sold the most?", "what were this quarter's average order sizes by region?") without writing manual formulas. It automatically aggregates the underlying rows into a compact summary that can be reorganised interactively.

### 6.2 Changing Aggregation Methods

A pivot table applies an **aggregation (summary) function** to each value field – Sum is the default for numeric fields, Count for text fields. You can change this via right-click on a value → Summarize Values By, or via the Value Field Settings dialog (Analyze tab → Active Field → Field Settings), where the available aggregation methods include Sum, Count, Average, Max, and Min. The Value Field Settings dialog also lets you rename the field (Custom Name) and apply number formatting (e.g. currency with 0 decimal places). Because Excel auto-generates a field name like "Sum of Amount" or "Average of Amount" based on the chosen aggregation, it's good practice to give it a clearer custom name. Steps on pages 81-83.

### 6.3 Displaying Multiple Aggregation Values

The same underlying field can be dragged into the Values area of the pivot table more than once, with a different aggregation method applied to each copy – for example showing Sum, Count, Max, and Min of the same "Amount" column side-by-side in one pivot table, each given a distinct custom name (e.g. "Total", "Transactions", "Highest", "Lowest") so the report clearly shows several angles on the same data at once. Steps on pages 84-86.

### 6.4 Using Built-In Calculations

Beyond basic aggregation, the **"Show Values As"** option (in Value Field Settings, or via right-click → Show Values As) applies a further calculation on top of the aggregated values:
- **% of Grand Total** – each value as a percentage of the overall total.
- **% of Column Total / % of Row Total** – each value as a percentage of its column's or row's total.
- **Difference From** – the difference between one value and another reference value/item in the same field (e.g. comparing payment types against a baseline like Visa).
- **% Difference From** – the same comparison expressed as a percentage.
- **Running Total In** – a cumulative total building up across a chosen field (e.g. cumulative daily sales through a month).
- **Rank Smallest to Largest / Rank Largest to Smallest** – ranks each value against the others in the field (e.g. ranking departments by transaction count).

Each of these can also be renamed via Custom Name for clarity. Full worked examples (percentage-of-total sales by department, cumulative running totals, card-type differences, and transaction-count ranking) are on pages 87-93.

### 6.5 Review Exercise
Practical exercise building pivot tables with average cost, running totals, percentage-of-total order values, and largest-to-smallest sales ranking (book pages 94-96).

---
## Lesson 7 – Pivot Table Frequency Analysis (Book pages 97-106)

### 7.1 Grouping Date, Time and Numeric Data

When a pivot table field contains many distinct dates, times, or numbers, grouping them into bins reveals patterns that would otherwise be lost in the detail (e.g. how transaction counts vary across the days of the week, or which sales-amount band is most common). To group: click any value in the row/column labels → Analyze tab → Group → Group Field → in the Grouping dialog, set a Starting at/Ending at range and either pick a date unit (seconds, minutes, hours, days, months, quarters, years – for days, also specify "Number of days") or, for numeric fields, set the "By" interval size (e.g. group order amounts into bands of 20). Date fields also support multiple simultaneous grouping levels (e.g. group by both week and by day) for hierarchical drill-down. Steps and worked examples on pages 98-101.

### 7.2 Creating Custom Groups

Sometimes the grouping you want isn't based on date or numeric range but on your own business logic (e.g. grouping individual banks into custom regional or organisational groups). To do this manually: select the specific row/column items to combine (Ctrl-click for a non-contiguous selection) → Analyze tab → Group → Group Selection. This creates a new custom group (default-named "Group1" etc.) which you then rename to something meaningful; repeat for the other groups you want to create, and Excel automatically places any remaining ungrouped items into their own group. Steps and worked example (grouping banks into custom country/region groups) on pages 102-104.

### 7.3 Ungrouping Data

To reverse either an automatic or manual grouping, select a group label and choose Ungroup (Analyze tab → Group → Ungroup, or right-click → Ungroup), which restores the original, ungrouped list of items. Steps on page 105.

### 7.4 Review Exercise
Practical exercise grouping sales data by year/quarter, by numeric bands, and creating custom groups for combined regions (book page 106).

---

## Lesson 8 – Filtering Pivot Tables (Book pages 107-122)

### 8.1 Using Report Filters

Dragging a field into the **Filters** area of the PivotTable Fields pane adds a dropdown control above the pivot table that filters the *entire* report by that field (e.g. filter the whole table down to just one Year and one Region), without removing the field from view as a column/row. Multiple report filters can be stacked. The **Show Report Filter Pages** command (Analyze tab → Options → Show Report Filter Pages) is a time-saving feature that automatically generates one new worksheet per item in a chosen filter field, each pre-filtered to that single item – useful for quickly producing a separate report per region/branch/etc. Note that these generated pages are static snapshots and won't automatically update if the source pivot table later changes. Steps on pages 108-112.

### 8.2 Using Pivot Table Slicers

Pivot table slicers work like table slicers (Lesson 5.2) but for pivot tables: Analyze tab → Filter → Insert Slicer → tick the desired field(s) → OK. Slicers can be restyled (Slicer Styles gallery), resized, and have their column count changed for a more compact layout. A particularly powerful feature is **Report Connections** (Slicer's Options tab → Report Connections), which lets one slicer simultaneously filter multiple pivot tables/charts that share the same underlying data source – so selecting an item once updates every connected report. Steps on pages 113-117.

### 8.3 Using Timelines

A **Timeline** is a specialised slicer purpose-built for filtering by a date field, requiring at least one date-formatted field in the pivot table. To insert one: click in the pivot table → Analyze tab → Filter → Insert Timeline → select the date field → OK. A Timeline shows a horizontal scrollable strip of time periods; you can change the granularity shown (years/quarters/months/days) via a small dropdown, and select a specific range by dragging across the tiles. As with slicers, a Timeline can be connected to multiple pivot tables via Report Connections, and has a Clear Filter icon to reset it. Steps on pages 118-121.

### 8.4 Review Exercise
Practical exercise adding and linking slicers and a timeline across multiple pivot tables built from the same source data (book page 122).

---
## Lesson 9 – Using Pivot Charts (Book pages 123-138)

### 9.1 Inserting Pivot Charts from Pivot Tables

A **pivot chart** is a chart that visualises the data already summarised in a pivot table, created via Analyze tab → Tools → PivotChart from an existing pivot table. The mapping between the two is direct: pivot table row fields become the pivot chart's category (axis) fields, pivot table column fields become the chart's series/legend fields, and the pivot table's value fields become the plotted data. Because the chart is linked to the pivot table, changing the pivot table (e.g. re-filtering, re-grouping, or changing aggregation) automatically updates the chart, and vice versa for layout-type changes. If the source pivot table is later deleted, the pivot chart becomes an ordinary static chart. Steps on pages 124-127.

### 9.2 Creating Pivot Charts from Tables

A pivot chart (and the pivot table behind it) can also be generated in one step directly from a raw data table, without first manually building a pivot table: Insert tab → PivotChart → confirm the source range and destination → then, in the PivotChart Fields pane, drag fields into Filters/Legend(Series)/Axis(Categories)/Values, exactly as you would for a plain pivot table. Once created, the chart can be customised like any Excel chart: Design tab → Change Chart Type to switch chart types (e.g. to a 100% Stacked Bar to compare proportions); chart elements (title, legend, axis titles) can be added/edited via the Chart Elements button; field buttons (the small filter buttons Excel places on the chart itself) can be hidden or shown via the Field Buttons control. Steps and worked example (building a payment-method pivot chart with slicer, then changing its type and styling) on pages 129-136.

### 9.3 Review Exercise
Practical exercise creating a 3D pie pivot chart, adding a slicer, and building a clustered column pivot chart with a grouped salary-range axis (book pages 137-138).

---

## Lesson 10 – Data Visualization Tools (Book pages 139-150)

### 10.1 Key Features of Data Visualization Tools

Dedicated data visualization tools go beyond spreadsheet charts. Key features include: connecting to a wide range of data sources (spreadsheets, databases, web services); building varied visual types such as charts (line, bar, column, pie/donut), tables, Key Performance Indicator (KPI) visuals and gauge charts (which measure progress against a target), and maps (plotting data geographically); and combining several visuals into a single-page **report**, or into a **dashboard** – a curated, live-updating single screen pulling together the most important metrics for at-a-glance monitoring. These tools also typically support interactivity (filtering/drilling into visuals by clicking on them) and easy sharing/collaboration.

### 10.2 Data Visualization Tools Setup

The course introduces two example tools:
- **Microsoft Power BI** – consists of the free desktop application **Power BI Desktop** (used to connect to data, build reports, and design visuals) plus the online **Power BI service** (used to publish, share, and collaborate) and mobile apps. You need the (typically paid, though the course uses a free trial) Power BI service to actually share content built in Desktop.
- **Tableau Public** – a free, web-based alternative platform for building and publicly sharing visualizations, with a paid version also available.

Power BI Desktop is downloaded and installed free of charge from the Microsoft site (or the Microsoft Store). Steps on page 144.

### 10.3 Visualization Tool Environment

Once installed, the Power BI Desktop interface has: a **Ribbon** similar to other Microsoft Office apps; a **Report View**, where you build the actual report canvas and visuals (this is the default/main view); and a **Data View**, where you can inspect, explore and understand the raw data currently loaded into the model (similar to looking at a spreadsheet of the imported data).

### 10.4 Importing Data Sets from Spreadsheets

To bring an Excel workbook into Power BI: open Power BI Desktop → Home tab → External Data/Get Data group → Get Data → choose "Excel workbook" (or select it directly from the Get Data source list) → browse to and select the file → in the Navigator window, tick the specific table/sheet(s) to load → Load. The data then appears in the Fields pane, ready to be dragged onto visuals, and can be inspected via the Data View. Steps on pages 147-149.

### 10.5 Review Exercise
Self-test quiz on visualization tool concepts, followed by a practical exercise importing a sales spreadsheet into Power BI Desktop (book page 150).

---
## Lesson 11 – Creating Basic Data Visualizations (Book pages 151-183)

### 11.1 Creating Table Visualizations

The simplest visual is a **Table**, useful when you need to compare detailed/exact values rather than see an overall trend. Build it via Report view → click the Table icon in the Visualizations pane → drag the desired fields into the Values well (or drag-and-drop fields directly onto the canvas). Formatting options (via the paintbrush/Format icon) include grid lines, values number formatting, column headers, and cell colours/rules. Steps on pages 152-153.

### 11.2 Creating Chart Visualizations

Power BI's core chart types and when to use them:
- **Line chart** – best for showing a trend in continuous data over time (emphasises the flow/direction of values).
- **Pie chart / Donut chart** – best for showing parts of a whole (proportions), with the donut leaving a centre hole for extra labelling.
- **Bar chart / Column chart** – best for comparing values across categories; a bar chart lays categories out horizontally (good for long category labels), while a column chart lays them out vertically. Both come in **Clustered** (side-by-side comparison across categories) and **Stacked** (composition within each category, stacked on top of each other) variants.

Choosing the right chart depends on the purpose of the visualization (comparison vs composition vs distribution vs relationship), how many categories/data points need to be shown, and how many series need to be compared at once.

To build any of these: select the chart icon in the Visualizations pane, then drag fields into the Axis (categories), Legend (series), and Values wells as appropriate. Formatting (via the Format/paintbrush icon) covers: legend position and style, data colours per series, line style/markers (for line charts), axis titles and text size/colour, gridlines, and general chart title. The book walks through building and formatting a line chart (sales & profit by month, with markers and a highlighted data point), a donut chart (sales distribution by region, with percentage labels), a stacked column chart (sales & profit by region), and a clustered bar chart (sales by customer type, sorted and coloured) – each with detailed formatting steps. Full click-by-click steps for all of these chart builds are on pages 156-165.

### 11.3 Enhancing Visualizations Using Conditional Formatting

Conditional formatting highlights key values or exceptions directly within a table/matrix visual, without needing a separate chart:
- **Background colour** – fills a cell's background based on its value, either as a smooth colour **Gradient** between a minimum and maximum colour, or as discrete colour **Rules** for specific value ranges (e.g. red below 0, yellow 0-1500, green above 2000).
- **Font colour** – the same gradient/rules logic, but applied to the text colour instead of the cell background – useful when you still want to read the raw numbers clearly against the natural background.
- **Data bars** – draws an in-cell bar whose length is proportional to the value (with configurable minimum/maximum and bar colour), giving an at-a-glance sense of relative magnitude directly inside a table.

All three are accessed via the small drop-down arrow that appears on a field within the Values area of the Visualizations pane → Conditional Formatting → choose Background colour / Font colour / Data bars, then configure the rule in the resulting dialog. They can be removed the same way via Remove Conditional Formatting. Full worked examples and steps on pages 167-173.

### 11.4 Enhancing Visualizations Using Visual Level Filters

Every visual has its own **"Filters on this visual"** pane, letting you restrict what that one visual displays independently of the rest of the report page. For numeric fields you can apply threshold-style filters (e.g. "is less than 30000") combined with AND/OR logic across multiple conditions; for categorical fields you tick/untick specific items from a list, and a "Require single selection" option can force only one category to be viewable at a time. This is distinct from a report- or page-level filter, since it only affects the one selected visual. Steps on pages 174-176.

### 11.5 Creating Visualizations Using Maps

Two map visual types are covered, both relying on Power BI's built-in Bing-powered geocoding of a location field (e.g. Country, State):
- **Map (bubble map)** – places a bubble at each geographic point, with bubble *size* proportional to a chosen value (e.g. sales volume by state), and colour optionally used to distinguish a category. Good for showing both location and relative magnitude together.
- **Filled map (choropleth)** – shades each region (e.g. each U.S. state) with a colour intensity proportional to its value, using a gradient from a "low" colour to a "high" colour. Good for showing regional distribution/concentration patterns rather than exact point locations.

Build process for both: select the Map or Filled Map icon in Visualizations → drag the location field into Location and a numeric field into Bubble Size/colour saturation as appropriate → format via the Format pane (map style/background, border, bubble size/colour, gradient colours, title). Hovering or clicking on a location highlights that area's value, and filled maps can cross-filter other visuals on the same page when clicked. Full steps on pages 178-182.

### 11.6 Review Exercise
Practical exercise building a pie chart, clustered column chart, conditional formatting on a table, and data bars on a report, then saving the files (book pages 182-183).

---
## Lesson 12 – Creating Additional Data Visualizations (Book pages 184-204)

### 12.1 Creating Visualizations to Measure Progress

Two visual types exist specifically to show progress against a goal/target:
- **KPI (Key Performance Indicator) visualization** – compares a current "Base" measure against a "Goal"/target measure and shows the result as a single number plus a small trend indicator: shown in **green with a tick** if the base measure meets/exceeds the goal, **red with an exclamation mark** if it falls short, or a neutral/yellow indicator if it exactly matches the goal. Building one involves creating the base measure and goal measure (e.g. via a Quick/New Measure in Power BI's Calculations group), then dragging Base into the Value well, Trend axis into the Trend Axis well, and the Goal measure into the Target well of the KPI visual.
- **Gauge visualization** – displays progress as a needle/shaded arc on a circular dial running from a minimum value (left) to a maximum value (right), with a marked target line showing the goal and the current value both as a shaded arc and as a bold number. The Gauge axis's Minimum, Maximum, and Target values are all configurable in the Format pane.

Both visual types are commonly formatted with a custom title, text colour/size, and a visual border, and are often placed side-by-side or combined with a map for an executive-style progress dashboard. Full worked examples and steps for both KPI and Gauge visuals are on pages 185-192.

### 12.2 Creating Card Visualizations

A **Card** visual highlights a single important number very prominently – e.g. a total order count or total sales figure – making it ideal for headline metrics at the top of a report or dashboard. To build: select the Card icon in Visualizations → drag the relevant field into the Fields/Value well → if the field is a text/ID column being used just to count records, change its aggregation to **Count (Distinct)** so it counts unique orders/customers rather than summing or literally listing the values. Formatting options include Category label on/off, Callout value (the big number) font size/colour, title text, and border. Multiple cards are often copied, edited, and then aligned/distributed evenly using the Format tab's Align and Distribute commands. Steps on pages 193-196.

### 12.3 Creating Matrix Visualizations

A **Matrix** visual is Power BI's equivalent of an Excel pivot table: drag one field into Rows, another into Columns, and a numeric field into Values to produce a cross-tabulated summary (e.g. total sales broken down by customer type down the rows and product category across the columns, with row/column totals). Matrix-specific formatting includes row padding, global font size, cell background data bars, and borders, all set through Style presets or the individual Format pane sections. Steps on pages 197-199.

### 12.4 Adding Interactivity Using Slicers

Power BI **slicers** work like the Excel versions but as a first-class visual type: select the Slicer icon, then drag a field into it. List-style slicers show one item per row (with "Select all" and single/multi-select options); date slicers offer several styles including a **Between** range slider, a vertical/tile list, Before/After, and various relative-date options (e.g. "last 30 days"). Formatting covers the slicer header, selection highlight colour, and title text. As with all Power BI visuals, selecting an item in a slicer cross-filters every other visual on the same report page that shares the underlying field. Steps on pages 200-203.

### 12.5 Review Exercise
Practical exercise building card, matrix and slicer visuals, formatting titles/labels, and aligning multiple cards on a sales report (book page 204).

---

## Lesson 13 – Publishing and Sharing (Book pages 205-227)

### 13.1 Creating and Preparing to Share Reports

To move a report from your own machine (Power BI Desktop) into a form that others can view, you need a **Power BI service** account:
- **Power BI Pro licence** – full ability to publish, share reports/dashboards, and collaborate with other Pro users inside an organisation.
- **Power BI (free) licence** – lets you use most Power BI service capabilities individually but cannot share/collaborate on content with others in the same way.

The book uses a free 60-day trial sign-up (powerbi signup page → email address → verification code → account details) to demonstrate this. Steps on pages 207-208.

### 13.2 Publishing and Sharing Reports

From Power BI Desktop: File menu → Publish → Publish to Power BI → sign in → choose the destination workspace (e.g. "My workspace") → the report uploads to the Power BI service, where it can then be opened and viewed online. Two main ways to share a published report:
- **Email a link** – share report access with specific named people; a "Share report" dialog lets you add recipients, an optional message, and a "copy link" option. Recipients inside your organisation can view (and, if permitted, edit); the exact permissions available depend on licensing.
- **Publish to the web** – generates a public embed link/HTML code that requires no Power BI licence to view, suitable for embedding in a public website or blog. Because this makes the report visible to anyone with the link/embed code, Power BI shows an explicit warning before you confirm, and you should never publish sensitive/confidential data this way.

Steps for both sharing methods are on pages 209-216.

### 13.3 Creating Dashboards

A **dashboard** (created only within the Power BI service, not in Desktop) is a single canvas that pulls together the most important visuals — called **tiles** — from one or more reports into one place, for quick, at-a-glance monitoring. You build a dashboard by opening a published report, hovering over an individual visual, and clicking its "pin" icon to add it to a new or existing dashboard. Tiles can be freely resized (from small 1x1 units up to large 5x5) and repositioned, and (unlike the report page they came from) a dashboard mixes tiles pulled from potentially different reports/pages onto one screen. Steps on pages 218-219.

### 13.4 Sharing Dashboards

Dashboards are shared from the Power BI service via a **Share** icon, which opens a dialog to add recipient email addresses and configure options such as allowing recipients to reshare the dashboard, allowing them to build new content from the underlying data, and sending an email notification. Recipients need appropriate Power BI licensing to view shared content. Access can later be reviewed or revoked via Manage Permissions (e.g. "Remove reshare" to stop a recipient sharing further, or "Remove access" to cut off their access entirely). Steps on pages 220-223.

### 13.5 Good Design Practice

Recommended principles for effective reports/dashboards:
- Keep the layout **clean and uncluttered** so the most important insights aren't lost among decorative elements.
- Use **descriptive titles and labels** on every visual so a reader doesn't have to guess what they're looking at.
- Keep **fonts and colours consistent** across the report (generally 1-3 font sizes/styles) to give a professional, easy-to-scan appearance.
- Use **colour meaningfully rather than decoratively** – e.g. consistent use of green/red for positive/negative values, gradients to show magnitude, and reserving bright/dark colours for outliers or critical values that need attention.

### 13.6 Evaluating Results

This closes the loop back to the six-phase data analysis process introduced in Lesson 1.3: once reports/dashboards are built and deployed, the **Evaluation** phase asks whether the results actually answer the original business question, what new insights were gained, what practical next steps follow from them, and whether the analysis needs another iteration. Because the process is cyclical, evaluation findings typically feed back into a refined round of business/data understanding.

### 13.7 Review Exercise
Final self-test quiz covering report sharing options, publishing steps, dashboard design do's-and-don'ts, and consistent styling (book pages 227).

---

*Note: Book pages 228-236 contain an ICDL syllabus cross-reference table (mapping each official ICDL syllabus reference number to the relevant book section/page) — useful mainly for exam-preparation cross-checking rather than as study content in itself. Page 237 is the course's closing/completion page.*
