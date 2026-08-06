# ICDL Data Analytics – Foundation: Study Notes

Notes summarizing the eBook "ICDL Data Analytics - Foundation 1.0 Asia eng", lesson by lesson. Each section lists what it covers, and any hands-on task or exercise you need to complete is marked under **Task**.

---

## Lesson 1 – Key Concepts

**1.1 Types of Data Analytics** – Introduces the wide range of sources organisations collect data from (mobile devices, online platforms, payment systems, cameras, GPS, wireless sensors, legacy systems) and defines data analytics. Splits analytics into quantitative (numeric/measurable) and qualitative (attitudes/opinions, less structured), then into four types: descriptive (what happened), diagnostic (why it happened), predictive (what's likely to happen) and prescriptive (what to do next).
- **Task:** Case study on a retailer's big-data use – classify listed activities into descriptive, diagnostic, predictive or prescriptive analytics.

**1.2 Business Benefits** – Covers four benefits data analytics brings to a business: identifying patterns/trends, improving efficiency, supporting decision-making, and presenting information effectively (e.g. dashboards, visual reports).

**1.3 Data Analysis Process** – Describes a six-phase cyclical process: business understanding, data understanding, data preparation, modelling, evaluation, deployment. Notes this Foundation course focuses on the data understanding and data preparation phases in Excel/Power BI.

**1.4 Data Protection Considerations** – Covers key data protection principles (lawful basis, specified purpose, minimal/adequate data, accuracy, secure storage), GDPR as an example law, and anonymising personal data by removing direct identifiers.

**1.5 Review Exercise**
- **Task:** Answer a set of quiz questions covering analytics types, business benefits, and phases of the data analysis process (multiple choice + short answer, pen-and-paper style).

---

## Lesson 2 – Statistical Analysis

**2.1 Summary Statistics Introduction** – Introduces two families of statistics: measures of central tendency (mean, median, mode) and measures of variation (range, variance, quartiles).
- **Task:** Case example about shoe-size data – discuss what counts as an "average" size and whether a single value or range is more meaningful.

**2.2 Measures of Central Tendency** – Explains mean, median and mode with worked examples (retail gross profit, customer satisfaction ratings), showing how outliers skew the mean versus the median.

**2.3 Calculating Central Tendency**
- **Task:** Open **Orders1.xlsx**. Use `=AVERAGE()`, `=MEDIAN()` and `=MODE()` formulas on the order amount column. Save the file as **Orders1completed.xlsx**.

**2.4 Measures of Variation** – Introduces range, variance and how they show how spread-out a data set is, comparing two stores' sales data for consistency.

**2.5 Calculating Variation**
- **Task:** Open **Orders2.xlsx**. Use `=MAX()-MIN()` for range, `=VAR.P()` for variance, and `=QUARTILE()` for quartile values on an amount column. Answer a follow-up question about which value set is more spread out.

**2.6 Review Exercise**
- **Task:** Open **Cards.xlsx**. Enter formulas for mean, median, mode, range and quartiles on credit-card transaction data, then answer analysis questions about the most frequent/average charged amounts.

---

## Lesson 3 – Importing Data Sets

**3.1 Importing Data Sets Introduction** – Overview of common external data sources (text files, spreadsheets, web tables, databases) and connected (refreshable) vs static imports.

**3.2 Importing Data from Text Files** – Explains CSV vs delimited text files.
- **Task:** Import **Customer Data.csv** into the **Customers.xlsx** workbook using the Text Import Wizard / Get Data, choosing delimiters, skipping specific columns, and setting the date format.

**3.3 Importing Data from Spreadsheets**
- **Task:** Import a table from **Ticket Sales.xlsx** into the **Trips.xlsx** workbook via Existing Connections / Get Data From Workbook.

**3.4 Importing Data from Website Tables**
- **Task:** Import a web table of exchange rates (from icdl.org) into **Rates.xlsx** using Get Data From Web.

**3.5 Importing Data from Database Tables**
- **Task:** Import the tblCustomers table from the **BakeryDatabase** Access database into **Customer Details.xlsx**.

**3.6 Review Exercise**
- **Task:** Create a new workbook. Import **Real Estate.csv** (comma-delimited, headers present, skip the Sale Date/Latitude/Longitude columns). Save as **Real Estate Imported**.

---

## Lesson 4 – Shaping Data Sets

**4.1 Shaping Data Sets Introduction** – Overview of cleaning tasks needed before analysis (fixing spelling/formatting, removing duplicates, merging/splitting columns) and Excel's built-in cleaning tools.

**4.2 Removing Duplicate Data**
- **Task:** Open **Duplicate Records.xlsx**. Use Excel's Remove Duplicates tool to find and delete duplicate salesperson rows.

**4.3 Validating Data Using VLOOKUP** – Explains VLOOKUP syntax for checking whether a value exists in a reference list.
- **Task:** Open **Value Validation.xlsx**. Write a VLOOKUP formula to cross-check country codes against a reference table.

**4.4 Validating Data Using IF Functions** – Explains IF (including nested/AND/OR) for validating whether a value falls within an accepted range.
- **Task:** In the same workbook, write IF-based formulas to flag sales values that fall outside a minimum/maximum range.

**4.5 Extracting Values Using Text Functions** – Explains LEFT, RIGHT, MID, LEN and FIND, including combinations like LEFT+LEN.
- **Task:** Open **Text Functions.xlsx**. Split a combined country-code field into separate Country and Country Code columns using text functions.

**4.6 Review Exercise**
- **Task:** Open **Shipping.xlsx**. Remove duplicate records, extract order/shipping details using LEN/IF/VLOOKUP/text functions, and calculate a commission amount using a lookup-based rate table.

---

## Lesson 5 – Filtering Data Sets

**5.1 Formatting Data Sets as Tables**
- **Task:** Open **Sales.xlsx**. Convert the data range into an Excel Table and configure table style options (header row, banded rows, filter button).

**5.2 Using Table Slicers**
- **Task:** Open **Slicers.xlsx**. Insert slicers on the table, resize them, and use them (including multi-select) to filter the data; then clear the filter.

**5.3 Review Exercise**
- **Task:** Open **Regional Sales.xlsx**. Format the range as a table, remove banded rows/AutoFilter, insert and resize slicers for Region and Category, then filter for specific values (e.g. credit transactions for particular regions).

---

## Lesson 6 – Pivot Table Data Aggregation

**6.1 Summarising Data Introduction** – Why pivot tables are useful for answering business questions from large data sets.

**6.2 Changing Aggregation Methods** – Explains pivot table summary functions (Sum, Count, Average, Max, Min).
- **Task:** In **Cards Pivot.xlsx**, change a pivot field's aggregation method to Average, rename it, and format it as currency.

**6.3 Displaying Multiple Aggregation Values**
- **Task:** In the same workbook, display Sum, Count, Max and Min aggregations together in one pivot table and rename the fields (Total, Transactions, Highest, Lowest).

**6.4 Using Built-In Calculations** – Explains "Show Values As" options: % of Grand Total, % of Column/Row Total, Difference From, % Difference From, Running Total, Rank.
- **Task:** Apply % of Grand Total, a ranking calculation, and a running (cumulative) total calculation to pivot table values.

**6.5 Review Exercise**
- **Task:** Open **Aggregate.xlsx**. Build pivot tables across the Trips, Shipping and Sales worksheets to show average cost/ticket totals, ranked values, running totals, and percentage shares.

---

## Lesson 7 – Pivot Table Frequency Analysis

**7.1 Grouping Date, Time and Numeric Data**
- **Task:** In **Cards Group.xlsx**, group pivot table dates by week/month and group numeric transaction amounts into intervals of 20.

**7.2 Creating Custom Groups**
- **Task:** Manually select and group specific issuers (e.g. banks) into a named custom group ("USA") within a pivot table.

**7.3 Ungrouping Data**
- **Task:** Ungroup a previously grouped field in the pivot table to restore the original view.

**7.4 Review Exercise**
- **Task:** Open **Sales Group.xlsx**. Ungroup an existing date grouping, regroup by Year and Quarter, group sales amounts into thousand-unit bands, and create/rename custom regional groups (e.g. combining Northeast & Northwest into "North").

---

## Lesson 8 – Filtering Pivot Tables

**8.1 Using Report Filters**
- **Task:** In **Sales.xlsx**, add Account Date and Region as report filters on a pivot table, then use "Show Report Filter Pages" to auto-generate one worksheet per region.

**8.2 Using Pivot Table Slicers**
- **Task:** In **Pivot Slicers.xlsx**, insert, style and resize a slicer, and connect it to multiple pivot tables via Report Connections so one slicer filters both.

**8.3 Using Timelines**
- **Task:** In **Timeline.xlsx**, insert a Timeline control on a date field, change its time level (years/quarters/months/days), and adjust the visible date range.

**8.4 Review Exercise**
- **Task:** Open **Purchases.xlsx**. Add and link slicers and a timeline across multiple pivot tables, adjust their display settings, and set specific filter selections (e.g. filter to certain categories and a date range).

---

## Lesson 9 – Using Pivot Charts

**9.1 Inserting Pivot Charts from Pivot Tables**
- **Task:** In **Regional1.xlsx**, create a pivot chart directly from an existing pivot table and customise chart elements (title, axis buttons, gridlines, legend, chart type/style).

**9.2 Creating Pivot Charts from Tables**
- **Task:** In **Regional2.xlsx**, create a pivot chart (and its underlying pivot table) directly from a plain data table by dragging fields into the chart's filter/legend/axis/values areas, then format it.

**9.3 Review Exercise**
- **Task:** Open **Personnel.xlsx**. Insert and format a 3D pie pivot chart ("Salary Distribution"), plus a clustered column chart with a slicer, and build a "Salary Range Frequency Distribution" chart by grouping salaries into 10,000-unit bands.

---

## Lesson 10 – Data Visualization Tools

**10.1 Key Features of Data Visualization Tools** – Overview of visualisation types (tables, KPIs, gauges, maps, dashboards) and their interactive filtering/drill-down abilities.

**10.2 Data Visualization Tools Setup** – Introduces Microsoft Power BI (Desktop + Service) and Tableau Public as common visualisation tools.

**10.3 Visualization Tool Environment**
- **Task:** Download and install Power BI Desktop, and get familiar with its interface (Ribbon, Report View, Data View).

**10.4 Importing Data Sets from Spreadsheets**
- **Task:** Import **Sales Format.xlsx** into Power BI Desktop and save the report as a .pbix file.

**10.5 Review Exercise**
- **Task:** Answer quiz questions on visualisation concepts, then open Power BI Desktop, import a Sales data set, and save it as **Sales overview imported.pbix**.

---

## Lesson 11 – Creating Basic Data Visualizations

**11.1 Creating Table Visualizations**
- **Task:** In **TableChart.pbixi**, build and format a table visual from Sales/Country fields.

**11.2 Creating Chart Visualizations** – Overview of chart types (line, pie/donut, bar/column, stacked/clustered).
- **Task:** In **Sales Chart.pbix**, build and format a line chart, a donut chart, a stacked column chart, and a clustered bar chart, adjusting titles, legends, colours and axes.

**11.3 Enhancing Visualizations Using Conditional Formatting**
- **Task:** Apply background-colour and font-colour conditional formatting rules to table values based on magnitude (e.g. highest/lowest sales).

**11.4 Enhancing Visualizations Using Data Bars**
- **Task:** Add in-cell data bars to a table visualisation to represent relative values, then save as **Sales Chart Formatted**.

**11.5 Enhancing Visualizations Using Visual Level Filters**
- **Task:** Apply filters to an individual visual only (not the whole report), using numeric ("less than") and category-based single-selection filters. Save as **Visual Levels Added**.

**11.6 Creating Visualizations Using Maps**
- **Task:** Create a bubble map (sales by state) and a filled/choropleth map (customer distribution by state), with formatting for borders, colours, and tooltips. Save as **MapChart Added**.

**11.7 Review Exercise**
- **Task:** Answer quiz questions, then build/format a clustered column chart with custom colours, a conditional-formatted table (with red/yellow/green thresholds), and a bar chart with custom bar colour/direction; save as **PivotReport Added**.

---

## Lesson 12 – Additional Data Visualizations

**12.1 Creating Visualizations to Measure Progress** – Explains KPI visuals (actual vs target, with status icon) and Gauge visuals (progress arc toward a goal/target).
- **Task:** In **KPI.pbix**/**KPI Solution.pbix**, create a Customers KPI and an Orders KPI (with trend axis and target), then a Sales Target gauge chart; format titles, colours and axis ranges. Save as **KPI Added** / **Gauge added**.

**12.2 Creating Card Visualizations**
- **Task:** In **Orders Card.pbix**, create card visuals showing number of orders, number of customers, and total sales, then align/distribute and format them. Save as **Orders Card Added**.

**12.3 Creating Matrix Visualizations**
- **Task:** Build a Matrix visual showing total sales by customer type (rows) and product category (columns), then format and resize it. Save as **Matrix Added**.

**12.4 Adding Interactivity Using Slicers**
- **Task:** Add a Region list slicer and an Order Date range/timeline slicer to a sales report, format them, and save as **Orders Report Final**.

**12.5 Review Exercise**
- **Task:** Answer quiz questions, then build a report combining card, matrix, gauge and map visualizations with slicers, following specific formatting instructions (title alignment, borders, conditional formatting) and save as **CreateSummary/PivotReport** outputs.

---

## Lesson 13 – Publishing and Sharing

**13.1 Creating and Preparing to Share Reports** – Explains Power BI Pro vs Free licensing.
- **Task:** Sign up for a free Power BI account/trial (if you want to follow along with sharing steps).

**13.2 Publishing and Sharing Reports** – Explains the two sharing options: emailing a link via the Power BI service, or publishing publicly to the web (embed code).
- **Task:** Publish a report from Power BI Desktop to the Power BI service, then share it via a link, and separately try the "Publish to Web" embed-code option.

**13.3 Creating Dashboards** – Dashboards are made of "tiles" pinned from one or more reports (dashboards can only be created in the Power BI service, not Desktop).
- **Task:** Pin several visuals from a report into a new dashboard, then resize/rename the tiles.

**13.4 Sharing Dashboards**
- **Task:** Share a dashboard with other users via a link or email invitation, and review/adjust their access permissions (e.g. remove reshare or remove access rights).

**13.5 Good Design Practice** – Tips: use a clean, uncluttered layout; use descriptive titles and labels; use consistent fonts; use colour purposefully to highlight meaning (not decoration).

**13.6 Evaluating Results** – Revisits the "evaluation" phase of the data analysis process, with reflection questions: what insights were gained, does the analysis address the original problem, and what should happen next.

**13.7 Review Exercise**
- **Task:** Answer quiz questions on sharing methods, licensing requirements, and good report/dashboard design practice.

---

## End of Book

The eBook ends with a completion/congratulations page confirming the skills covered: data analytics key concepts, statistical analysis, importing/cleansing/filtering data, pivot tables and pivot charts, data visualisation techniques, and creating/sharing reports and dashboards — preparing the reader for the ICDL certification test.
