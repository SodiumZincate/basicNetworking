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

// void query(sqlite3 *db){
// 	char *errMsg;
// 	string sqlQuery = "SELECT * FROM DATA";
// 	if(sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &errMsg) != SQLITE_OK){
// 		cerr << "SQL Error: " << errMsg << endl;
// 		sqlite3_free(errMsg);
// 	}
// }

int main(int argc, char *argv[])
// int initDatabase(string username, string email, string password)
{
	sqlite3 *db;
	int exit = 0;
	char *errMsg;

	stringstream ss1;
	ss1 << "CREATE TABLE USER"
		<< "("
        << "UID INTEGER PRIMARY KEY AUTOINCREMENT, "
		<< "USERNAME TEXT NOT NULL,"
		<< "EMAIL TEXT NOT NULL,"
		<< "PASSWORD TEXT NOT NULL"
		<< ")";
	stringstream ss2;
	ss2 << "CREATE TABLE LEAGUE"
		<< "("
        << "LID INTEGER PRIMARY KEY AUTOINCREMENT, "
        << "UID INTEGER NOT NULL, "
		<< "LNAME TEXT NOT NULL"
		<< ")";
	stringstream ss3;
	ss3 << "CREATE TABLE TEAM"
		<< "("
        << "TID INTEGER PRIMARY KEY AUTOINCREMENT, "
        << "UID INTEGER NOT NULL, "
        << "LID INTEGER NOT NULL, "
		<< "POSITION INTEGER NOT NULL,"
		<< "TNAME TEXT NOT NULL,"
		<< "WIN INTEGER NOT NULL,"
		<< "LOSS INTEGER NOT NULL,"
		<< "DRAW INTEGER NOT NULL,"
		<< "GF INTEGER NOT NULL,"
		<< "GA INTEGER NOT NULL,"
		<< "GD INTEGER NOT NULL,"
		<< "POINTS INTEGER NOT NULL"
		<< ")";

	std::string sqlCreateUser;
	sqlCreateUser = ss1.str();
	std::string sqlCreateLeague;
	sqlCreateLeague = ss2.str();
	std::string sqlCreateTeam;
	sqlCreateTeam = ss3.str();

	exit = sqlite3_open("uploads/leaguedata.db", &db);
	if(exit){
		cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
		return 1;
	}
	else{
		cout << "Database opened successfully" << endl;
	}

	exit = sqlite3_exec(db, sqlCreateUser.c_str(), NULL, 0, &errMsg);
	if(exit!=SQLITE_OK){
		cerr << "Error creating user table" << endl;
		cerr << errMsg << endl;
		sqlite3_free(errMsg);
	}
	else{
		cout << "User Table created successfully" << endl;
	}
	exit = sqlite3_exec(db, sqlCreateLeague.c_str(), NULL, 0, &errMsg);
	if(exit!=SQLITE_OK){
		cerr << "Error creating league table" << endl;
		cerr << errMsg << endl;
		sqlite3_free(errMsg);
	}
	else{
		cout << "League Table created successfully" << endl;
	}
	exit = sqlite3_exec(db, sqlCreateTeam.c_str(), NULL, 0, &errMsg);
	if(exit!=SQLITE_OK){
		cerr << "Error creating team table" << endl;
		cerr << errMsg << endl;
		sqlite3_free(errMsg);
	}
	else{
		cout << "Team Table created successfully" << endl;
	}
	
	sqlite3_close(db);
	return 0;
}