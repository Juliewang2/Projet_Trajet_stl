#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Trajet.h"
#include "Catalogue.h"
#include "Graphe.h"
#include <limits>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;
enum Operation{AJOUT_TRAJ_S=1,AJOUT_TRAJ_COMPO=2,AFFICHAGE=3,RECHERCHE=4,QUITTER=5,SAUVGARDER=6,CHARGER=7,CHEMIN_PLUS_COURT=8};
void clearInput(){
  //vide le buffer d'entrée
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(),'\n');//ignorer les caracteres inutiles jusqu'a la fin de la ligne
}
TrajetSimple* CreateTrajetSimple(){
  //Demaande à l'utilisateur le Trajet Simple à Ajouter
  TrajetSimple* trajet(nullptr);
  string villeDepart;
  string villeArrive;
  string moyenTransport;
  int longueur;
  cout<<"veuillez entrer une ville de départ:\t";
  cin>>villeDepart;
  cout<<"veuillez entrer une ville d'arrivée:\t";
  cin>>villeArrive;
  cout<<"veuillez donner un moyen de transport:\t";
  cin>>moyenTransport;
  cout<<"Longueur de trajet:\t";
  cin>>longueur;
  trajet=new TrajetSimple(villeDepart,villeArrive,moyenTransport,longueur);
  return trajet;
}
TrajetCompose* CreateTrajetCompose()
{
    TrajetCompose* trajet=nullptr;
    vector<Trajet*>unTrajCom;
    int taille;
    cout<<"Veuillez entrer un nombre étape: \t";
    cin>>taille;
     if (!cin || taille < 1)
    {
        cout << "entrée invalide" << endl;
        return nullptr;
    }
    for  (int t=0;t<taille;++t)
    {
        cout<<"trajet number"<<t+1<<":"<<endl;
        TrajetSimple* ts=CreateTrajetSimple();
        if (ts==nullptr)
        {
            for (Trajet* p:unTrajCom)
            {
                 delete p;
            }
            return nullptr;
        }
        unTrajCom.push_back(ts);
    }
    if (TrajetValide(unTrajCom))
    {
            trajet = new TrajetCompose(unTrajCom);
    }
    else
    {
            cout << "liaison invalide" << endl;
    }

    // nettoyage des trajets simples "patrons"
    for (Trajet* p : unTrajCom)
        delete p;
    return trajet;
}
int main()
{
      Catalogue cata;
      int numOp(0);
      Trajet* trajetAAjouter;
      cout<<"Bienvenue dans notre application de gestion de trajets"<<endl;
      while(numOp!=QUITTER){
        numOp=0;
        cout<<"Quelle opération souhaitez-vous effectuer?"<<endl;
        cout<<AJOUT_TRAJ_S<<":\t Ajout d'un Trajet Simple"<<endl;
        cout<<AJOUT_TRAJ_COMPO<<":\t Ajout d'un Trajet Composé"<<endl;
        cout<<AFFICHAGE<<":\t Affichage du Catalogue"<<endl;
        cout<<RECHERCHE<<":\t Recherche d'itinéraires possible pour un road trip"<<endl;
        cout<<QUITTER<<":\t Quitter l'application"<<endl;
        cout<<SAUVGARDER<<":\t Sauvegarder le catalogue dans un fichier"<<endl;
        cout<<CHARGER<<":\t Charger le catalogue depuis un fichier"<<endl;
        cout<<CHEMIN_PLUS_COURT<<":\t Trouver le chemin le plus court"<<endl;
        cout<<"CHOIX => :";
        if (!(cin>>numOp)){
          cerr<<"entrée invalide, veuillez réessayer"<<endl;
          clearInput();
          continue;
        }
        cout<<endl;
        switch(numOp){
            case AJOUT_TRAJ_S:
              trajetAAjouter=CreateTrajetSimple();
              if(trajetAAjouter==nullptr){
        	       cout<<"echec de l'ajout"<<endl;
              }
              else{
                 if (trajetAAjouter->GetVilleDepart()==trajetAAjouter->GetVilleArrive()){
                      cout<<"Le trajet ne peut pas commencer et se finir dans la meme ville."<<endl;
                      delete trajetAAjouter;
                      break;
                 }
              cata.AjouterTrajet(trajetAAjouter);//transfert de propriété de la case mémoire pointé par AjoutTrajet
              cout<<"trajet bien ajouté"<<endl;
              }
              break;
             case AJOUT_TRAJ_COMPO:
             {    bool invalide=false;
                  trajetAAjouter=CreateTrajetCompose();
                  if(trajetAAjouter==nullptr){
            	       cout<<"echec de l'ajout"<<endl;
                     break;
                  }
                  else{
                     if (trajetAAjouter->GetVilleDepart()==trajetAAjouter->GetVilleArrive()){
                          cout<<"Le trajet ne peut pas commencer et se finir dans la meme ville."<<endl;
                          delete trajetAAjouter;
                          break;
                     }
                     TrajetCompose* tc = dynamic_cast<TrajetCompose*>(trajetAAjouter);

                    if (tc != nullptr)
                    {
                         int n = tc->NbEtapes();
                         for (int i = 0; i < n; ++i)
                         {
                              const Trajet* ts = tc->GetEtape(i);
                              if (ts->GetVilleDepart() == ts->GetVilleArrive())
                              {
                                   cout<<"Le trajet composé contient une étape invalide où la ville de départ et la ville d'arrivée sont les mêmes."<<endl;
                                   invalide=true;
                                   break;
                              }
                         }
                    }
                    }
                      if (invalide){
                         delete trajetAAjouter;
                         break;
                      }
                      cata.AjouterTrajet(trajetAAjouter);//transfert de propriété de la case mémoire pointé par AjoutTrajet
                      cout<<"trajet bien ajouté"<<endl;
                      break;
              }
             case AFFICHAGE:
                cata.Afficher();
                break;
             case RECHERCHE:
             {
                   string depart,arrive;
                   cout<<"Ville de depart :";
                   cin>>depart;
                   cout<<"Ville d'arrive :";
                   cin>>arrive;
                   cata.RechercheChemins(depart,arrive);
                   break;
             }
             case QUITTER:
                   cout<<"Quit"<<endl;
                   break;
             case SAUVGARDER:
             { string nomFichier;
                   cout<<"Nom du fichier à sauvgarder : ";
                   cin >> nomFichier;
                   cata.Sauvgarder(nomFichier);
                   break;
             }
             case CHARGER:
             {     string nomFichier;
                   cout<<"Nom du fichier à charger : ";
                   cin >> nomFichier;
                   cata.Charger(nomFichier);
                   break;
             }
             case CHEMIN_PLUS_COURT:
             {     string depart,arrive;
                  cout<<"Ville de depart :";
                  cin>>depart;
                  cout<<"Ville d'arrive :";
                  cin>>arrive;
                  cata.GetGraphe().ChercherPlusCourtChemin(depart,arrive);
                  break;
             }
             default:
                   cerr<<"opération non définie"<<endl;
                   break;
        }
        cout<<endl;
      }
      return 0;
}
