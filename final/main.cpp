
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

void waitInput() {
    std::cin.ignore();
    std::cin.clear();
    do {
        std::cout << "\n Press any key to continue...";
    } while(std::cin.get() != '\n');
    system("clear");
}

int main() {

    system("clear");

    int selectedMode;
    int subSelectedMode;
    bool alive = true;
    bool bSubMenuAlive = true;
    std::string password;
    std::string name;

    std::cout << "\n####################################" 
              << "\n#         Base de Donnees          #"
              << "\n####################################\n\n" << std::endl;
    std::cout << "Selectionner une option de Login\n\n  \033[1;32m[1]-Patient\033[0m\n  \033[1;36m[2]-Medecin\033[0m" << std::endl;
    std::cin >> selectedMode;

    if(selectedMode == 1) {
        std::cout << "Indiquez votre nom" << std::endl;
        std::cin >> name;
        std::cout << "Indiquez votre mot de passe" << std::endl;
        std::cin >> password;

        Patient p;
        if(p.load(name, password)) {

            system("clear");

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
            std::cout << "\033[1;31m mot de passe ou identifiant incorrect \033[0m" << std::endl;
        }
    }

    if(selectedMode == 2) {
        std::cout << "Indiquez votre nom" << std::endl;
        std::cin >> name;
        std::cout << "Indiquez votre mot de passe" << std::endl;
        std::cin >> password;

        Doctor d;

        if(d.load(name, password)) {

            system("clear");

            do {
                
                std::cout << "\n####################################" 
                          << "\n    Bienvenue  " << d.getStatus() << " " <<  d.getName()
                          << "\n####################################\n\n" << std::endl;

                std::cout << " Affichage : " << std::endl;
                std::cout << "   \033[1;36m[1]: Afficher la liste de vos radiographies\033[0m\n" << std::endl;
                std::cout << " Selection/Ajout : " << std::endl;
                std::cout << "   \033[1;32m[2]: Selectionner une radiographie" << std::endl;
                std::cout << "   [3]: Ajouter une radiographie\033[0m\n" << std::endl;
                std::cout << " Mon Compte : " << std::endl;
                std::cout << "   \033[1;34m[4]: Changer de mot de passe" << std::endl;
                std::cout << "   [5]: Se Deconnecter\033[0m\n" << std::endl;
                std::cout << " Extras : " << std::endl;
                std::cout << "   \033[1;33m[6]: Afficher l'aide\033[0m\n" << std::endl;

                std::cin >> subSelectedMode;
                int sortType = 0;

                switch(subSelectedMode) {
                    
                    // Displaying radiography Form
                    case 1:
                        {
                            std::cout << "choisir le type de tri vous souhaitez : " << std::endl;
                            std::cout << " [1]: Par patientId \n [2]: Par radioId \n [3]: Par date" << std::endl;
                            std::cin >> sortType;                            
                            d.showRadiographies(sortType);
                            break;
                        }

                    // Selecting a radiography
                    case 2:
                        {
                            int selectedRadioId;
                            std::cout << "Indiquez quel radiographie vous voulez selectionner" << std::endl;
                            d.showRadiographies(2);

                            std::cin >> selectedRadioId;

                            bSubMenuAlive = false;

                            // Check if the radiography selected is one the doctor should have access to
                            for(int i = 0; i < d.getRadiographies().size(); i++) {
                                if(d.getRadiographies().at(i).getId() == selectedRadioId) {
                                    bSubMenuAlive = true;
                                }
                            }

                            if(bSubMenuAlive == false) {
                                std::cout << "\033[1;31m\nVous n'avez pas l'autorisation d'acceder a cette radiographie\033[0m" << std::endl;
                                break;
                            } else {
                                system("clear");
                            }

                            int actionId;

                            do {

                                std::string filename;
                                int pictureId;
                                std::string reportContent;

                                std::cout << "\n####################################" 
                                          << "\n#         Radiographie " << selectedRadioId << "           #"
                                          << "\n####################################\n\n" << std::endl;
                                std::cout << " General : " << std::endl;
                                std::cout << "   \033[1;35m[1]: Quitter la selection\33[0m\n" << std::endl;
                                std::cout << " Affichage : " << std::endl;
                                std::cout << "   \033[1;36m[2]: Afficher la liste des clichés" << std::endl;
                                std::cout << "   [3]: Afficher le rapport medical associé\33[0m\n" << std::endl;
                                std::cout << " Ajouter/Modifier : " << std::endl;
                                std::cout << "   \033[1;32m[4]: Ajouter un cliché" << std::endl;
                                std::cout << "   [5]: Ajouter un rapport" << std::endl;
                                std::cout << "   [6]: Modifier le rapport\33[0m\n" << std::endl;
                                std::cout << " Supprimer : " << std::endl;
                                std::cout << "   \033[1;31m[7]: Supprimer un cliché" << std::endl;
                                std::cout << "   [8]: Supprimer la radiographie\033[0m\n" << std::endl;

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
                                            d.addPicture(selectedRadioId, filename);
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

                                if(bSubMenuAlive) {
                                    waitInput();
                                }

                            } while(bSubMenuAlive);

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
                        }

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
                            std::cout << "Page d'aide : \n Merci de lire le readme.md  :) " << std::endl;
                            break;
                        }

                    // Unkown menu requested
                    default: 
                        {
                            std::cout << "Mode inconnu selectionne ! " << std::endl;
                            break;
                        }
                }

                waitInput();

            } while(alive);

        } else {

            std::cout << "\033[1;31m mot de passe  ou identifiant incorrect (ou les deux)\033[0m" << std::endl;

        }

    }

    return 0;
}