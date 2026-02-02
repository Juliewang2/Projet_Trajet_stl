#if ! defined ( TRAJETCOMPOSE_H )
#define TRAJETCOMPOSE_H

#include "Trajet.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class TrajetCompose : public Trajet
{
public:
    TrajetCompose() : Trajet("", "", "") {}
    TrajetCompose(const std::vector<Trajet*>& trajets);
    virtual ~TrajetCompose();
    virtual Trajet* clone() const override ;
    void Afficher() const override;
    void Sauvgarder(std::ofstream& out) const override;
    int NbEtapes() const;
    int GetLongueur() const override;
    void AjouterEtape(Trajet* t);
    const Trajet* GetEtape(int i)const ;

protected:
    std::vector<Trajet*> unTrajCom;
};


bool TrajetValide(const std::vector<Trajet*>& trajets);

#endif
