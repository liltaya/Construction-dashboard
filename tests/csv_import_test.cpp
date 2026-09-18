#include "construction/csv/CsvImporter.h"

#include <gtest/gtest.h>

#include <QDir>
#include <QFile>
#include <QTemporaryDir>
#include <QTextStream>

namespace {

QString createTemporaryCsv(
    QTemporaryDir& directory,
    const QString& fileName,
    const QString& content
)
{
    const QString path =
        directory.filePath(fileName);

    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return {};
    }

    QTextStream stream(&file);
    stream << content;

    return path;
}

} 
TEST(CsvImporterTest, ImportsValidProject)
{
    QTemporaryDir directory;

    ASSERT_TRUE(directory.isValid());

    const QString csv =
        "id,name,description,location,start_date,end_date,status,budget\n"
        "1,Tower A,Residential tower,Burnaby,2026-01-01,2027-01-01,active,5000000\n";

    const QString path =
        createTemporaryCsv(
            directory,
            "projects.csv",
            csv
        );

    const auto result =
        construction::CsvImporter::importProjects(path);

    ASSERT_TRUE(result.success());
    ASSERT_EQ(result.objects.size(), 1);

    const auto& project =
        result.objects.front();

    EXPECT_EQ(project.id, 1);
    EXPECT_EQ(project.name, "Tower A");
    EXPECT_EQ(project.status, "active");
    EXPECT_DOUBLE_EQ(project.budget, 5000000.0);
}
TEST(CsvImporterTest, RejectsInvalidProjectStatus)
{
    QTemporaryDir directory;

    ASSERT_TRUE(directory.isValid());

    const QString csv =
        "id,name,description,location,start_date,end_date,status,budget\n"
        "1,Tower A,Residential tower,Burnaby,2026-01-01,2027-01-01,banana,5000000\n";

    const QString path =
        createTemporaryCsv(
            directory,
            "projects.csv",
            csv
        );

    const auto result =
        construction::CsvImporter::importProjects(path);

    EXPECT_FALSE(result.success());
    EXPECT_TRUE(result.objects.empty());
    EXPECT_FALSE(result.errors.empty());
}
TEST(CsvImporterTest, RejectsNegativeProjectBudget)
{
    QTemporaryDir directory;

    ASSERT_TRUE(directory.isValid());

    const QString csv =
        "id,name,description,location,start_date,end_date,status,budget\n"
        "1,Tower A,Residential tower,Burnaby,2026-01-01,2027-01-01,active,-5000\n";

    const QString path =
        createTemporaryCsv(
            directory,
            "projects.csv",
            csv
        );

    const auto result =
        construction::CsvImporter::importProjects(path);

    EXPECT_FALSE(result.success());
    EXPECT_TRUE(result.objects.empty());
}
TEST(CsvParserTest, HandlesQuotedComma)
{
    QTemporaryDir directory;

    ASSERT_TRUE(directory.isValid());

    const QString csv =
        "id,name,description,location,start_date,end_date,status,budget\n"
        "1,Tower A,\"Concrete, steel and glass\",\"Burnaby, BC\",2026-01-01,2027-01-01,active,5000000\n";

    const QString path =
        createTemporaryCsv(
            directory,
            "projects.csv",
            csv
        );

    const auto result =
        construction::CsvImporter::importProjects(path);

    ASSERT_TRUE(result.success());
    ASSERT_EQ(result.objects.size(), 1);

    EXPECT_EQ(
        result.objects.front().description,
        "Concrete, steel and glass"
    );

    EXPECT_EQ(
        result.objects.front().location,
        "Burnaby, BC"
    );
}
TEST(CsvImporterTest, AllowsCostWithoutTask)
{
    QTemporaryDir directory;

    ASSERT_TRUE(directory.isValid());

    const QString csv =
        "id,project_id,task_id,category,description,amount,entry_date\n"
        "1,1,,permit,Building permit,15000,2026-01-01\n";

    const QString path =
        createTemporaryCsv(
            directory,
            "costs.csv",
            csv
        );

    const auto result =
        construction::CsvImporter::importCostEntries(path);

    ASSERT_TRUE(result.success());
    ASSERT_EQ(result.objects.size(), 1);

    EXPECT_FALSE(
        result.objects.front().taskId.has_value()
    );

    EXPECT_DOUBLE_EQ(
        result.objects.front().amount,
        15000.0
    );
}
TEST(CsvImporterTest, RejectsWrongHeader)
{
    QTemporaryDir directory;

    ASSERT_TRUE(directory.isValid());

    const QString csv =
        "name,id,budget\n"
        "Tower A,1,5000000\n";

    const QString path =
        createTemporaryCsv(
            directory,
            "projects.csv",
            csv
        );

    const auto result =
        construction::CsvImporter::importProjects(path);

    EXPECT_FALSE(result.success());
    EXPECT_TRUE(result.objects.empty());
}
