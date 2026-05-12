#include "Auth.h"
#include <fstream>

using namespace std;

const string FILE_NAME = "password.txt";

bool Auth::createAccount(const string& username, const string& password) {
    ofstream file(FILE_NAME, ios::app);
    if (!file) return false;

    file << username << " " << password << "\n";
    return true;
}

bool Auth::login(const string& username,
                 const string& password,
                 User& user) {

    ifstream file(FILE_NAME);
    if (!file.is_open()) return false;

    string u, p;

    while (file >> u >> p) {
        if (u == username && p == password) {
            user.setUsername(username);
            return true;
        }
    }

    return false;
}