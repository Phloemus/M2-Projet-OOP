#include<iostream>
#include<string>
#include<vector>

class Patient {

    private:
        int id;
        std::string name;
    
    public:
        Patient();
        Patient(int, std::string);
        int getId();
        std::string getName();

};

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


class Report {

    private:
        std::string password;
        std::string content;
        std::string authorName;

    public:
        Report();
        Report(std::string, std::string, std::string);
        //Report checkPassword(std::string); // check if the password is ok. 
        //std::string getAuthor();

        std::string getPassword();
        
        std::string getContent();
        std::string getAuthorName();
        
};

class Picture {
    
    private:
        int id;
        std::string filename;
        Report report;

        bool checkPassword(std::string); // real password checking
    
    public:
        Picture();
        Picture(int, std::string);
        Picture(int, std::string, Report);
        
        int getId();
        std::string getFilename();

        Report getReport(std::string); // necessite un mot de passe
        bool setReport(Report);
};

class Radiography {

    private:
        int id;
        std::string type;
        bool state;
        Patient patient;
        Date date;
        std::vector<Picture> pictures;

    public:
        Radiography(int, std::string, bool, Patient, Date);
        int getId();
        std::string getType();
        bool getState();
        Patient getPatient();
        Date getDate();
        std::vector<Picture>& getPictures();
        void addPicture(Picture);

};

class App {

    private:
        std::vector<Radiography> radiographies;

    public:
        App();
        /*
        void loadRadiographies(std::string);
        bool addRadiography(Radiography);
        bool deleteRadiography(Radiography);
        bool saveRadiographies(std::string);*/
};