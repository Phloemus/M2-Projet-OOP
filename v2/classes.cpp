
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<jsoncpp/json/json.h>

#include "classes.hpp"

User::User(std::string name, std::string password) { this->name = name; this->password = password; }
User::~User() {}

bool User::authenticate() {

    std::ifstream file(this->filename);
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {

        if(((*it)["name"] == this->name) && ((*it)["password"] == this->password)) {
            this->role = (*it)["role"].asInt();
            std::cout << "you are connected" << std::endl;
            return true;
        }

    }

    std::cout << "password incorrect" << std::endl;
    return false;
}

User User::upgrade() {
    switch(this->role) {
        case 1:
            return Patient(this->name, this->password);
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            break;
    }
    return User(this->name, this->password);
}

bool User::disconnect() {
    std::cout << "you are disconnected" << std::endl;
    return true;
}

/*************************** Patient class ******************************************/

Patient::Patient(std::string name, std::string password) : User(name, password) {}
Patient::~Patient() {}

bool Patient::authenticate() {
    User::authenticate();
    std::cout << "authentification au niveau de Patient" << std::endl;
    return true;
}

void Patient::test() {
    std::cout << "vous etes bien un patient" << std::endl;
}