#pragma once
#include <vector>

namespace Config {
	enum ColumnType {
		INTEGER = 0,
		STRING = 1,
		BINARY = 2
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
public: 
	char* data;
};
class Table {
public:
	void addColumn(struct Config::Column col);
	void setName(char* name);
	void addEntry(TableEntry entry);
	TableEntry getEntry(int index);
	int getColumnCount();
	int getEntryCount();
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
	void save(const char* filename);
	Table getTable(int index);
	static int size(Config::Column col);
	static int size(Config::Table table);
	static int size(Table table);
	int tableCount();
	void addTable(Table table);
	static int headerSize(Config::Table table);
	static int headerSize(Table table);
	char* getName();
private:
	char* name;
	std::vector<Table> tables;
};
