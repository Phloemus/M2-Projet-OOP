
#include<iostream>
#include<string>
#include<vector>

#include "classes.h"

// g++ -c classes.cpp

//  Patient definitions

Patient::Patient() {}

Patient::Patient(int id, std::string name) {
    this->id = id;
    this->name = name;
}

int Patient::getId() {
    return id;
}

std::string Patient::getName() {
    return name;
}

// Date definition
Date::Date() {
    this->day = 1;
    this->month = 1;
    this->year = 1970;
}

Date::Date(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}

int Date::getDay() {
    return day;
}
int Date::getMonth() {
    return month;
}
int Date::getYear() {
    return year;
}
std::string Date::getStringDate() {
    std::string date;
    date = std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    return date;
}

// Report definition

Report::Report() {}

Report::Report(std::string password, std::string content, std::string authorName) {
    this->password = password;
    this->content = content;
    this->authorName = authorName;
}

std::string Report::getPassword() {
    return password;
}

std::string Report::getContent() {
    return content;
}

std::string Report::getAuthorName() {
    return authorName;
}

// Picture definition

Picture::Picture() {}

Picture::Picture(int id, std::string filename) {
    this->id;
    this->filename = filename;
    this->report = Report("", "", "NONE");
}

Picture::Picture(int id, std::string filename, Report report) {
    this->id = id;
    this->filename = filename;
    this->report = report;
}

int Picture::getId() {
    return id;
}

std::string Picture::getFilename() {
    return filename;
}

// Private function (utility)
bool Picture::checkPassword(std::string password) {
    if((this->report.getPassword() == "") || (this->report.getPassword() == password)) {
        return true;
    }
    return false;
}

// Public function
Report Picture::getReport(std::string password) {
    if(this->checkPassword(password)) {
        return report;
    }
    Report emptyReport("", "", "INVALID");
    return emptyReport;
}

bool Picture::setReport(Report report) {
    if(this->report.getAuthorName() == "NONE") {
        this->report = report;
        return true;
    }
    return false;
}

// Radiography definition

Radiography::Radiography(int id, std::string type, bool state, Patient patient, Date date) {
    this->id = id;
    this->type = type;
    this->state = state;
    this->patient = patient;
    this->date = date;
}

int Radiography::getId() {
    return id;
}
std::string Radiography::getType() {
    return type;
}
bool Radiography::getState() {
    return state;
}
Patient Radiography::getPatient() {
    return patient;
}
Date Radiography::getDate() {
    return date;
}
std::vector<Picture>& Radiography::getPictures() {
    return pictures;
}
void Radiography::addPicture(Picture picture) {
    this->pictures.push_back(picture);
}

// App

App::App() {};
/*
void App::loadRadiographies(std::string filename);
bool App::addRadiography(Radiography);
bool App::deleteRadiography(Radiography);
bool App::saveRadiographies(std::string filename);*/