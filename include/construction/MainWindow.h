#pragma once

#include "construction/repositories/ConstructionRepository.h"
#include "construction/services/DashboardService.h"

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QTabWidget>
#include <QLabel>
#include <QWidget>

#include <cstdint>

namespace construction {

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(
        DashboardService& service,
        ConstructionRepository& repository,
        QWidget* parent = nullptr
    );

private:
    //Backend references
    DashboardService& service_;
    ConstructionRepository& repository_;

    //Global controls
    QComboBox* projectSelector_ = nullptr;
    QTabWidget* tabs_ = nullptr;

    //Dashboard pages
    QWidget* overviewPage_ = nullptr;
    QWidget* costPage_ = nullptr;
    QWidget* schedulePage_ = nullptr;
    QWidget* workforcePage_ = nullptr;

    //Overview
    QLabel* budgetLabel_ = nullptr;
    QLabel* actualCostLabel_ = nullptr;
    QLabel* varianceLabel_ = nullptr;
    QLabel* completionLabel_ = nullptr;
    QLabel* overdueLabel_ = nullptr;
    QLabel* laborLabel_ = nullptr;

    QWidget* overviewChart_ = nullptr;

    //Costs
    QWidget* categoryChart_ = nullptr;
    QTableWidget* costTable_ = nullptr;
    QLineEdit* costSearch_ = nullptr;
    QComboBox* costCategoryFilter_ = nullptr;

    //Schedule
    QWidget* progressChart_ = nullptr;
    QWidget* statusChart_ = nullptr;
    QTableWidget* taskTable_ = nullptr;
    QLineEdit* taskSearch_ = nullptr;
    QComboBox* statusFilter_ = nullptr;

    //Workforce / Safety
    QLabel* workforceHoursLabel_ = nullptr;
    QLabel* safetyLabel_ = nullptr;
    QTableWidget* workLogTable_ = nullptr;

    //Setup methods
    void buildUI();
    void buildOverviewPage();
    void buildCostPage();
    void buildSchedulePage();
    void buildWorkforcePage();

    //Data loading
    void loadProjects();
    void refreshDashboard();
    void refreshOverview(std::int64_t projectId);
    void refreshCosts(std::int64_t projectId);
    void refreshSchedule(std::int64_t projectId);
    void refreshWorkforce(std::int64_t projectId);

    //Filtering
    void filterCosts();
    void filterTasks();
};

}
