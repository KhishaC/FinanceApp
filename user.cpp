#include "User.h"

User::User() : username("") {}

User::User(const std::string& name) : username(name) {}

std::string User::getUsername() const {
    return username;
}

void User::setUsername(const std::string& name) {
    username = name;
}