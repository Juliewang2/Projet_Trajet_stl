#include "Graphe.h"
#include "Trajet.h"
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <queue>
#include <climits>
void Graphe::AjouterTrajet(const Trajet * t)
{
     graphe[t->GetVilleDepart()].push_back(t);
}
void Graphe::Afficher()const
{
     if (graphe.empty()){
          cout<<"Catalogue vide."<<endl;
          return;
     }
     for (const auto & [villeDepart,trajets]:graphe)
     {
          cout<<"Depuis"<<villeDepart<<":"<<endl;
          for (const Trajet* t:trajets)
          {
               cout<<"->";
               t->Afficher();
          }
          cout<<endl;
     }
}
void Graphe::DFS(const string & courant,const string & arrive,map<string,bool> & visite,vector<string>&chemin)const
{
     visite[courant]=true;
     chemin.push_back(courant);
     if (courant==arrive)
     {
          for (const string & ville:chemin)
              cout<<ville<<" ";
          cout<<endl; 
     }
     else
     {
          auto it =graphe.find(courant);
          if (it !=graphe.end())
          {
               for (const Trajet* t:it->second)
               {
                    string suivant =t->GetVilleArrive();
                    if (!visite[suivant])
                    {
                         DFS(suivant,arrive,visite,chemin);
                    }
               }
          }
     }
     chemin.pop_back();
     visite[courant]=false;
}
void Graphe::ChercherCheminsPossibles(const string & depart,const string & arrive)const
{    
     map<string,bool> visite;
     vector<string> chemin;
     DFS(depart, arrive, visite, chemin);
}

void Graphe::ChercherPlusCourtChemin(const string & depart,const string & arrive)const
{
     using Noeud = pair<int,string>;
     priority_queue<
         Noeud,
         vector<Noeud>,
         greater<Noeud>
     > pq;
     map<string,int>distance;
     map<string,string>precedent;
     for (auto & [ville, _]:graphe)
          distance[ville]=INT_MAX;
     distance[depart] =0;
     pq.push({0,depart});
     while (!pq.empty())
     {
          auto [dist,ville]=pq.top();
          pq.pop();
          if (ville==arrive)break;
          auto it = graphe.find(ville);
          if (it == graphe.end()) continue;
          for (const Trajet* t:it->second)
          {
              string next = t->GetVilleArrive();
              int newDist = dist + t->GetLongueur();
              if (newDist<distance[next])
              {
                  distance[next]=newDist;
                  precedent[next]=ville;
                  pq.push({newDist,next});
              }
          }
     }
     if (distance[arrive] == INT_MAX)
     {
         cout << "Aucun chemin trouvé" << endl;
         return;
     }

     vector<string> chemin;
     for (string v = arrive; v != depart; v = precedent[v])
         chemin.push_back(v);
     chemin.push_back(depart);

     reverse(chemin.begin(), chemin.end());

     for (const string& v : chemin)
         cout << v << " ";
     cout << endl;
}
Graphe::Graphe(){};
Graphe::~Graphe(){};