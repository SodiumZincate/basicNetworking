#include "database.h"

using namespace std;

// Callback function is called for each row
// data = database, argc = no. of columns in a row,
// argv = array of strings where each string is the value of a column in the row
// azcolName = array of strings where each string is the name of the column
static int callback(void* data, int argc, char **argv, char** azcolName){
	int i;
	for(i=0; i<argc; i++){
		cout << azcolName[i] << " = " << argv[i] << endl; 
	}
	cout << endl;
	return 0;
}

void query(sqlite3 *db){
	char *errMsg;
	string sqlQuery = "SELECT * FROM DATA";
	if(sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &errMsg) != SQLITE_OK){
		cerr << "SQL Error: " << errMsg << endl;
		sqlite3_free(errMsg);
	}
}

int main(int argc, char *argv[])
// int initDatabase(string username, string email, string password)
{
	sqlite3 *db;
	int exit = 0;
	char *errMsg;

	stringstream ss1;
	ss1 << "CREATE TABLE DATA"
		<< "("
        << "LID INTEGER PRIMARY KEY AUTOINCREMENT, "
		<< "USERNAME TEXT NOT NULL,"
		<< "EMAIL TEXT NOT NULL,"
		<< "PASSWORD TEXT NOT NULL"
		<< ")";

	std::string sqlCreate;
	if(strcmp(argv[1], "login") == 0)
		sqlCreate = ss1.str();
	// cout << sqlMsg << endl;

	exit = sqlite3_open("uploads/login.db", &db);
	if(exit){
		cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
		return 1;
	}
	else{
		cout << "Database opened successfully" << endl;
	}

	exit = sqlite3_exec(db, sqlCreate.c_str(), NULL, 0, &errMsg);
	if(exit!=SQLITE_OK){
		cerr << "Error creating table" << endl;
		cerr << errMsg << endl;
		sqlite3_free(errMsg);
	}
	else{
		cout << "Table created successfully" << endl;
	}
	
	sqlite3_close(db);
	return 0;
}