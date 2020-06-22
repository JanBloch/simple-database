#include "Database.h"
#include <stdio.h>
void create(Database * db);
void open(Database * db);

const char *  print_type(Config::ColumnType type) {
	switch (type) {
	case Config::ColumnType::INTEGER:
		return "Integer";
	case Config::ColumnType::STRING:
		return "String";
	case Config::ColumnType::BINARY:
		return "Binary";
	}
	return "Unknown";
}

void print_table(Table table) {
	printf("%s\n", table.getName());
	for (int i = 0; i < table.getColumnCount(); i++) {
		Config::Column col = table.getColumn(i);
		printf("%s | %s\t", col.name, print_type(col.type));
	}
	printf("\n");
	for (int i = 0; i < table.getEntryCount(); i++) {
		printf("%s\n", table.getEntry(i).data);
	}
	printf("\n\n");
}


int main() {
	Database db;
	//create(&db);
	open(&db);
	//TableEntry entry;
	//entry.data = (char*)"asdf";
	//db.getTablePtr(0)->addEntry(entry);
	//db.save("database.db");
	for (int i = 0; i < db.tableCount(); i++) {
		print_table(db.getTable(i));
	}
	printf("\n");
	printf("Database: %s\n", db.getName());
}


void open(Database * db) {
	
	(*db).openFromFile("database.db");
}
void create(Database * db) {
	struct Config::Config config;
	struct Config::Table tableOne;
	struct Config::Table tableTwo;
	struct Config::Column tbl1_column1;
	struct Config::Column tbl1_column2;
	struct Config::Column tbl2_column1;
	struct Config::Column tbl2_column2;
	struct Config::Column tbl2_column3;

	tbl1_column1.name = "col1";
	tbl1_column2.name = "col2";
	tbl2_column1.name = "col1";
	tbl2_column2.name = "col2";
	tbl2_column3.name = "col3";
	tbl1_column1.type = Config::ColumnType::INTEGER;
	tbl1_column2.type = Config::ColumnType::STRING;
	tbl2_column1.type = Config::ColumnType::INTEGER;
	tbl2_column2.type = Config::ColumnType::STRING;
	tbl2_column3.type = Config::ColumnType::STRING;

	tableOne.name = "Table One";
	tableOne.columns.push_back(tbl1_column1);
	tableOne.columns.push_back(tbl1_column2);
	tableTwo.name = "Table Two";
	tableTwo.columns.push_back(tbl2_column1);
	tableTwo.columns.push_back(tbl2_column2);
	tableTwo.columns.push_back(tbl2_column3);

	config.tables.push_back(tableOne);
	config.tables.push_back(tableTwo);
	config.name = "the_db";

	(*db).create("database.db", config);
}