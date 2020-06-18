#pragma once
#include <vector>

namespace Config {
	enum ColumnType {
		INTEGER,
		STRING,
		BINARY
	};
	struct Column {
		const char* name;
		ColumnType type;
	};
	struct Table {
		std::vector<struct Column> columns;
		const char* name;
	};
	struct Config {
		std::vector<struct Table> tables;
		const char* name;
	};
}
class TableEntry {

};
class Table {
public:
	void addColumn(struct Config::Column col);
	void setName(char* name);
	int getColumnCount();
	struct Config::Column getColumn(int index);
	char* getName();
private:
	char* name;
	std::vector<struct Config::Column> columns;
	std::vector<TableEntry> entries;
};
class Database {
public:
	void openFromFile(const char* filename);
	void addTable(char* data, size_t start, size_t end);
	void addTableHeader(char* data, size_t start, size_t end, Table* table);
	void addTableColumns(char* data, size_t start, size_t end, Table* table);
	void addTableColumn(char* data, size_t start, size_t end, Table* table);
	void addTableEntry(char* data, size_t start, size_t end, Table* table);
	void create(const char* filename, struct Config::Config config);
	Table getTable(int index);
	int size(Config::Table table);
	int tableCount();
	void addTable(Table table);
	int headerSize(Config::Table table);
	char* getName();
private:
	char* name;
	std::vector<Table> tables;
};
