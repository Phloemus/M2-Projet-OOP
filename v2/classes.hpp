
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<jsoncpp/json/json.h>


class User {

    protected:
        std::string filename = "database/users.json";
        std::string name;
        std::string password;
        int role;

    public:
        User(std::string, std::string);
        ~User();

    protected:
        bool disconnect();

    public:
        bool authenticate();
        User upgrade(); // allow to transform the normal user into a patient, doctor or admin
    
};

class Patient : public User {

    public:
        Patient(std::string, std::string);
        ~Patient();

    public:
        bool authenticate();
        void test();

};
