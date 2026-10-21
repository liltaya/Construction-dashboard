#include "construction/MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QPainter>
#include <QPaintEvent>
#include <QProgressBar>
#include <QDate>
#include <QMap>
#include <QSet>
#include <QVariant>
#include <QAbstractItemView>
#include <QFont>

#include <algorithm>
#include <vector>

namespace construction {

namespace {

//Helper: Format monetary values

QString money(double value)
{
    return QString("$%1").arg(
        value, 0, 'f', 2
    );
}

//Custom chart widget using QPainter
//No Qt Charts dependency required

class BarChart : public QWidget
{
public:
    explicit BarChart(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        setMinimumHeight(170);
    }

    void setData(
        const QVector<QPair<QString, double>>& data)
    {
        data_ = data;
        update();
    }

protected:
    void paintEvent(QPaintEvent*) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.fillRect(rect(), palette().base());

        if (data_.isEmpty())
        {
            painter.drawText(
                rect(),
                Qt::AlignCenter,
                "No data available"
            );
            return;
        }

        const int left = 145;
        const int right = 115;
        const int top = 15;
        const int rowHeight = 38;

        double maximum = 1.0;

        for (const auto& bar : data_)
        {
            maximum = std::max(maximum, bar.second);
        }

        int chartWidth =
            std::max(20, width() - left - right);

        for (int i = 0; i < data_.size(); ++i)
        {
            const auto& bar = data_[i];

            int y = top + i * rowHeight;

            QRect labelRect(
                5, y, left - 15, 26
            );

            painter.setPen(palette().text().color());

            painter.drawText(
                labelRect,
                Qt::AlignVCenter | Qt::AlignRight,
                bar.first
            );

            //Chart background
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor("#e5e7eb"));

            painter.drawRoundedRect(
                QRect(left, y + 4, chartWidth, 18),
                4, 4
            );

            //Chart value
            int barWidth = static_cast<int>(
                chartWidth * bar.second / maximum
            );

            painter.setBrush(QColor("#2563eb"));

            painter.drawRoundedRect(
                QRect(left, y + 4, barWidth, 18),
                4, 4
            );

            //Value label
            painter.setPen(palette().text().color());

            painter.drawText(
                QRect(left + chartWidth + 8,
                      y, right - 10, 26),
                Qt::AlignVCenter,
                QString::number(bar.second, 'f', 1)
            );
        }
    }

private:
    QVector<QPair<QString, double>> data_;
};
// Helper: Create a KPI display

QGroupBox* createKpi(
    const QString& title,
    QLabel*& valueLabel)
{
    auto* group = new QGroupBox(title);
    auto* layout = new QVBoxLayout(group);

    valueLabel = new QLabel("--");

    QFont font = valueLabel->font();
    font.setPointSize(19);
    font.setBold(true);
    valueLabel->setFont(font);

    layout->addWidget(valueLabel);

    return group;
}
//Helper: Configure a table

void configureTable(
    QTableWidget* table,
    const QStringList& headers)
{
    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);

    table->horizontalHeader()
         ->setSectionResizeMode(
             QHeaderView::Stretch
         );

    table->setEditTriggers(
        QAbstractItemView::NoEditTriggers
    );

    table->setSelectionBehavior(
        QAbstractItemView::SelectRows
    );

    table->setAlternatingRowColors(true);
    table->setSortingEnabled(true);
}

//Sort numbers numerically, not alphabetically.
class NumericItem : public QTableWidgetItem
{
public:
    explicit NumericItem(double value)
        : QTableWidgetItem(
              QString::number(value, 'f', 2))
    {
        setData(Qt::UserRole, value);
    }

    bool operator<(
        const QTableWidgetItem& other
    ) const override
    {
        return data(Qt::UserRole).toDouble()
            < other.data(Qt::UserRole).toDouble();
    }
};

} //anonymous namespace

//MAIN WINDOW CONSTRUCTOR

MainWindow::MainWindow(
    DashboardService& service,
    ConstructionRepository& repository,
    QWidget* parent)
    : QMainWindow(parent),
      service_(service),
      repository_(repository)
{
    buildUI();
    loadProjects();
}

//BUILD MAIN DASHBOARD

