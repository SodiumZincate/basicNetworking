#include "../cpp-httplib/httplib.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>

using namespace httplib;
using namespace std;

auto form_html = R"(
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Form with Button</title>
    </head>
    <body>
        <form action="/download" method="get">
            <h1>Hello</h1>
            <input type="text" name="filename" placeholder="Enter filename"/>
            <button type="submit">Download File</button>
        </form>
        <form action="/files" method="get">
            <button type="submit">View All Files</button>
        </form>
    </body>
    </html>
)";

void run_server() {
    Server svr;
    string upload_dir = "./uploads";

    if (!filesystem::exists(upload_dir)) {
        filesystem::create_directory(upload_dir);
    }

    svr.Get("/", [](const Request &req, Response &res) {
        res.set_content(form_html, "text/html");
    });

    svr.Get("/files", [upload_dir](const Request &req, Response &res) {
        string content;
        for (const auto &entry : filesystem::directory_iterator(upload_dir)) {
            if (entry.is_regular_file()) {
                ifstream ifs(entry.path(), ios::binary);
                if (!ifs) {
                    cout << "Failed to open file: " << entry.path() << endl;
                    continue;
                }
                string line;
                content += "\n\n=======================================================================\n\n";
                content += entry.path().string();
                content += "\n";
                while (getline(ifs, line)) {
                    content += line + "\n";
                }
                ifs.close();
            } else {
                cout << "Not a regular file" << endl;
                exit(1);
            }
        }
        res.set_content(content, "text/plain");
    });

    svr.Get("/download", [upload_dir](const Request &req, Response &res) {
        string filename = req.get_param_value("filename");
        string filepath = upload_dir + "/" + filename;

        ifstream file(filepath, ios::binary);
        if (file) {
            stringstream buffer;
            buffer << file.rdbuf();
            file.close();

            res.set_content(buffer.str(), "application/octet-stream");
            res.set_header("Content-Disposition", "attachment; filename=" + filename);
            res.status = 200;
        } else {
            res.status = 404;
            res.set_content("File not found", "text/plain");
        }
    });

    cout << "Server is listening on http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
}

void run_client() {
    Client cli("localhost", 8080);

    string upload_dir = "./uploads";
    string download_dir = "./downloads";

    if (!filesystem::exists(download_dir)) {
        filesystem::create_directory(download_dir);
    }

    for (const auto &entry : filesystem::directory_iterator(upload_dir)) {
        if (entry.is_regular_file()) {
            string filename = entry.path().filename().string();
            auto res = cli.Get(("/download?filename=" + filename).c_str());

            if (res && res->status == 200) {
                ofstream outfile(download_dir + "/" + filename, ios::binary);
                outfile.write(res->body.data(), res->body.size());
                cout << "Downloaded file: " << filename << endl;
            } else {
                cerr << "Failed to download file: " << filename << endl;
                if (res) {
                    cerr << "Status code: " << res->status << endl;
                    cerr << "Response body: " << res->body << endl;
                } else {
                    cerr << "No response from server" << endl;
                }
            }
        }
    }
}

int main() {
    thread server_thread(run_server);

    this_thread::sleep_for(chrono::seconds(1));

    run_client();

    server_thread.join();
    return 0;
}
