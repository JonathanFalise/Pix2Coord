// Pix2Coord.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>//librairie pour les string
#include <string> //a inclure pour pouvoir inprimer un string!!

using namespace std;

//Prototypes
void Shutdown(string message, ifstream &f_in, ofstream &f_out);
void Print(string nomVect, vector <int> const &vect2PrintX, vector <int> const &vect2PrintY, ofstream &f_out);

//Définition des fonctions
void Shutdown(string message, ifstream &f_in, ofstream &f_out) {
	cerr << message << endl;
	f_in.close();
	f_out.close();
	exit(EXIT_FAILURE); // Arrete le fichier si la fonction shutdown est appele
}

//print les vecteurs contenant les coordonnées de la trace indiquée
void Print(string nomVect, vector <int> const &vect2PrintX, vector <int> const &vect2PrintY, ofstream &f_out) {
	if (f_out.fail()) {
		cerr << "erreur lors de l'ecriture dans le fichier de sortie" << endl;
		//Un truc pour clean
	}
	else {
		int sizeVect = vect2PrintX.size();
		f_out << nomVect << endl;
		for (int i(0); i<sizeVect; i++) {
			f_out << vect2PrintX.at(i) << " " << vect2PrintY.at(i) << endl;
		}
		f_out << "];" << endl;
	}
}

