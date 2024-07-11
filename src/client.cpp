#include <httplib.h>
#include <iostream>
#include <sqlite3.h>
#include <filesystem>

using namespace std;

int main(int argc, char *argv[]) {
	httplib::Client cli("0.0.0.0", 8080);
	
	if (strcmp(argv[1], "insert") == 0){
		if (auto res = cli.Post("/login/insert?=login.db", "Prasiddha\nprasiddhapokh@gmail.com\n12345678", "text/plain")) {
			cout << res->status << endl;
			cout << res->get_header_value("Content-Type") << endl;
		}
		else {
			cout << "error code: " << res.error() << std::endl;
		}
	}
	else if(strcmp(argv[1], "delete") == 0){
		if (auto res = cli.Post("/login/delete", "Prasiddha\nprasiddhapokh@gmail.com\n12345678", "text/plain")) {
			cout << res->status << endl;
			cout << res->get_header_value("Content-Type") << endl;
		}
		else {
			cout << "error code: " << res.error() << std::endl;
		}
	}
	else if(strcmp(argv[1], "query") == 0){
		if (auto res = cli.Post("/login/query", "Prasiddha\nprasiddhapokh@gmail.com\n12345678", "text/plain")) {
			cout << res->status << endl;
			cout << res->get_header_value("Content-Type") << endl;
		}
		else {
			cout << "error code: " << res.error() << std::endl;
		}
	}
	else if(strcmp(argv[1], "team") == 0){
		if (auto res = cli.Post("/team/insert", "1\n1\n1\nBrazil\n1\n0\n0\n0\n0\n0\n0\n0", "text/plain")) {
			cout << res->status << endl;
			cout << res->get_header_value("Content-Type") << endl;
		}
		else {
			cout << "error code: " << res.error() << std::endl;
		}
	}
  return 0;
}