void MainWindow::buildUI()
{
    setWindowTitle("Construction Dashboard");
    resize(1200, 800);

    auto* central = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(central);

    auto* title = new QLabel(
        "Construction Management Dashboard"
    );

    QFont titleFont = title->font();
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);

    mainLayout->addWidget(title);

    //Project selector
    auto* selectorLayout = new QHBoxLayout;

    selectorLayout->addWidget(
        new QLabel("Select project:")
    );

    projectSelector_ = new QComboBox;

    selectorLayout->addWidget(projectSelector_, 1);

    mainLayout->addLayout(selectorLayout);

    //Dashboard tabs
    tabs_ = new QTabWidget;

    buildOverviewPage();
    buildCostPage();
    buildSchedulePage();
    buildWorkforcePage();

    tabs_->addTab(overviewPage_, "Overview");
    tabs_->addTab(costPage_, "Costs");
    tabs_->addTab(schedulePage_, "Schedule");
    tabs_->addTab(workforcePage_, "Workforce / Safety");

    mainLayout->addWidget(tabs_, 1);

    setCentralWidget(central);

    //Refresh whenever selected project changes
    connect(
        projectSelector_,
        QOverload<int>::of(
            &QComboBox::currentIndexChanged),
        this,
        [this](int)
        {
            refreshDashboard();
        }
    );
}

//OVERVIEW PAGE

void MainWindow::buildOverviewPage()
{
    overviewPage_ = new QWidget;

    auto* layout = new QVBoxLayout(overviewPage_);
    auto* metrics = new QGridLayout;

    metrics->addWidget(
        createKpi("Budget", budgetLabel_), 0, 0
    );

    metrics->addWidget(
        createKpi("Actual Cost", actualCostLabel_), 0, 1
    );

    metrics->addWidget(
        createKpi("Budget Variance", varianceLabel_), 0, 2
    );

    metrics->addWidget(
        createKpi("Completion", completionLabel_), 1, 0
    );

    metrics->addWidget(
        createKpi("Overdue Tasks", overdueLabel_), 1, 1
    );

    metrics->addWidget(
        createKpi("Labor Hours", laborLabel_), 1, 2
    );

    layout->addLayout(metrics);

    auto* chartGroup =
        new QGroupBox("Budget vs. Actual Cost");

    auto* chartLayout = new QVBoxLayout(chartGroup);

    overviewChart_ = new BarChart;

    chartLayout->addWidget(overviewChart_);
    layout->addWidget(chartGroup);
    layout->addStretch();
}

//COST PAGE

void MainWindow::buildCostPage()
{
    costPage_ = new QWidget;

    auto* layout = new QVBoxLayout(costPage_);

    //Category chart
    auto* group = new QGroupBox(
        "Costs by Category"
    );

    auto* groupLayout = new QVBoxLayout(group);

    categoryChart_ = new BarChart;

    groupLayout->addWidget(categoryChart_);
    layout->addWidget(group);

    //Cost filters
    auto* filters = new QHBoxLayout;

    costSearch_ = new QLineEdit;
    costSearch_->setPlaceholderText(
        "Search costs..."
    );

    costCategoryFilter_ = new QComboBox;
    costCategoryFilter_->addItem("All categories");

    filters->addWidget(costSearch_, 2);
    filters->addWidget(costCategoryFilter_, 1);

    layout->addLayout(filters);

    //Cost table
    costTable_ = new QTableWidget;

    configureTable(
        costTable_,
        {"ID", "Category", "Description",
         "Amount", "Date"}
    );

    layout->addWidget(costTable_, 1);

    connect(
        costSearch_,
        &QLineEdit::textChanged,
        this,
        [this](const QString&)
        {
            filterCosts();
        }
    );

    connect(
        costCategoryFilter_,
        QOverload<int>::of(
            &QComboBox::currentIndexChanged),
        this,
        [this](int)
        {
            filterCosts();
        }
    );
}

//SCHEDULE PAGE

