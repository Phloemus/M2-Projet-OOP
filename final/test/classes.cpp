#include<iostream>
#include<vector>

#include "classes.hpp"

Page::Page(std::string text) { this->text = text; }

Book::Book() {}
void Book::addPage(Page p) {
    this->pages.push_back(p);
}
int Book::countPages() {
    return this->pages.size();
}