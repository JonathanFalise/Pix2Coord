#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>//librairie pour les string

using namespace std;

//Prototypes
void shutdown(string message, ifstream &f_in, ofstream &f_out);
void printTabl(vector <int> const &vect2Print());

//Définition des fonctions
void Shutdown(string message, ifstream &f_in, ofstream &f_out){
    cerr<<message<<endl;
    f_in.close();
    f_out.close();
    exit(EXIT_FAILURE); // Arrete le fichier si la fonction shutdown est appele
}

void printVect(vector <int> const &vect2Print){//print le vecteur
    int szVect2Print=vect2Print.size();
    for(int i(0);i<sizeVect2Print;i++){
        cout<<"V("<<i<<")= "<<vect2Print.at(i)<<endl;
    }
    /*string f_name_out;
    f_name_out= "Pos.txt";
    ofstream f_out(f_name_out.c_str());
    if(f_out.fail()){
        cerr<<"erreur lors de l'ecriture dans le fichier de sortie"<<endl;
        //Un truc pour clean
    }else{
        f_out<<TabCoord[0]<<","<<TabCoord[1]<<endl;//écrit dans le fichier la postion 1 du tableau
        f_out<<TabCoord[2]<<","<<TabCoord[3]<<endl;
        f_out<<TabCoord[4]<<","<<TabCoord[5]<<endl;
        f_out.close();
    }*/
}

int main(){
    ifstream f_in("Pixmap1.txt");
    ofstream f_out;

    if(f_in.fail()){ //test de l'ouvertutre du fichier
        string errOuv = "Erreur lors de l'ouverture du fichier pixmap.txt";
        Shutdown(errOuv, f_in, f_out);
    }
    else{
        if(f_in.fail()){ //test de la lecture du fichier
            string errLect = "Erreur lors de la lecture du fichier";
            Shutdown(errLect, f_in, f_out);
        }
        else{
            int largeur(0), hauteur(0), nbCoul(0), nbTraces(0), compteur(0);
            int XptRef1(0),YptRef1(0),XptRef2(0),YptRef2(0),XptRef3(0),YptRe31(0),XptRef4(0),YptRef4(0);
            
            f_in >> largeur; // Récupération de la largeur dans un int
            if(largeur<10){
                //cout<<"Largeur= "<<largeur<<endl;
                string errDim = "La largeur est trop petite (<10)!";
                Shutdown(errDim, f_in, f_out);
            }
            else if(largeur>1000){
                //cout<<"Largeur= "<<largeur<<endl;
                string errDim = "La largeur est trop grande (>1000)!";
                Shutdown(errDim, f_in, f_out);
            }
            
            f_in >> hauteur; // Récupération de la hauteur
            if(hauteur<10){
                string errDim = "La hauteur est trop petite (<10)!";
                Shutdown(errDim, f_in, f_out);
            }
            else if(hauteur>1000){
                string errDim = "La hauteur est trop grande (>1000)!";
                Shutdown(errDim, f_in, f_out);
            }
            
            cout<<largeur<<": largeur"<<endl;
            cout<<hauteur<<": hauteur"<<endl;
            
            f_in >> nbCoul;
            nbTraces = nbCoul - 4;
            
            for(int i(0); i < 4; i++){ //Couleurs des points référence dans un vecteur
                int tmp(0);
                f_in >> tmp;
                vectColorRef.push_back(tmp);
            }
            printVect(vectColorRef);

            for(int j(0); j < nbTraces; j++){  //Couleurs des différentes traces
                int tmp(0);
                f_in >> tmp;
                vectColorTraces.push_back(tmp);
            }
            printVect(vectColorTraces);
            
            while(!f_in.eof()){     //Boucle qui lit tout le fichier GESTION ERREUR A FAIRE: 1PIXEL NON BLANC. A VOIR: PAS BESOIN DE TABLEAU DE STOCKAGE INTERME COMME DEMANDER DANS LA DONNEE.
                int tmp(0);
                f_in>> tmp;

                if(tmp==vectColorRef.at(0)){    //test si la ligne a la couleur de ref 1. CA A L'AIRE OK. A VERIFIER
                    XptRef1= compteur%largeur;
                    YptRef1= (hauteur-1)-(compteur/largeur);
                    cout<<"X= "<<XptRef1<<" Y= "<<YptRef1<<endl;
                }
                if(tmp==vectColorRef.at(1)){    //test si la ligne a la couleur de ref 1. CA A L'AIRE OK. A VERIFIER
                    XptRef2= compteur%largeur;
                    YptRef2= (hauteur-1)-(compteur/largeur);
                    cout<<"X= "<<XptRef1<<" Y= "<<YptRef1<<endl;
                }
                if(tmp==vectColorRef.at(2)){    //test si la ligne a la couleur de ref 1. CA A L'AIRE OK. A VERIFIER
                    XptRef3= compteur%largeur;
                    YptRef4= (hauteur-1)-(compteur/largeur);
                    cout<<"X= "<<XptRef1<<" Y= "<<YptRef1<<endl;
                }
                if(tmp==vectColorRef.at(3)){    //test si la ligne a la couleur de ref 1. CA A L'AIRE OK. A VERIFIER
                    XptRef4= compteur%largeur;
                    YptRef4= (hauteur-1)-(compteur/largeur);
                    cout<<"X= "<<XptRef1<<" Y= "<<YptRef1<<endl;
                }
                compteur++;
            }
        }
    }
}
