#include <iostream>
#include <fstream>
#include <cstdlib>//librairie pour les string

using namespace std;

//Prototypes
void shutdown(string message, ifstream &f_in, ofstream &f_out);

//Définition des fonctions
void Shutdown(string message, ifstream &f_in, ofstream &f_out){
    cerr<<message<<endl;
    f_in.close();
    f_out.close();
    exit(EXIT_FAILURE); // Arrete le fichier si la fonction shutdown est appele
}
int main(){
    //string f_name_in("Pixmap.txt");
    ifstream f_in("Pixmap1.txt");
    ofstream f_out;

    if(f_in.fail()){//test de l'ouvertutre du fichier
        string errOuv = "Erreur lors de l'ouverture du fichier pixmap.txt";
        Shutdown(errOuv, f_in, f_out);
    }else{
        if(f_in.fail()){//test de la lecture du fichier
            string errLect = "Erreur lors de la lecture du fichier";
            Shutdown(errLect, f_in, f_out);
        }
        else{
            string largeurStr, hauteurStr;
            string tmp;
            getline(f_in,tmp);
            largeurStr=tmp;
            if(largeur<=10){
                //cout<<"Largeur= "<<largeur<<endl;
                string errDim = "La largeur est trop petite <=10";
                Shutdown(errDim, f_in, f_out);
            }else if(largeur>1000){
                //cout<<"Largeur= "<<largeur<<endl;
                string errDim = "La largeur est trop grande >1000";
                Shutdown(errDim, f_in, f_out);
            }
           f_in.read((char*)&hauteur,sizeof(hauteur)-1);// meme chose que pour la largeure, mais pour la hauteurs
           if(hauteur<=10){
                string errDim = "La hauteur est trop petite <=10";
                Shutdown(errDim, f_in, f_out);
            }else if(hauteur>1000){
                string errDim = "La hauteur est trop grande >1000";
                Shutdown(errDim, f_in, f_out);
            }

            cout<<largeur<<": largeur"<<endl;
            cout<<hauteur<<": hauteur"<<endl;
        }
    }
}