void MainWindow::buildSchedulePage()
{
    schedulePage_ = new QWidget;

    auto* layout = new QVBoxLayout(schedulePage_);

    auto* chartsLayout = new QHBoxLayout;

    auto* progressGroup = new QGroupBox(
        "Actual vs. Planned Progress"
    );

    auto* progressLayout =
        new QVBoxLayout(progressGroup);

    progressChart_ = new BarChart;
    progressLayout->addWidget(progressChart_);

    chartsLayout->addWidget(progressGroup);

    auto* statusGroup = new QGroupBox(
        "Task Status"
    );

    auto* statusLayout =
        new QVBoxLayout(statusGroup);

    statusChart_ = new BarChart;
    statusLayout->addWidget(statusChart_);

    chartsLayout->addWidget(statusGroup);

    layout->addLayout(chartsLayout);

    //Task filters
    auto* filters = new QHBoxLayout;

    taskSearch_ = new QLineEdit;
    taskSearch_->setPlaceholderText(
        "Search tasks..."
    );

    statusFilter_ = new QComboBox;

    statusFilter_->addItems({
        "All statuses",
        "completed",
        "in_progress",
        "not_started",
        "cancelled",
        "Overdue only"
    });

    filters->addWidget(taskSearch_, 2);
    filters->addWidget(statusFilter_, 1);

    layout->addLayout(filters);

    //Task table
    taskTable_ = new QTableWidget;

    configureTable(
        taskTable_,
        {"ID", "Task", "Status", "Priority",
         "Start", "Due", "Overdue"}
    );

    layout->addWidget(taskTable_, 1);

    connect(
        taskSearch_,
        &QLineEdit::textChanged,
        this,
        [this](const QString&)
        {
            filterTasks();
        }
    );

    connect(
        statusFilter_,
        QOverload<int>::of(
            &QComboBox::currentIndexChanged),
        this,
        [this](int)
        {
            filterTasks();
        }
    );
}

//WORKFORCE / SAFETY PAGE

void MainWindow::buildWorkforcePage()
{
    workforcePage_ = new QWidget;

    auto* layout = new QVBoxLayout(workforcePage_);

    auto* metrics = new QHBoxLayout;

    metrics->addWidget(
        createKpi("Recorded Labor Hours",
                  workforceHoursLabel_)
    );

    layout->addLayout(metrics);

    auto* logsGroup = new QGroupBox(
        "Work Logs"
    );

    auto* logsLayout = new QVBoxLayout(logsGroup);

    workLogTable_ = new QTableWidget;

    configureTable(
        workLogTable_,
        {"Log ID", "Worker ID", "Hours", "Date"}
    );

    logsLayout->addWidget(workLogTable_);

    layout->addWidget(logsGroup, 1);

    //The original repository has no incident
    //queries, so this is an explicit placeholder.
    auto* safetyGroup = new QGroupBox(
        "Safety Monitoring"
    );

    auto* safetyLayout =
        new QVBoxLayout(safetyGroup);

    safetyLabel_ = new QLabel(
        "Incident records are not connected yet. "
        "Add an incidents table and repository "
        "queries to enable safety metrics."
    );

    safetyLabel_->setWordWrap(true);

    safetyLayout->addWidget(safetyLabel_);

    layout->addWidget(safetyGroup);
}

//LOAD PROJECTS FROM SQLITE

void MainWindow::loadProjects()
{
    const auto projects = service_.getProjects();

    projectSelector_->blockSignals(true);
    projectSelector_->clear();

    for (const auto& project : projects)
    {
        projectSelector_->addItem(
            QString::fromStdString(project.name),
            QVariant::fromValue(
                static_cast<qlonglong>(project.id)
            )
        );
    }

    projectSelector_->blockSignals(false);

    if (projectSelector_->count() > 0)
    {
        refreshDashboard();
    }
}

//REFRESH ALL TABS

void MainWindow::refreshDashboard()
{
    if (projectSelector_->currentIndex() < 0)
    {
        return;
    }

    const std::int64_t id =
        projectSelector_->currentData().toLongLong();

    refreshOverview(id);
    refreshCosts(id);
    refreshSchedule(id);
    refreshWorkforce(id);
}

//REFRESH OVERVIEW

