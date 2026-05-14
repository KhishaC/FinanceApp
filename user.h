
#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;

public:
    User();
    User(const std::string& name);

    std::string getUsername() const;
    void setUsername(const std::string& name);
};

#endif