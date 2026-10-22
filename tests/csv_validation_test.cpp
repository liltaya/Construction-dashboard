#include "construction/csv/CsvValidator.h"

#include <gtest/gtest.h>

using construction::CsvValidator;

TEST(CsvValidatorTest, AcceptsValidCsv)
{
    const auto result = CsvValidator::validate(
        "id,name,budget\n"
        "1,Tower A,1200000\n"
        "2,Tower B,900000\n"
    );

    EXPECT_TRUE(result.valid);
    EXPECT_EQ(result.rows.size(), 2);
    EXPECT_EQ(result.headers.size(), 3);
}

TEST(CsvValidatorTest, RejectsEmptyFile)
{
    const auto result =
        CsvValidator::validate("");

    EXPECT_FALSE(result.valid);
}

TEST(CsvValidatorTest, RejectsMissingColumn)
{
    const auto result = CsvValidator::validate(
        "id,name,budget\n"
        "1,Tower A\n"
    );

    EXPECT_FALSE(result.valid);
}

TEST(CsvValidatorTest, HandlesQuotedComma)
{
    const auto result = CsvValidator::validate(
        "id,name\n"
        "1,\"Tower A, Phase 2\"\n"
    );

    ASSERT_TRUE(result.valid);
    ASSERT_EQ(result.rows.size(), 1);

    EXPECT_EQ(
        result.rows[0][1],
        "Tower A, Phase 2"
    );
}

TEST(CsvValidatorTest, RejectsUnclosedQuote)
{
    const auto result = CsvValidator::validate(
        "id,name\n"
        "1,\"Tower A\n"
    );

    EXPECT_FALSE(result.valid);
}

TEST(CsvValidatorTest, HandlesEscapedQuotes)
{
    const auto result = CsvValidator::validate(
        "id,name\n"
        "1,\"Tower \"\"A\"\"\"\n"
    );

    ASSERT_TRUE(result.valid);

    EXPECT_EQ(
        result.rows[0][1],
        "Tower \"A\""
    );
}

TEST(CsvValidatorTest, RejectsEmptyHeader)
{
    const auto result = CsvValidator::validate(
        "id,,budget\n"
        "1,Tower A,1200000\n"
    );

    EXPECT_FALSE(result.valid);
}
