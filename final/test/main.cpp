#include<iostream>
#include<vector>

#include "classes.hpp"

int main() {

    Book b = Book();
    Page p1 = Page("Bonjour");
    Page p2 = Page("Je suis Brieuc");

    b.addPage(p1); b.addPage(p2);
    std::cout << "nb pages dans le livre : " << b.countPages() << std::endl;
    
    return 0;
}