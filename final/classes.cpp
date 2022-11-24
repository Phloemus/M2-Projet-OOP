
/*

    compilation: g++ -c classes.cpp -ljsoncpp

*/

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<memory>
#include<jsoncpp/json/json.h>

#include "classes.hpp"

/****** Date Class Definition *****************************************************/

Date::Date() { this->day = 1; this->month = 1; this->year = 1970; }
Date::Date(int d, int m, int y) { day = d; month = m; year = y; }

int Date::getDay() { return day; }
int Date::getMonth() { return month; }
int Date::getYear() { return year; }

std::string Date::getStringDate() {
    std::string date;
    date = std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    return date;
}

/****** Report Class Definition ***************************************************/

Report::Report() {}
Report::Report(int id, std::string content) { this->id = id; this->content = content; }

std::string Report::getContent() { return content; }

/****** Picture Class Definiton ****************************************************/

Picture::Picture() {}
Picture::Picture(int id, std::string filename) { this->id = id; this->filename = filename; }

int Picture::getId() { return id; }
std::string Picture::getFilename() { return filename; }

/****** Radiography class Definition ***********************************************/

Radiography::Radiography() {}
Radiography::Radiography(int id, std::string type, std::string state, int patientId, int doctorId, Date date) { 
    this->id = id;
    this->type = type;
    this->state = state;
    this->patientId = patientId;
    this->doctorId = doctorId;
    this->date = date;

    // Load the pictures from json
    std::ifstream pictureJsonFile("data/pictures.json");
    Json::Value pictureValue;
    Json::Reader pictureReader;

    pictureReader.parse(pictureJsonFile, pictureValue);

    // empty the picture vector 
    this->pictures.clear();

    // reload the whole picture vector with fresh content
    for(Json::Value::iterator it = pictureValue.begin(); it != pictureValue.end(); it++) {

        if(this->id == (*it)["radioId"].asInt()) {
            //TODO : Still have a problem with the first id which is not injected correctly to the Picture instance
            Picture p = Picture((*it)["id"].asInt(), (*it)["filename"].asString());
            this->pictures.push_back(p);
        }

    }

    pictureJsonFile.close();

    // Load Report from Json
    std::ifstream file("data/reports.json");
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {

        if(this->id == (*it)["radioId"].asInt()) {
            Report rep = Report((*it)["radioId"].asInt(), (*it)["content"].asString());
            this->report = rep;
        }
    }

    file.close();
}

int Radiography::getId() { return id; }
int Radiography::getDoctorId() { return doctorId; }
std::string Radiography::getType() { return type; }
std::string Radiography::getState() { return state; }
int Radiography::getPatientId() { return patientId; }
Date Radiography::getDate() { return date; }
std::vector<Picture>& Radiography::getPictures() { return pictures; }
Report Radiography::getReport() { return report; }

void Radiography::addPicture(Picture picture) { this->pictures.push_back(picture); }

/****** Patient class Definition ***************************************************/

Patient::Patient() {}
Patient::Patient(int id, std::string name) { this->id = id; this->name = name; }

void Patient::loadRadiographies() {

    std::vector<Radiography> tempRadios;

    std::ifstream file("data/radiographies.json");
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {

        if((*it)["patientId"] == this->id) {
            Date date = Date(
                (*it)["date"]["day"].asInt(),
                (*it)["date"]["month"].asInt(),
                (*it)["date"]["year"].asInt()
            );
            Radiography r = Radiography(
                (*it)["id"].asInt(),
                (*it)["type"].asString(),
                (*it)["state"].asString(),
                (*it)["patientId"].asInt(),
                (*it)["doctorId"].asInt(),
                date
            );

            tempRadios.push_back(r);
        }

    }

    file.close();

    this->radiographies = tempRadios;
}

bool Patient::load(std::string name, std::string password) {
    std::ifstream file("data/patients.json");
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {
        std::string fromJsonName = (*it)["name"].asString();
        std::string fromJsonPassword = (*it)["password"].asString();

        if(fromJsonName == name && fromJsonPassword == password) {

            this->name = fromJsonName;
            this->password = fromJsonPassword;
            this->id = (*it)["id"].asInt();

            this->loadRadiographies();

            return true;
        }

        if(fromJsonName == name && fromJsonPassword != password) {
            return false;
        }

    }

    file.close();

    return false;
}

int Patient::getId() { return id; }
std::string Patient::getName() { return name; }
std::vector<Radiography>& Patient::getRadiographies() { return radiographies; }


/****** Doctor class Definition ****************************************************/

Doctor::Doctor() {}
Doctor::Doctor(int id, std::string name, std::string status, std::string password) { this->id = id; this->name = name; this->status = status; this->password = password; }
int Doctor::getId() { return id; }
std::string Doctor::getName() { return name; }
std::string Doctor::getStatus() { return status; }
std::string Doctor::getPassword() { return password; }
std::vector<Radiography>& Doctor::getRadiographies() { return radiographies; }

