#ifndef AUTH_H
#define AUTH_H

#include <string>
#include "user.h"

class Auth {
public:
    bool createAccount(const std::string& username,
                       const std::string& password);

    bool login(const std::string& username,
               const std::string& password,
               User& user);
};

#endif