#include<iostream>

#include "classes.h"

// compilation : g++ -o main main.cpp classes.o

int main() {

    Patient p1(1, "Brieuc Quemeneur");
    Patient p2(2, "Florent Boyer");

    std::cout << p1.getName() << std::endl;
    std::cout << p2.getName() << std::endl;

    Radiography r1(1, "Rayon X", true, p1, Date());

    std::cout << "Nom du patient : " << r1.getPatient().getName() << std::endl;
    std::cout << "Date de la radiographie : " << r1.getDate().getStringDate() << std::endl;
    std::cout << "Effectu?? ? " << std::to_string(r1.getState()) << std::endl;
    std::cout << "Type de radio : " << r1.getType() << std::endl;

    Picture pic1(1, "picture1.jpg");

    r1.addPicture(pic1);

    std::cout << "\nNom du fichier de la photo : " << r1.getPictures().at(0).getFilename() << std::endl;

    Report report1 = Report("12341234", "contenu", "Dr Yahadih");

    std::cout << "Rapport modifi?? ? " << std::to_string(r1.getPictures().at(0).setReport(report1)) << std::endl;

    std::cout << "Indiquer le mot de passe" << std::endl;

    std::string pwd;
    std::cin >> pwd;

    if(r1.getPictures().at(0).getReport(pwd).getAuthorName() != "INVALID") {
        std::cout << "Contenu du rapport " << r1.getPictures().at(0).getReport(pwd).getContent() << std::endl;
        std::cout << "Auteur du rapport " << r1.getPictures().at(0).getReport(pwd).getAuthorName() << std::endl;
    } else {
        std::cout << "le mot de passe est incorrect" << std::endl;
    }

    return 0;
}