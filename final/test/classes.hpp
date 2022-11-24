#include<iostream>
#include<vector>


class Page {
    private:
        std::string text;
    public:
        Page(std::string);
};

class Book {

    private:
        std::vector<Page> pages;

    public:
        Book();
        void addPage(Page);
        int countPages();
};