#include <QCoreApplication>
#include <QStandardPaths>

#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    QCoreApplication application(argc, argv);

    application.setOrganizationName(
        "ConstructionDashboard"
    );

    application.setApplicationName(
        "ConstructionDashboardTests"
    );

    QStandardPaths::setTestModeEnabled(true);

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
