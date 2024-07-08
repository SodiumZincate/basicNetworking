#include<iostream>
#include<sstream>
#include<string.h>
#include<sqlite3.h>

static int callback(void* data, int argc, char **argv, char** azcolName);

void query(sqlite3 *db);

int initDatabase(std::string, std::string, std::string);