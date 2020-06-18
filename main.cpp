#include "Database.h"
#include <stdio.h>
void create(Database * db);
void open(Database * db);

void print_table(Table table) {
	printf("%s\n", table.getName());
	for (int i = 0; i < table.getColumnCount(); i++) {
		printf("%s\t", table.getColumn(i).name);
	}
	printf("\n\n");
}

int main() {
	Database db;
	create(&db);
	open(&db);
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