#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H
#include "Trajet.h"
#include <string>
#include <fstream>
using namespace std;
class TrajetSimple:public Trajet
{
    public:
          void Afficher()const;
          void Sauvgarder(ofstream & out)const override;
          int GetLongueur()const override;
          Trajet* clone() const override ;
          TrajetSimple(const string & depart,
                       const string & arrive,
                       const string & transport,
                       int longueur);
          ~TrajetSimple();
    protected:
          int longueur;
};
#endif
