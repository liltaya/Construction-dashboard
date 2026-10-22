
#include "construction/database/Database.h"
#include "construction/repositories/ConstructionRepository.h"

#include <gtest/gtest.h>

#include <QTemporaryDir>
#include <QSqlQuery>

#include <stdexcept>

using namespace construction;

namespace {

Project sampleProject()
{
    Project project;

    project.id = 1;
    project.name = "Test Tower";
    project.description = "Testing";
    project.location = "Burnaby";
    project.startDate = "2026-01-01";
    project.endDate = "2026-12-31";
    project.status = "active";
    project.budget = 1000000.0;

    return project;
}

}

TEST(DatabaseTest, CreatesTables)
{
    QTemporaryDir temp;
    ASSERT_TRUE(temp.isValid());

    Database database(temp.filePath("test.db"));

    QSqlQuery query(database.connection());

    ASSERT_TRUE(query.exec(
        "SELECT name FROM sqlite_master "
        "WHERE type = 'table' "
        "AND name = 'projects';"
    ));

    EXPECT_TRUE(query.next());
}

TEST(DatabaseTest, InsertAndRead)
{
    QTemporaryDir temp;
    ASSERT_TRUE(temp.isValid());

    Database database(temp.filePath("test.db"));
    ConstructionRepository repo(database);

    repo.insertProject(sampleProject());

    const auto result = repo.findProjectById(1);

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->name, "Test Tower");
    EXPECT_DOUBLE_EQ(result->budget, 1000000.0);
}

TEST(DatabaseTest, UpdateProject)
{
    QTemporaryDir temp;
    ASSERT_TRUE(temp.isValid());

    Database database(temp.filePath("test.db"));
    ConstructionRepository repo(database);

    Project project = sampleProject();

    repo.insertProject(project);

    project.budget = 1200000.0;

    repo.updateProject(project);

    const auto result = repo.findProjectById(1);

    ASSERT_TRUE(result.has_value());

    EXPECT_DOUBLE_EQ(result->budget, 1200000.0);
}

TEST(DatabaseTest, DuplicateIdThrows)
{
    QTemporaryDir temp;
    ASSERT_TRUE(temp.isValid());

    Database database(temp.filePath("test.db"));
    ConstructionRepository repo(database);

    const Project project = sampleProject();

    repo.insertProject(project);

    EXPECT_THROW(
        repo.insertProject(project),
        std::runtime_error
    );
}

TEST(DatabaseTest, NegativeBudgetRejected)
{
    QTemporaryDir temp;
    ASSERT_TRUE(temp.isValid());

    Database database(temp.filePath("test.db"));
    ConstructionRepository repo(database);

    Project project = sampleProject();
    project.budget = -100.0;

    EXPECT_THROW(
        repo.insertProject(project),
        std::runtime_error
    );
}

TEST(DatabaseTest, CountsSafetyIncidents)
{
    QTemporaryDir temp;
    ASSERT_TRUE(temp.isValid());

    Database database(temp.filePath("test.db"));
    ConstructionRepository repo(database);

    repo.insertProject(sampleProject());

    QSqlQuery query(database.connection());

    ASSERT_TRUE(query.exec(R"(
        INSERT INTO incidents (
            id, project_id, title,
            description, severity,
            status, incident_date
        )
        VALUES (
            1, 1, 'Test Incident',
            'Unit test', 'low',
            'resolved', '2026-06-15'
        );
    )"));

    EXPECT_EQ(repo.countIncidentsByProject(1), 1);
}
