#include<iostream>
#include<stack>
#include<vector>
#include<string>

class Screen {

    private:
        std::string name;
        std::vector<Screen> children;
        bool hasChildren;

    public:
        Screen();
        Screen(std::string);
        std::string getName();
        std::vector<Screen> getChildren();
        bool getHasChildren();
};

class App {

    private:
        std::stack<Screen> screens;
        Screen currentScreen;
        std::string hierarchyFilename;

    public:
        App();
        Screen getCurrentScreen();
        std::string getHierarchyFilename();
        bool up(int);
        bool down();
};