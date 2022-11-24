
/*
    Projet de Programmation Orientée Objet

    ~~~~~~~~~~~~
    main.cpp

    Code source de l'application base de donnée 
    orientée objet. Voir les fonctionnalités 
    supportées dans README.md

    compilation: g++ -o main main.cpp classes.o -ljsoncpp

    ~~~~~~~~~~~~
    Auteurs:
        Brieuc Quemeneur
        Florent Boyer

    ~~~~~~~~~~~~
    Licence-MIT

*/


#include<iostream>
#include<memory>
#include<jsoncpp/json/json.h>

#include "classes.hpp"

// compilation : g++ -o main main.cpp classes.o -ljsoncpp

int main() {

    int selectedMode;
    int subSelectedMode;
    bool alive = true;
    bool bSubMenuAlive = true;
    std::string password;
    std::string name;

    std::cout << "Selectionner une option de Login\n [1]-Patient\n [2]-Medecin" << std::endl;
    std::cin >> selectedMode;

    if(selectedMode == 1) {
        std::cout << "Indiquez votre nom" << std::endl;
        std::cin >> name;
        std::cout << "Indiquez votre mot de passe" << std::endl;
        std::cin >> password;

        Patient p;
        if(p.load(name, password)) {
            // Cas ou le patient est log avec succes

            std::cout << "Bonjour " << p.getName() <<std::endl;
            std::cout << " Voici vos radiographies" << std::endl;

            std::cout << " ID       | TYPE        | ETAT              | DATE      | PATIENT         " << std::endl;
            for(int i=0; i < p.getRadiographies().size(); i++) {
                std::cout << " " << p.getRadiographies().at(i).getId() << "         " << p.getRadiographies().at(i).getType() << "          "
                          << p.getRadiographies().at(i).getState() << "         " << p.getRadiographies().at(i).getDate().getStringDate() 
                          << "      " << p.getName() << std::endl;
            }

        } else {
            std::cout << "mot de passe incorrect" << std::endl;
        }
    }

    if(selectedMode == 2) {
        std::cout << "Indiquez votre nom" << std::endl;
        std::cin >> name;
        std::cout << "Indiquez votre mot de passe" << std::endl;
        std::cin >> password;

        Doctor d;

        if(d.load(name, password)) {

            while(alive) {

                std::cout << "Connecté en tant que " << d.getStatus() << " " <<  d.getName() << std::endl;
                std::cout << "Actions possibles : " << std::endl;
                std::cout << " Affichage : " << std::endl;
                std::cout << "   [1]: Afficher la liste de vos radiographies" << std::endl;
                std::cout << " Selection/Ajout : " << std::endl;
                std::cout << "   [2]: Selectionner une radiographie" << std::endl;
                std::cout << "   [3]: Ajouter une radiographie" << std::endl;
                std::cout << " Mon Compte : " << std::endl;
                std::cout << "   [4]: Changer de mot de passe" << std::endl;
                std::cout << "   [5]: Se Deconnecter" << std::endl;
                std::cout << " Extras : " << std::endl;
                std::cout << "   [6]: Afficher l'aide" << std::endl;

                std::cin >> subSelectedMode;

                switch(subSelectedMode) {
                    
                    // Displaying radiography Form
                    case 1:
                        {
                            d.showRadiographies();
                            break;
                        }

                    // Selecting a radiography
                    case 2:
                        {
                            int selectedRadioId;
                            std::cout << "Indiquez quel radiographie vous voulez selectionner" << std::endl;
                            d.showRadiographies();

                            std::cin >> selectedRadioId;

                            bSubMenuAlive = false;

                            // Check if the radiography selected is one the doctor should have access to
                            for(int i = 0; i < d.getRadiographies().size(); i++) {
                                if(d.getRadiographies().at(i).getId() == selectedRadioId) {
                                    bSubMenuAlive = true;
                                }
                            }

                            int actionId;

                            while(bSubMenuAlive) {

                                std::string filename;
                                int pictureId;
                                std::string reportContent;

                                std::cout << "Radiographie " << selectedRadioId << " selectionnee" << std::endl;
                                std::cout << "Actions possibles : " << std::endl;
                                std::cout << " General : " << std::endl;
                                std::cout << "   [1]: Quitter la selection" << std::endl;
                                std::cout << " Affichage : " << std::endl;
                                std::cout << "   [2]: Afficher la liste des clichés" << std::endl;
                                std::cout << "   [3]: Afficher le rapport medical associé" << std::endl;
                                std::cout << " Ajouter/Modifier : " << std::endl;
                                std::cout << "   [4]: Ajouter un cliché" << std::endl;
                                std::cout << "   [5]: Ajouter un rapport" << std::endl;
                                std::cout << "   [6]: Modifier le rapport" << std::endl;
                                std::cout << " Supprimer : " << std::endl;
                                std::cout << "   [7]: Supprimer un cliché" << std::endl;
                                std::cout << "   [8]: Supprimer la radiographie" << std::endl;

                                std::cin >> actionId;

                                switch(actionId) {
                                    case 1:
                                        {   
                                            bSubMenuAlive = !bSubMenuAlive;
                                            break;
                                        }
                                    case 2:
                                        {
                                            d.showPictureList(selectedRadioId);
                                            break;
                                        }
                                    case 3:
                                        {   
                                            std::cout << "Pour accèder au rapport, entrez votre mot de passe personnel" << std::endl;
                                            std::string password;
                                            std::cin >> password;
                                            d.showReport(selectedRadioId, password);
                                            break;
                                        }
                                    case 4:
                                        {
                                            std::cout << "Ajouter de cliche" << std::endl;
                                            std::cout << "indiquer le nom du fichier" << std::endl;
                                            std::cin >> filename;
                                            d.addPicture(selectedRadioId, filename); //! ajoute bien la picture au fichier mais n'affiche correctement la liste de pictures..
                                            break;
                                        }
                                    case 5:
                                        {
                                            d.addReport(selectedRadioId);
                                            break;
                                        }
                                    case 6:
                                        {
                                            std::cout << "indiquer le texte a ajouter dans le rapport" << std::endl;
                                            std::cin >> reportContent;
                                            d.modifyReport(selectedRadioId, reportContent);
                                            break;
                                        }
                                    case 7:
                                        {   
                                            // works
                                            d.showPictureList(selectedRadioId);
                                            std::cout << "Indiquer l'identifiant de la photo a supprimer" << std::endl;
                                            std::cin >> pictureId;
                                            d.deletePicture(pictureId);
                                            break;
                                        }
                                    case 8:
                                        {
                                            // works
                                            // TODO : implement the complete deletion of the file
                                            if(d.deleteRadiography(selectedRadioId)) {
                                                bSubMenuAlive = !bSubMenuAlive;
                                            } else {
                                                std::cout << "la radiographie n'a pas pu etre supprimee" << std::endl;
                                            }

                                            break;
                                        }
                                    default:
                                        {
                                            std::cout << "L'option selectionnée n'est pas reconnue" << std::endl;
                                            break;
                                        }
                                }

                            }
                            break;
                        }
                    case 3:
                        {
                            int selectedId;
                            std::string type;
                            std::string state;
                            int day = 1;
                            int month = 1;
                            int year = 1970;
                            Date date = Date();
                            
                            std::cout << "Liste des patients" << std::endl;
                            std::vector<Patient> patients = d.getPatientList();
                            std::cout << " ID       | NOM        " << std::endl;
                            for(int i = 0; i < patients.size(); i++) {
                                std::cout << patients.at(i).getId() << "      " << patients.at(i).getName() << std::endl;
                            }
                            std::cout << "Selectionner le patient correspondant à la radiographie" << std::endl;
                            std::cin >> selectedId;

                            std::cout << "Quel est le type de radiographie ?" << std::endl;
                            std::cin >> type;

                            std::cout << "Quel est l'état de la radiographie ?" << std::endl;
                            std::cin >> state;

                            std::cout << "Indiquez la date de la radiographie [JOUR MOIS ANNEE]";
                            std::cin >> day; std::cin >> month; std::cin >> year;

                            d.addRadiography(type, state, selectedId, Date(day, month, year));

                            break;
                        }/*
                    case 3:
                        {
                            int rmRadioId;
                            std::cout << "Indiquer quelle radiographie supprimer " << std::endl;
                            std::cin >> rmRadioId;
                            if(d.deleteRadiography(rmRadioId)) {
                                std::cout << "Radiographie " << rmRadioId << " supprimée avec succès" << std::endl;
                            } else {
                                std::cout << "La radiographie n'a pas pu être supprimée. Elle est soit inexistante ou vous n'avez pas les droits de la supprimer" << std::endl;
                            }
                            break;
                        }
                    */
                    // Change password
                    case 4:
                        {
                            std::string newPassword;
                            std::cout << "Formulaire de changement de mot de passe" << std::endl;
                            std::cout << "Nouveau mot de passe : ";
                            std::cin >> newPassword;
                            d.changePassword(newPassword);
                            break;
                        }

                    // Disconnect
                    case 5:
                        {
                            alive = !alive;
                            break;
                        }

                    case 6:
                        {
                            std::cout << "This is the help page" << std::endl;
                            break;
                        }

                    // Unkown menu requested
                    default: 
                        {
                            std::cout << "Mode inconnu selectionne ! " << std::endl;
                            break;
                        }
                }
            }

        } else {
            std::cout << "mot de passe incorrect" << std::endl;
        }
    }

    return 0;
}