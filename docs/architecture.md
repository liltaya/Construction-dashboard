
# Construction Dashboard Architecture

```mermaid
flowchart TD
    UI[Qt6 MainWindow]
    O[Overview Dashboard]
    C[Cost Dashboard]
    S[Schedule Dashboard]
    W[Workforce and Safety]

    DS[DashboardService]
    AE[AnalyticsEngine]
    R[ConstructionRepository]
    DB[(SQLite Database)]
    CSV[CSV Parser and Validator]
    LOG[Logger]

    UI --> O
    UI --> C
    UI --> S
    UI --> W

    O --> DS
    C --> DS
    S --> DS
    W --> DS

    DS --> AE
    DS --> R
    UI --> R

    R --> DB
    CSV --> R

    UI --> LOG
    DS --> LOG
```

## Components

### Presentation Layer
Qt Widgets renders dashboards, tables, charts,
filters and project selection.

### Service Layer
DashboardService manages project operations and
coordinates analytics.

### Analytics Layer
AnalyticsEngine calculates spending, budget variance,
completion, overdue tasks and labor hours.

### Repository Layer
ConstructionRepository provides prepared SQL queries
for storing and retrieving records.

### Database Layer
Database manages SQLite connections and schema setup
using RAII.

### CSV Layer
CSV parsing and validation support data import.

### Logging
Logger records operational and error messages.
