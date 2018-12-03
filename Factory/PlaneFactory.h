//
// Created by cs on 11/27/18.
//

#ifndef EX2_PLANEFACTORY_H
#define EX2_PLANEFACTORY_H

#include "AbsFactory.h"
#include "../MyPlane.h"

class PlaneFactory : public AbsFactory<MyPlane> {
public:
    virtual MyPlane *create();

    void setModel_number(int model_number);

    void setCrew_needed(const map<Jobs, int> &crew_needed);

    void setMax_passangers(const map<Classes, int> &max_passangers);

private:
public:
    virtual ~PlaneFactory();

private:
    list<MyPlane *> listToFree;
    int m_model_number;
    map<Jobs, int> m_crew_needed;
    map<Classes, int> m_max_passangers;
};


#endif //EX2_PLANEFACTORY_H
