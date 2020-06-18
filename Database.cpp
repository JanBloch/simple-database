#include "Database.h"
#include <fstream>
#include <iostream>

void copy(char* target, char* arr, size_t start, size_t size) {
	for (size_t i = start; i < start + size; i++) {
		target[i - start] = arr[i];
	}
}
void print_arr(char arr[], size_t arr_length) {
	printf("[");
	for (int i = 0; i < arr_length; i++) {
		const char* str = (i == arr_length - 1) ? "%d]\n" : "%d, ";
		printf(str, (int)arr[i]);
	}
}
char* intToCharBuffer(int val) {
	char* out = (char*)malloc(sizeof(int));
	if (out != NULL) {
		memcpy(out, &val, sizeof(int));
	}
	return out;
}
int charBufferToInt(char* buffer) {
	/*char* debug = (char*)malloc(sizeof(int));
	memcpy(debug, buffer, sizeof(int));
	print_arr(debug);*/
	int out = 0;
	memcpy(&out, buffer, sizeof(int));
	return out;
}

void Database::openFromFile(const char* filename) {
	std::ifstream dbFile(filename, std::ios::binary);
	int i = 0;
	int start = dbFile.tellg();
	dbFile.seekg(0, std::ios::end);
	int end = dbFile.tellg();
	int size = end - start;
	dbFile.seekg(0, std::ios::beg);
	char* arr = new char[size];

	while (!dbFile.eof() && i < size) {
		dbFile.get(arr[i++]);
	}
	arr[size] = '\0';
	int nameSize = 0;
	nameSize = charBufferToInt(arr);
	char* name = new char[nameSize];
	for (size_t j = sizeof(int); j < nameSize + sizeof(int); j++) {
		name[j - sizeof(int)] = arr[j];
	}
	for (size_t j = nameSize + sizeof(int); j < size; j++) {
		this->addTable(arr, j + 1, j + arr[j]);
		j += arr[j];
	}
	name[arr[0]] = '\0';
	this->name = name;
}

void Database::addTable(char* data, size_t start, size_t end) {
	char* tableData = new char[end - start];
	memcpy(tableData, data + start, end - start + 1);
	if (strlen(tableData) > end - start + 1) {
		tableData[end - start + 1] = '\0';
	}
	Table table;
	addTableHeader(tableData, 1, tableData[0], &table);
	for (int i = tableData[0]; i < strlen(tableData); i++) {
		TableEntry entry;
		addTableEntry(tableData, i + 1, i + tableData[i], &table);
		i += tableData[i];
	}
	tables.push_back(table);
}

void Database::addTableHeader(char* data, size_t start, size_t end, Table* table) {
	char* tableHeader = new char[end - start];
	
	memcpy(tableHeader, data + start, end - start + 1);
	int nameSize = charBufferToInt(tableHeader);
	char* name = new char[nameSize];
	for (int i = sizeof(int); i < nameSize + sizeof(int); i++) {
		name[i - sizeof(int)] = tableHeader[i];
	}
	name[nameSize] = '\0';
	table->setName(name);
	addTableColumns(tableHeader, nameSize + sizeof(int), end - start , table);
}
void Database::addTableColumns(char* data, size_t start, size_t end, Table* table) {
	char* columns = new char[end - start];
	memcpy(columns, data + start, end - start + 1);
	columns[end - start + 1] = '\0';
	for (int i = 0; i < strlen(columns); i++) {
		addTableColumn(columns, i + 1, columns[i] + i, table);
		i += columns[i];
	}
}
void Database::addTableColumn(char* data, size_t start, size_t end, Table* table) {
	char* column = new char[end - start];
	memcpy(column, data + start, end - start + 1);
	column[end - start + 1] = '\0';
	struct Config::Column col;
	col.type = Config::ColumnType::BINARY;
	col.name = column;
	table->addColumn(col);
}
void Table::addColumn(struct Config::Column col) {
	columns.push_back(col);
}
void Table::setName(char* name) {
	this->name = name;
}
int Table::getColumnCount() {
	return columns.size();
}
Config::Column Table::getColumn(int index) {
	return columns[index];
}
char* Table::getName() {
	return name;
}
void Database::addTableEntry(char* data, size_t start, size_t end, Table* table) {
	char* tableEntry = new char[end - start];
	memcpy(tableEntry, data + start, end - start + 1);
}


void Database::addTable(Table table) {
	this->tables.push_back(table);
}
void Database::create(const char* filename, Config::Config config) {
	std::ofstream file(filename, std::ios::binary);
	file.write(intToCharBuffer(strlen(config.name)), sizeof(int));
	file << config.name;
	for (int i = 0; i < config.tables.size(); i++) {
		file << (char)size(config.tables[i]);
		file << (char)headerSize(config.tables[i]);
		file.write(intToCharBuffer(strlen(config.tables[i].name)), sizeof(int));
		file << config.tables[i].name;
		for (int j = 0; j < config.tables[i].columns.size(); j++) {
			file << (char)strlen(config.tables[i].columns[j].name);
			file << config.tables[i].columns[j].name;
		}
	}
	file.close();
}

Table Database::getTable(int index) {
	return tables[index];
}


int Database::size(Config::Table table) {
	int size = 1 + sizeof(int) + strlen(table.name);
	for (int i = 0; i < table.columns.size(); i++) {
		size += strlen(table.columns[i].name) + 1;
	}
	return size;
}

int Database::tableCount() {
	return tables.size();
}

int Database::headerSize(Config::Table table) {
	int size = sizeof(int) + strlen(table.name);
	for (int i = 0; i < table.columns.size(); i++) {
		size += strlen(table.columns[i].name) + 1;
	}
	return size;
}
char* Database::getName() {
	return this->name;
}