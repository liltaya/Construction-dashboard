#include "construction/MainWindow.h"
#include "construction/database/Database.h"
#include "construction/repositories/ConstructionRepository.h"
#include "construction/services/DashboardService.h"
#include "construction/utils/Logger.h"

#include <QApplication>
#include <QMessageBox>
#include <QDir>

#include <exception>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    application.setOrganizationName(
        "ConstructionDashboard"
    );

    application.setApplicationName(
        "ConstructionDashboard"
    );

    auto& logger =
        construction::Logger::instance();

    logger.info("Application starting");

    try
    {
        construction::Database database(
            QDir::current().filePath(
                "construction.db"
            )
        );

        logger.info("Database initialized");

        construction::ConstructionRepository repository(
            database
        );

        construction::DashboardService service(
            repository
        );

        construction::MainWindow mainWindow(
            service,
            repository
        );

        mainWindow.show();

        logger.info("Main window opened");

        const int result = application.exec();

        logger.info("Application closed");

        return result;
    }
    catch (const std::exception& exception)
    {
        const QString errorMessage =
            QString::fromUtf8(exception.what());

        logger.error(errorMessage);

        QMessageBox::critical(
            nullptr,
            "Application Error",
            "Failed to start Construction Dashboard:\n\n"
            + errorMessage
        );

        return 1;
    }
}