void Doctor::loadRadiographies() {

    std::vector<Radiography> tempRadios;

    std::ifstream file("data/radiographies.json");
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {

        if((*it)["doctorId"] == this->id) {
            Date date = Date(
                (*it)["date"]["day"].asInt(),
                (*it)["date"]["month"].asInt(),
                (*it)["date"]["year"].asInt()
            );
            Radiography r = Radiography(
                (*it)["id"].asInt(),
                (*it)["type"].asString(),
                (*it)["state"].asString(),
                (*it)["patientId"].asInt(),
                (*it)["doctorId"].asInt(),
                date
            );
            tempRadios.push_back(r);
        }

    }

    file.close();

    this->radiographies = tempRadios;
}

void Doctor::showRadiographies() {
    std::cout << " ID       | TYPE        | ETAT              | DATE      | PATIENT ID         " << std::endl;
    for(int i=0; i < getRadiographies().size(); i++) {
        std::cout << " " << getRadiographies().at(i).getId() << "         " << getRadiographies().at(i).getType() << "          "
                << getRadiographies().at(i).getState() << "         " << getRadiographies().at(i).getDate().getStringDate() 
                << "      " << getRadiographies().at(i).getPatientId() << std::endl;
    }
}

bool Doctor::deleteRadiography(int id) {

    bool result = false;

    if((id >= 0) && (radiographies.size() !=0) && (radiographies.size() >= 0)) {
        
        std::ifstream file("data/radiographies.json");
        Json::Value value;
        Json::Reader reader;

        reader.parse(file, value);

        for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {

            if(((*it)["doctorId"].asInt() == this->id) && ((*it)["id"].asInt() == id)) {
                
                // TODO: delete the pictures linked to the radiography

                // TODO: delete the report linked to the radiography

                // TODO: delete the radiography in the database
                (*it).clear();

                Json::StreamWriterBuilder builder;
                builder["commentStyle"] = "None";
                builder["indentation"] = "   ";

                std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                std::ofstream outputFileStream("data/radiographies.json");
                writer -> write(value, &outputFileStream);

                outputFileStream.close();

                result = true;
            }

        }

        file.close();
    }

    this->loadRadiographies();

    return result;
}

std::vector<Patient> Doctor::getPatientList() {

    std::vector<Patient> patients;

    std::ifstream file("data/patients.json");
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {

        Patient patient = Patient((*it)["id"].asInt(), (*it)["name"].asString());
        patients.push_back(patient);

    }

    file.close();

    return patients;

}

bool Doctor::addRadiography(std::string type, std::string state, int patientId, Date date) {

    std::ifstream file("data/radiographies.json");
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    // get the last id of from the json table
    int lastExistingRadioId = 0;
    for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {

        lastExistingRadioId = (*it)["id"].asInt();

    }

    lastExistingRadioId++;

    // create a jsonValue for the new radiography
    Json::Value valueRadio;
    valueRadio["date"]["day"] = date.getDay();
    valueRadio["date"]["month"] = date.getMonth();
    valueRadio["date"]["year"] = date.getYear();
    valueRadio["doctorId"] = this->id;
    valueRadio["id"] = lastExistingRadioId;
    valueRadio["patientId"] = patientId;
    valueRadio["state"] = state;
    valueRadio["type"] = type;

    // append the new value to the old array
    value.append(valueRadio);

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "   ";

    // Push changes to the json file
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    std::ofstream outputFileStream("data/radiographies.json");
    writer -> write(value, &outputFileStream);

    file.close();
    outputFileStream.close();

    // Add the new radiography to the radiography vector of the doctor
    Radiography r = Radiography(lastExistingRadioId, type, state, patientId, this->id, date);
    this->radiographies.push_back(r);

    return true;
}

bool Doctor::load(std::string name, std::string password) {
    std::ifstream file("data/doctors.json");
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {
        std::string fromJsonName = (*it)["name"].asString();
        std::string fromJsonPassword = (*it)["password"].asString();

        if(fromJsonName == name && fromJsonPassword == password) {

            this->name = fromJsonName;
            this->password = fromJsonPassword;
            this->status = (*it)["status"].asString();
            this->id = (*it)["id"].asInt();

            this->loadRadiographies();

            return true;
        }

    }

    file.close();

    return false;
}

void Doctor::changePassword(std::string newPasseword) {

    std::ifstream file("data/doctors.json");
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {
        std::string fromJsonName = (*it)["name"].asString();
        std::string fromJsonPassword = (*it)["password"].asString();

        if(fromJsonName == this->name && fromJsonPassword == this->password) {
            
            (*it)["password"] = newPasseword;

            Json::StreamWriterBuilder builder;
            builder["commentStyle"] = "None";
            builder["indentation"] = "   ";

            std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
            std::ofstream outputFileStream("data/doctors.json");
            writer -> write(value, &outputFileStream);

            outputFileStream.close();
        }

    }

    file.close();

    this->password = newPasseword;
}

