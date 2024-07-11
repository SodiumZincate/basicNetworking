#pragma once

#include <httplib.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sqlite3.h>
#include <thread>

using namespace httplib;
using namespace std;

struct QueryResult{
	std::vector<string> result;
};

extern QueryResult QR1;

static int callback(void* data, int argc, char **argv, char** azcolName);

void query(sqlite3 *db);

void insertDatabaseTeam(string, string);

void insertDatabase(string, string);

void deleteDatabase(string, string);

void queryDatabase(string, string, Response&);