void MainWindow::refreshOverview(
    std::int64_t projectId)
{
    const auto analytics =
        service_.getProjectAnalytics(projectId);

    budgetLabel_->setText(
        money(analytics.budget)
    );

    actualCostLabel_->setText(
        money(analytics.actualCost)
    );

    varianceLabel_->setText(
        money(analytics.budgetVariance)
    );

    completionLabel_->setText(
        QString::number(
            analytics.completionPercent, 'f', 1
        ) + "%"
    );

    overdueLabel_->setText(
        QString::number(analytics.overdueTasks)
    );

    laborLabel_->setText(
        QString::number(
            analytics.laborHours, 'f', 1
        ) + " h"
    );

    auto* chart =
        static_cast<BarChart*>(overviewChart_);

    chart->setData({
        {"Budget", analytics.budget},
        {"Actual Cost", analytics.actualCost}
    });
}
//REFRESH COSTS

void MainWindow::refreshCosts(
    std::int64_t projectId)
{
    const auto costs =
        repository_.findCostsByProject(projectId);

    QMap<QString, double> categoryTotals;
    QSet<QString> categories;

    costTable_->setSortingEnabled(false);
    costTable_->setRowCount(
        static_cast<int>(costs.size())
    );

    for (int i = 0; i < static_cast<int>(costs.size()); ++i)
    {
        const auto& cost = costs[i];

        QString category =
            QString::fromStdString(cost.category);

        categoryTotals[category] += cost.amount;
        categories.insert(category);

        costTable_->setItem(
            i, 0,
            new NumericItem(cost.id)
        );

        costTable_->setItem(
            i, 1,
            new QTableWidgetItem(category)
        );

        costTable_->setItem(
            i, 2,
            new QTableWidgetItem(
                QString::fromStdString(
                    cost.description
                )
            )
        );

        costTable_->setItem(
            i, 3,
            new NumericItem(cost.amount)
        );

        costTable_->setItem(
            i, 4,
            new QTableWidgetItem(
                QString::fromStdString(
                    cost.entryDate
                )
            )
        );
    }

    costTable_->setSortingEnabled(true);

    //Update category filter
    const QString previous =
        costCategoryFilter_->currentText();

    costCategoryFilter_->blockSignals(true);
    costCategoryFilter_->clear();
    costCategoryFilter_->addItem("All categories");

    QStringList categoryNames = categories.values();
    categoryNames.sort();

    costCategoryFilter_->addItems(categoryNames);

    int index =
        costCategoryFilter_->findText(previous);

    costCategoryFilter_->setCurrentIndex(
        index >= 0 ? index : 0
    );

    costCategoryFilter_->blockSignals(false);

    //Update category chart
    QVector<QPair<QString, double>> bars;

    for (auto it = categoryTotals.cbegin();
         it != categoryTotals.cend(); ++it)
    {
        bars.append({it.key(), it.value()});
    }

    auto* chart =
        static_cast<BarChart*>(categoryChart_);

    chart->setData(bars);

    filterCosts();
}


//REFRESH SCHEDULE

void MainWindow::refreshSchedule(
    std::int64_t projectId)
{
    const auto tasks =
        repository_.findTasksByProject(projectId);

    const auto analytics =
        service_.getProjectAnalytics(projectId);

    //Progress chart
    static_cast<BarChart*>(progressChart_)
        ->setData({
            {"Actual", analytics.completionPercent},
            {"Planned", analytics.plannedCompletionPercent}
        });

    QMap<QString, double> statusCounts;

    taskTable_->setSortingEnabled(false);
    taskTable_->setRowCount(
        static_cast<int>(tasks.size())
    );

    const QDate today = QDate::currentDate();

    for (int i = 0; i < static_cast<int>(tasks.size()); ++i)
    {
        const auto& task = tasks[i];

        QString status =
            QString::fromStdString(task.status);

        statusCounts[status] += 1.0;

        QDate due = QDate::fromString(
            QString::fromStdString(task.dueDate),
            Qt::ISODate
        );

        bool overdue =
            due.isValid() &&
            due < today &&
            status != "completed" &&
            status != "cancelled";

        taskTable_->setItem(
            i, 0, new NumericItem(task.id)
        );

        taskTable_->setItem(
            i, 1,
            new QTableWidgetItem(
                QString::fromStdString(task.name)
            )
        );

        taskTable_->setItem(
            i, 2, new QTableWidgetItem(status)
        );

        taskTable_->setItem(
            i, 3,
            new QTableWidgetItem(
                QString::fromStdString(task.priority)
            )
        );

        taskTable_->setItem(
            i, 4,
            new QTableWidgetItem(
                QString::fromStdString(task.startDate)
            )
        );

        taskTable_->setItem(
            i, 5,
            new QTableWidgetItem(
                QString::fromStdString(task.dueDate)
            )
        );

        auto* overdueItem = new QTableWidgetItem(
            overdue ? "Yes" : "No"
        );

        if (overdue)
        {
            overdueItem->setForeground(
                QColor("#dc2626")
            );
        }

        taskTable_->setItem(i, 6, overdueItem);
    }

    taskTable_->setSortingEnabled(true);

    QVector<QPair<QString, double>> bars;

    for (auto it = statusCounts.cbegin();
         it != statusCounts.cend(); ++it)
    {
        bars.append({it.key(), it.value()});
    }

    static_cast<BarChart*>(statusChart_)
        ->setData(bars);

    filterTasks();
}

