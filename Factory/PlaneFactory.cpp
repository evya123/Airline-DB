//
// Created by cs on 11/27/18.
//

#include "PlaneFactory.h"

void PlaneFactory::setModel_number(int model_number) {
    m_model_number = model_number;
}

void PlaneFactory::setCrew_needed(const map<Jobs, int> &crew_needed) {
    m_crew_needed = crew_needed;
}

void PlaneFactory::setMax_passangers(const map<Classes, int> &max_passangers) {
    m_max_passangers = max_passangers;
}

MyPlane *PlaneFactory::create() {
    auto *ret = new MyPlane();
    try {
        ret->setM_ID(m_idFactory.createID(PID));
        ret->setM_modelNumber(m_model_number);
        ret->setM_maxEconomyClass(m_max_passangers.at(SECOND_CLASS));
        ret->setM_maxFirstClass(m_max_passangers.at(FIRST_CLASS));
        ret->setM_crewNeeded(m_crew_needed);
        listToFree.push_back(ret);
        return ret;

    } catch (...) {
        delete (ret);
        throw;
    }
}

PlaneFactory::~PlaneFactory() {
    for (auto it : listToFree)
        delete (it);
}
