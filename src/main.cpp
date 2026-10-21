#include "construction/MainWindow.h"

#include "construction/database/Database.h"
#include "construction/repositories/ConstructionRepository.h"
#include "construction/services/DashboardService.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    //Open existing SQLite database.
    //Creates tables if needed.
    construction::Database database(
        "construction.db"
    );

    //Data access layer
    construction::ConstructionRepository repository(
        database
    );

    //Business logic and analytics
    construction::DashboardService service(
        repository
    );

    //GUI now receives the existing backend objects
    construction::MainWindow mainWindow(
        service,
        repository
    );

    mainWindow.show();

    return application.exec();
}