void Doctor::showPictureList(int radioId) {

    Radiography r = Radiography();

    for(int i=0; i < getRadiographies().size(); i++) {
        if(getRadiographies().at(i).getId() == radioId) {
            r = getRadiographies().at(i);
        }
    }
    std::cout << " ID       | RADIO ID      | FILENAME      " << std::endl;
    for(int i=0; i < r.getPictures().size(); i++) {
        Picture p = r.getPictures().at(i);
        std::cout << " " << p.getId() << "      " << r.getId() << "     " << p.getFilename() << std::endl;
    }
}

void Doctor::showReport(int radioId, std::string pwd) {
    bool exists = false;
    Radiography r = Radiography();
    for(int i=0; i < getRadiographies().size(); i++) {
        if(getRadiographies().at(i).getId() == radioId) {
            r = getRadiographies().at(i);
            exists = true;
        }
    }
    if(!exists) {
        std::cout << "Aucun rapport n'est lié à cette radiographie" << std::endl;
        return;
    }
    if(this->password != pwd) {
        std::cout << "Mot de passe incorrect. Accès refusé" << std::endl;
        return;
    }
    std::cout << "Rapport médical : " << std::endl;
    std::cout << r.getReport().getContent() << std::endl;
}

void Doctor::addReport(int radioId) {

    bool isReportExisting = false;

    std::ifstream file("data/reports.json");
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    // get the last id of from the json table
    int lastExistingReportId = 0;
    for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {

        lastExistingReportId = (*it)["id"].asInt();

        // check if a report exist already for the current radiography
        if((*it)["radioId"].asInt() == radioId) {
            isReportExisting = true;
        }

    }

    // if the report do not exist then create it, else don't
    if(!isReportExisting) {

        lastExistingReportId++;

        // create a jsonValue for the new radiography
        Json::Value valueReport;
        valueReport["id"] = lastExistingReportId;
        valueReport["radioId"] = radioId;
        valueReport["content"] = "== Nouveau Rapport ==";
        
        // append the new value to the old array
        value.append(valueReport);

        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = "   ";

        // Push changes to the json file
        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        std::ofstream outputFileStream("data/reports.json");
        writer -> write(value, &outputFileStream);

        std::cout << "Un nouveau rapport a ete cree pour cette radiographie" << std::endl;

        file.close();
        outputFileStream.close();

        this->loadRadiographies();
    } else {
        std::cout << "Un rapport associe a cette radiographie existe deja" << std::endl;
    }
}


void Doctor::modifyReport(int radioId, std::string content) {

    std::ifstream file("data/reports.json");
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {

        if(radioId == (*it)["radioId"].asInt()) {
            
            Json::Value valueNewReport;
            valueNewReport["id"] = (*it)["id"].asInt();
            valueNewReport["radioId"] = (*it)["radioId"].asInt();
            valueNewReport["content"] = (*it)["content"].asString() + content;

            // delete the old report 
            (*it).clear();

            // add the new report to the list of reports in the json file
            value.append(valueNewReport);

            Json::StreamWriterBuilder builder;
            builder["commentStyle"] = "None";
            builder["indentation"] = "   ";

            std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
            std::ofstream outputFileStream("data/reports.json");
            writer -> write(value, &outputFileStream);

            outputFileStream.close();
            file.close();

            this->loadRadiographies();

            return;
        }
    }

}

void Doctor::addPicture(int radioId, std::string filename) {

    std::ifstream file("data/pictures.json");
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    // get the last id of from the json table
    int lastExistingPictureId = 0;
    for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {

        lastExistingPictureId = (*it)["id"].asInt();

    }

    lastExistingPictureId++;

    // create a jsonValue for the new radiography
    Json::Value valuePicture;
    valuePicture["id"] = lastExistingPictureId;
    valuePicture["radioId"] = radioId;
    valuePicture["filename"] = filename;
    
    // append the new value to the old array
    value.append(valuePicture);

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "   ";

    // Push changes to the json file
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    std::ofstream outputFileStream("data/pictures.json");
    writer -> write(value, &outputFileStream);

    file.close();
    outputFileStream.close();

    // Reload the whole radiography vector to get fresh data
    this->loadRadiographies(); //! This should reload the whole radiographies and their pictures
}

void Doctor::deletePicture(int pictureId) {
        
        std::ifstream file("data/pictures.json");
        Json::Value value;
        Json::Reader reader;

        reader.parse(file, value);

        for(Json::Value::iterator it = value.begin(); it != value.end(); it++) {

            if((*it)["id"].asInt() == pictureId) {

                (*it).clear();

                Json::StreamWriterBuilder builder;
                builder["commentStyle"] = "None";
                builder["indentation"] = "   ";

                std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
                std::ofstream outputFileStream("data/pictures.json");
                writer -> write(value, &outputFileStream);

                outputFileStream.close();
            }

        }

        file.close();

    this->loadRadiographies();

}

