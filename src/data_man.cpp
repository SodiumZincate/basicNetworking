#include "data_man.h"

// Callback function is called for each row
// data = database, argc = no. of columns in a row,
// argv = array of strings where each string is the value of a column in the row
// azcolName = array of strings where each string is the name of the column
static int callback(void* data, int argc, char **argv, char** azcolName){
	int i;
	for(i=0; i<argc; i++){
		std::cout << azcolName[i] << " = " << argv[i] << std::endl;
		QR1.result.push_back(argv[i]);
	}
	std::cout << std::endl;
	return 0;
}

void query(sqlite3 *db){
	char *errMsg;
	string sqlQuery = "SELECT * FROM TEAM";
	if(sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &errMsg) != SQLITE_OK){
		cerr << "SQL Error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
}

void insertDatabaseTeam(string cli_req, string file){
	sqlite3 *db;
	int exit = 0;
	char *errMsg;

	std::vector<string> string_list;
	std::string token;
	istringstream tokenStream(cli_req);
	while(getline(tokenStream, token, '\n')){
		string_list.push_back(token);
	}

	exit = sqlite3_open(file.c_str(), &db);
	std::cout << file.c_str() << std::endl;
	if(exit){
		cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
		
	}
	else{
		std::cout << "Database opened successfully" << std::endl;
	}

	string uid = string_list[0];
	string lid = string_list[1];
	string position = string_list[2];
	string team_name = string_list[3];
	string win = string_list[4];
	string loss = string_list[5];
	string draw = string_list[6];
	string ga = string_list[7];
	string gd = string_list[8];
	string gf = string_list[9];
	string point = string_list[10];

	stringstream ss;
	ss << "INSERT INTO TEAM(UID,LID,POSITION,TNAME,WIN,LOSS,DRAW,GA,GD,GF,POINTS) VALUES"
	<< "("
	<< "'" << uid << "',"
	<< "'" << lid << "',"
	<< "'" << position << "',"
	<< "'" << team_name << "',"
	<< "'" << win << "',"
	<< "'" << loss << "',"
	<< "'" << draw << "',"
	<< "'" << ga << "',"
	<< "'" << gd << "',"
	<< "'" << gf << "',"
	<< "'" << point << "'"
	<< ")";

	string sqlInsert = ss.str();
	exit = sqlite3_exec(db, sqlInsert.c_str(), NULL, 0, &errMsg);
	if(exit!=SQLITE_OK){
		cerr << "Error inserting data" << std::endl;
		cerr << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
	else{
		std::cout << "Data inserted successfully" << std::endl;
	}

	std::cout << "Table Contents: " << std::endl;
	query(db);

	sqlite3_close(db);
}

void insertDatabase(string cli_req, string file)
{
	sqlite3 *db;
	int exit = 0;
	char *errMsg;

	std::vector<string> string_list;
	std::string token;
	istringstream tokenStream(cli_req);
	while(getline(tokenStream, token, '\n')){
		string_list.push_back(token);
	}

	string username = string_list[0];
	string email = string_list[1];
	string password = string_list[2];

	exit = sqlite3_open(file.c_str(), &db);
	std::cout << file.c_str() << std::endl;
	if(exit){
		cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
		std::exit(1);
	}
	else{
		std::cout << "Database opened successfully" << std::endl;
	}

	stringstream ss;
	int LID = 1;
	ss << "INSERT INTO DATA(USERNAME,EMAIL,PASSWORD) VALUES"
	<< "("
	<< "'" << username << "',"
	<< "'" << email << "',"
	<< "'" << password << "'"
	<< ")";

	string sqlInsert = ss.str();
	exit = sqlite3_exec(db, sqlInsert.c_str(), NULL, 0, &errMsg);
	if(exit!=SQLITE_OK){
		cerr << "Error inserting data" << std::endl;
		cerr << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
	else{
		std::cout << "Data inserted successfully" << std::endl;
	}

	std::cout << "Table Contents: " << std::endl;
	query(db);

	sqlite3_close(db);
	
}

void deleteDatabase(string cli_req, string file)
{
	sqlite3 *db;
	int exit = 0;
	char *errMsg;

	std::vector<string> string_list;
	std::string token;
	istringstream tokenStream(cli_req);
	while(getline(tokenStream, token, '\n')){
		string_list.push_back(token);
	}

	string username = string_list[0];
	string email = string_list[1];
	string password = string_list[2];

	exit = sqlite3_open(file.c_str(), &db);
	std::cout << file.c_str() << std::endl;
	if(exit){
		cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
		std::exit(1);
	}
	else{
		std::cout << "Database opened successfully" << std::endl;
	}

	stringstream ss;
	ss << "DELETE FROM DATA WHERE USERNAME"
	<< "="
	<< "'" << username << "'";

	string sqlDelete = ss.str();
	exit = sqlite3_exec(db, sqlDelete.c_str(), NULL, 0, &errMsg);
	if(exit!=SQLITE_OK){
		cerr << "Error deleting data" << std::endl;
		cerr << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
	else{
		std::cout << "Data deleted successfully" << std::endl;
	}

	std::cout << "Table Contents: " << std::endl;
	query(db);
	
	sqlite3_close(db);
	
}

void queryDatabase(string cli_req, string file, Response &res)
{
	sqlite3 *db;
	int exit = 0;
	char *errMsg;

	std::vector<string> string_list;
	std::string token;
	istringstream tokenStream(cli_req);
	while(getline(tokenStream, token, '\n')){
		string_list.push_back(token);
	}

	string username = string_list[0];

	exit = sqlite3_open(file.c_str(), &db);
	std::cout << file.c_str() << std::endl;
	if(exit){
		cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
		std::exit(1);
	}
	else{
		std::cout << "Database opened successfully" << std::endl;
	}

	stringstream ss;
	ss << "SELECT LID, USERNAME, EMAIL, PASSWORD FROM DATA WHERE USERNAME"
	<< "="
	<< "'" + username + "'";

	QR1.result.clear();
	
	string sqlQuery = ss.str();
	exit = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &errMsg);
	if(exit!=SQLITE_OK){
		cerr << "Error Querying Data" << std::endl;
		cerr << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
	else{
		std::cout << "Data Queried successfully" << std::endl;
		// std::cout << QR1.result[1] << std::endl;
		stringstream content;
		for(string &c : QR1.result){
			content << c;
			content << "\n";
		}
		string line;
		bool userExists = false;
		while(getline(content, line, '\n')){
			if(strcmp(line.c_str(), username.c_str()) == 0){
				userExists = true;
				break;
			}
		}
		if(userExists){
			std::cout << "The user: " << username << " exists\n" << std::endl;
			res.set_content(content.str(), "text/plain");
		}
		else{
			std::cout << "The user: " << username << " doesn't exist\n" << std::endl;
			res.set_content("\n\n\n", "text/plain");
		}
	}

	// std::cout << "Table Contents: " << std::endl;
	// query(db);
	
	sqlite3_close(db);
}
