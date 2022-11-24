

#include<iostream>
#include<string>
#include<vector>
#include<memory>

/******** Date class Declaration ************************************************/

class Date {

    private:
        int day;
        int month;
        int year;

    public:
        Date();
        Date(int, int, int);
        int getDay();
        int getMonth();
        int getYear();
        std::string getStringDate(); // return stringlified version of the date
};

/******** Report class Declaration **********************************************/

class Report {

    private:
        int id;
        std::string content;

    public:
        Report();
        Report(int, std::string);
        
        std::string getContent();
        
};

/******* Picture class Declaration *********************************************/

class Picture {
    
    private:
        int id;
        std::string filename;
    
    public:
        Picture();
        Picture(int, std::string);
        
        int getId();
        std::string getFilename();

};

/****** Radiography class Declaration ******************************************/

class Radiography {

    private:
        int id;
        std::string type;
        std::string state;
        int patientId;
        int doctorId;
        Date date;

        std::vector<Picture> pictures;
        Report report;

    public:
        Radiography();
        Radiography(int, std::string, std::string, int, int, Date);

        int getId();
        std::string getType();
        std::string getState();
        int getPatientId();
        int getDoctorId();
        Date getDate();
        std::vector<Picture>& getPictures();
        Report getReport();

        void addPicture(Picture);

};

/****** Patient class Declaration **********************************************/

class Patient {

    // TODO : Peut etre amélioré, si y a deux personne avec le meme nom ca bug..

    private:
        int id;
        std::string name;
        std::string password;
        std::vector<Radiography> radiographies;

        void loadRadiographies();
    
    public:
        Patient();
        Patient(int, std::string);
        int getId();
        std::string getName();
        std::vector<Radiography>& getRadiographies();

        bool load(std::string, std::string);

};

/****** Doctor class Declaration ***********************************************/

class Doctor {

    private:
        int id;
        std::string name;
        std::string status;
        std::string password;
        std::vector<Radiography> radiographies;

        void loadRadiographies();

    public:
        Doctor();
        Doctor(int, std::string, std::string, std::string);
        int getId();
        std::string getName();
        std::string getStatus();
        std::string getPassword();
        std::vector<Radiography>& getRadiographies();

        void showRadiographies();
        bool deleteRadiography(int);
        bool addRadiography(std::string, std::string, int, Date);

        std::vector<Patient> getPatientList();

        bool load(std::string, std::string);

        void changePassword(std::string);

        void showPictureList(int);
        void showReport(int, std::string);
        void addReport(int);
        void modifyReport(int, std::string);

        void addPicture(int, std::string);
        void deletePicture(int);

};