// REFRESH WORKFORCE

void MainWindow::refreshWorkforce(
    std::int64_t projectId)
{
    const auto logs =
        repository_.findWorkLogsByProject(projectId);

    double totalHours = 0.0;

    workLogTable_->setSortingEnabled(false);
    workLogTable_->setRowCount(
        static_cast<int>(logs.size())
    );

    for (int i = 0; i < static_cast<int>(logs.size()); ++i)
    {
        const auto& log = logs[i];

        totalHours += log.hours;

        workLogTable_->setItem(
            i, 0, new NumericItem(log.id)
        );

        workLogTable_->setItem(
            i, 1, new NumericItem(log.workerId)
        );

        workLogTable_->setItem(
            i, 2, new NumericItem(log.hours)
        );

        workLogTable_->setItem(
            i, 3,
            new QTableWidgetItem(
                QString::fromStdString(log.workDate)
            )
        );
    }

    workLogTable_->setSortingEnabled(true);

    workforceHoursLabel_->setText(
        QString::number(totalHours, 'f', 1) + " h"
    );
    const auto incidentCount =
    repository_.countIncidentsByProject(projectId);

safetyLabel_->setText(
    QString("Recorded safety incidents: %1")
        .arg(incidentCount)
);
}
//FILTER COST TABLE

void MainWindow::filterCosts()
{
    const QString search =
        costSearch_->text().trimmed();

    const QString category =
        costCategoryFilter_->currentText();

    for (int row = 0;
         row < costTable_->rowCount(); ++row)
    {
        auto* categoryItem = costTable_->item(row, 1);
        auto* descriptionItem = costTable_->item(row, 2);

        if (!categoryItem || !descriptionItem)
            continue;

        bool matchesSearch =
            categoryItem->text().contains(
                search, Qt::CaseInsensitive
            ) ||
            descriptionItem->text().contains(
                search, Qt::CaseInsensitive
            );

        bool matchesCategory =
            category == "All categories" ||
            categoryItem->text() == category;

        costTable_->setRowHidden(
            row,
            !(matchesSearch && matchesCategory)
        );
    }
}
//FILTER TASK TABLE

void MainWindow::filterTasks()
{
    const QString search =
        taskSearch_->text().trimmed();

    const QString status =
        statusFilter_->currentText();

    for (int row = 0;
         row < taskTable_->rowCount(); ++row)
    {
        auto* nameItem = taskTable_->item(row, 1);
        auto* statusItem = taskTable_->item(row, 2);
        auto* overdueItem = taskTable_->item(row, 6);

        if (!nameItem || !statusItem || !overdueItem)
            continue;

        bool matchesSearch =
            nameItem->text().contains(
                search, Qt::CaseInsensitive
            );

        bool matchesStatus =
            status == "All statuses" ||
            statusItem->text() == status ||
            (status == "Overdue only" &&
             overdueItem->text() == "Yes");

        taskTable_->setRowHidden(
            row,
            !(matchesSearch && matchesStatus)
        );
    }
}

} //namespace construction
