//
// Created by cs on 11/27/18.
//

#include "FlightFactory.h"

FlightFactory::FlightFactory() : m_date("9999-01-01") {

}

void FlightFactory::setM_src(const string &src) {
    m_src = src;
}

void FlightFactory::setM_dst(const string &dst) {
    m_dst = dst;
}


void FlightFactory::setM_date(const Date &date) {
    m_date = date;
}

MyFlight *FlightFactory::create() {
    auto *ret = new MyFlight();
    try {
        ret->setM_currentCrew(m_crewForFlight);
        ret->setM_src(m_src);
        ret->setM_dst(m_dst);
        ret->setM_flightDate(m_date);
        ret->setM_ID(m_idFactory.createID(FID));
        ret->setM_plane(dynamic_cast<MyPlane *>(m_plane));
        listToFree.push_back(ret);
        return ret;
    } catch (...) {
        delete (ret);
        throw;
    }

}

void FlightFactory::setCrewForFlight(const list<Employee *> &crewForFlight) {
    m_crewForFlight = crewForFlight;
}

void FlightFactory::setPlane(Plane *p) {
    m_plane = p;
}

FlightFactory::~FlightFactory() {
    for (auto it : listToFree)
        delete (it);

}


