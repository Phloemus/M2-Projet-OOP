/*

   Author: Brieuc Quemeneur - 2022
   Compilation: g++ -o main main.cpp classes.o -ljsoncpp

*/


#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<jsoncpp/json/json.h>

#include "classes.hpp"

int main() {
    std::cout << "Cabinet de radiologie" << std::endl;

    std::string name;
    std::string password;

    // Displaying the authentification prompt
    std::cout << "Indiquez votre nom" << std::endl;
    std::cin >> name;
    std::cout << "Indiquez votre mot de passe" << std::endl;
    std::cin >> password;

    // Creation of the User class
    User user = User(name, password);

    // Authentification
    if(user.authenticate()) {
        
    }

    // Upgrade the user

    // Unlock its actions depending on its role
    
    return 0;
}