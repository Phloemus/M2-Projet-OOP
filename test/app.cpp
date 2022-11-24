#include<iostream>
#include<stack>
#include<vector>
#include<string>

#include "app.h"

// SCREEN CLASS

Screen::Screen() {}

Screen::Screen(std::string name) {
    this->name = name;
}

std::string Screen::getName() {
    return name;
}

std::vector<Screen> Screen::getChildren() {
    return children;
}

bool Screen::getHasChildren() {
    return hasChildren;
}

// APP CLASS

App::App() {
    Screen mainScreen = Screen("main screen");
    this->hierarchyFilename = "screens/hierarchy.json";
    this->currentScreen = mainScreen;
    this->screens.push(mainScreen);
}


Screen App::getCurrentScreen() {
    return currentScreen;
}

std::string App::getHierarchyFilename() {
    return hierarchyFilename;
}

bool App::up(int id) {
    if((id >= 0) && (currentScreen.getChildren().size() != 0) && (currentScreen.getChildren().size() >= id)) {
        currentScreen = currentScreen.getChildren().at(id);
        screens.push(currentScreen);
        return true;
    }
    return false;
}

bool App::down() {
    if(screens.size() > 1) {
        screens.pop();
        currentScreen = screens.top();
        return true;
    }
    return false;
}