int main() {
	ifstream f_in("pixmap.txt");
	string f_name_out;
	f_name_out = "traces.m";
	ofstream f_out(f_name_out.c_str());

	if (f_in.fail()) { //test de l'ouverture du fichier
		string errOuv = "Erreur lors de l'ouverture du fichier pixmap.txt";
		Shutdown(errOuv, f_in, f_out);
	}
	else {
		if (f_in.fail()) { //test de la lecture du fichier
			string errLect = "Erreur lors de la lecture du fichier";
			Shutdown(errLect, f_in, f_out);
		}
		else {
			int largeur(0), hauteur(0), nbCoul(0), nbTraces(0), compteur(0);
			int XptRef1(-1), YptRef1(-1), XptRef2(-1), YptRef2(-1), XptRef3(-1), YptRef3(-1), XptRef4(-1), YptRef4(-1);// initialise a -1 car on doit verifier si les points de références sont donnés (et il pourrait être égale a 0).
			vector <int> vectColorRef, vectColorTraces, vectRefX, vectRefY, vectPosXTr1, vectPosYTr1, vectPosXTr2, vectPosYTr2, vectPosXTr3, vectPosYTr3, vectPosXTr4, vectPosYTr4;

			// Récupération de la largeur dans un int
			f_in >> largeur;
			if (largeur<10) {
				//cout<<"Largeur= "<<largeur<<endl;
				string errDim = "La largeur est trop petite (<10)!";
				Shutdown(errDim, f_in, f_out);
			}
			else if (largeur>1000) {
				//cout<<"Largeur= "<<largeur<<endl;
				string errDim = "La largeur est trop grande (>1000)!";
				Shutdown(errDim, f_in, f_out);
			}

			// Récupération de la hauteur dans un int
			f_in >> hauteur;
			if (hauteur<10) {
				string errDim = "La hauteur est trop petite (<10)!";
				Shutdown(errDim, f_in, f_out);
			}
			else if (hauteur>1000) {
				string errDim = "La hauteur est trop grande (>1000)!";
				Shutdown(errDim, f_in, f_out);
			}

			cout << largeur << ": largeur" << endl;
			cout << hauteur << ": hauteur" << endl;

			f_in >> nbCoul;
			nbTraces = nbCoul - 4;

			if ((nbTraces == 0) || (nbTraces>4)) {
				string errNoTr = "Il y a un probleme avec le nombre de courbes (trop nombreuses ou aucune courbe presente)";
				Shutdown(errNoTr, f_in, f_out);
			}

			//Couleurs des points référence dans un vecteur
			for (int i(0); i < 4; i++) {
				int tmp(0);
				f_in >> tmp;
				vectColorRef.push_back(tmp);
			}
			//printVect(vectColorRef);

			//Couleurs des différentes traces
			for (int j(0); j < nbTraces; j++) {
				int tmp(0);
				f_in >> tmp;
				vectColorTraces.push_back(tmp);
			}


			while (!f_in.eof()) {     //Boucle qui lit tout le fichier GESTION ERREUR A FAIRE: 1PIXEL NON BLANC. A VOIR: PAS BESOIN DE TABLEAU DE STOCKAGE INTERME COMME DEMANDER DANS LA DONNEE.
				int tmp(0), XPtTraces(0), YPtTraces(0);
				f_in >> tmp;

				if (compteur == 0) {
					if (tmp != 0) {// test si le 1er pixel n'est pas blanc
						string errPix0 = "le premier pixel de l'image n'est pas blanc";
						Shutdown(errPix0, f_in, f_out);
					}
				}


				//Recherche Point de Ref   SWITCH CASE MIEUX ? A TESTER---> pas sur

				//test si la ligne a la couleur de ref 1. CA A L'AIRE OK. A VERIFIER
				if (tmp == vectColorRef.at(0)) {

					XptRef1 = compteur%largeur;
					YptRef1 = (hauteur - 1) - (compteur / largeur);// Possible promblème ? faudrait-il mieux arrondir avant la soustraction ?

					cout << "X= " << XptRef1 << " Y= " << YptRef1 << endl;
				}

				//test si la ligne a la couleur de ref 2. CA A L'AIRE OK. A VERIFIER
				else if (tmp == vectColorRef.at(1)) {
					XptRef2 = compteur%largeur;
					YptRef2 = (hauteur - 1) - (compteur / largeur);
					cout << "X= " << XptRef2 << " Y= " << YptRef2 << endl;
				}

				//test si la ligne a la couleur de ref 3. CA A L'AIRE OK. A VERIFIER
				else if (tmp == vectColorRef.at(2)) {
					XptRef3 = compteur%largeur;
					YptRef3 = (hauteur - 1) - (compteur / largeur);
					cout << "X= " << XptRef3 << " Y= " << YptRef3 << endl;
				}

				//test si la ligne a la couleur de ref 4. CA A L'AIRE OK. A VERIFIER
				else if (tmp == vectColorRef.at(3)) {
					XptRef4 = compteur%largeur;
					YptRef4 = (hauteur - 1) - (compteur / largeur);
					cout << "X= " << XptRef4 << " Y= " << YptRef4 << endl;
				}

				//no break car, il faut qu'il test chaque if necessaire.
				switch (nbTraces) {
				case 4:
					if (tmp == vectColorTraces.at(3)) {
						XPtTraces = compteur%largeur;
						YPtTraces = (hauteur - 1) - (compteur / largeur);
						vectPosXTr4.push_back(XPtTraces);
						vectPosYTr4.push_back(YPtTraces);
					}
				case 3:
					if (tmp == vectColorTraces.at(2)) {
						XPtTraces = compteur%largeur;
						YPtTraces = (hauteur - 1) - (compteur / largeur);
						vectPosXTr3.push_back(XPtTraces);
						vectPosYTr3.push_back(YPtTraces);
					}
				case 2:
					if (tmp == vectColorTraces.at(1)) {
						XPtTraces = compteur%largeur;
						YPtTraces = (hauteur - 1) - (compteur / largeur);
						vectPosXTr2.push_back(XPtTraces);
						vectPosYTr2.push_back(YPtTraces);
					}
				case 1:
					if (tmp == vectColorTraces.at(0)) {
						XPtTraces = compteur%largeur;
						YPtTraces = (hauteur - 1) - (compteur / largeur);
						vectPosXTr1.push_back(XPtTraces);
						vectPosYTr1.push_back(YPtTraces);
					}
					break;
				}
				compteur++;
			}

			//Test si les 4 points de Ref sont dans l'image
			if ((XptRef1 == -1) || (XptRef2 == -1) || (XptRef3 == -1) || (XptRef4 == -1)) { //Besoin de tester qu'une coord. car si x là --> y aussi
				string errPtRef = "Un Point de Reference est manquant";
				Shutdown(errPtRef, f_in, f_out);
			}

			string errNbPtTr = "Une courbe n'a pas assez de point pour pouvoir la dessiner";

			// Test s'il y a assez de points . tester dans un Switch car nombre de traces peut varier
			switch (nbTraces) {
			case 4:
				if (vectPosXTr4.size()<10) {
					Shutdown(errNbPtTr, f_in, f_out);
				}
			case 3:
				if (vectPosXTr3.size()<10) {
					Shutdown(errNbPtTr, f_in, f_out);
				}
			case 2:
				if (vectPosXTr2.size()<10) {
					Shutdown(errNbPtTr, f_in, f_out);
				}
			case 1:
				if (vectPosXTr1.size()<10) {
					Shutdown(errNbPtTr, f_in, f_out);
				}
				break;
			}

			vectRefX.push_back(XptRef1);
			vectRefY.push_back(YptRef1);
			vectRefX.push_back(XptRef2);
			vectRefY.push_back(YptRef2);
			vectRefX.push_back(XptRef3);
			vectRefY.push_back(YptRef3);
			vectRefX.push_back(XptRef4);
			vectRefY.push_back(YptRef4);

			string nomRef = "P=[";
			Print(nomRef, vectRefX, vectRefY, f_out);

			switch (nbTraces) {
			case 4: {
				string nomTr3 = "C3=[";
				Print(nomTr3, vectPosXTr4, vectPosYTr4, f_out);
			}
			case 3: {
				string nomTr2 = "C2=[";
				Print(nomTr2, vectPosXTr3, vectPosYTr3, f_out);
			}
			case 2: {
				string nomTr1 = "C1=[";
				Print(nomTr1, vectPosXTr2, vectPosYTr2, f_out);
			}
			case 1: {
				string nomTr0 = "C0=[";
				Print(nomTr0, vectPosXTr1, vectPosYTr1, f_out);
				break;
			}
			default: {
				cout << "test" << endl;
			}
			}

			f_in.close();
			f_out.close();

		}
	}
}
