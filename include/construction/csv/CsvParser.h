#pragma once

#include <QString>
#include <QStringList>

#include <vector>

namespace construction {

class CsvParser
{
public:
	using Row = QStringList;

	struct Result
{
	std::vector<Row> rows;
	QString error;

	bool success() const
{
	return error.isEmpty();
}
};

static Result parseFile(const QString& filePath);

private:
	static Row parseLine(const QString& line);
};

}
