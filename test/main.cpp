#include<iostream>
#include<stack>
#include<vector>
#include<string>

#include "app.h"

int main() {
    std::cout << "Hello " << std::endl; 

    App app = App();
    std::cout << "Vous etes sur l'écran : " << app.getCurrentScreen().getName() << std::endl;

    std::cout << app.down() << std::endl;
    std::cout << app.up(0) << std::endl;


    return 0;
}