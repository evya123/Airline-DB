//
// Created by cs on 11/27/18.
//

#ifndef EX2_FLIGHTFACTORY_H
#define EX2_FLIGHTFACTORY_H


#include "AbsFactory.h"
#include "../MyFlight.h"

class FlightFactory : public AbsFactory<MyFlight> {
public:
    FlightFactory();

    virtual MyFlight *create();

    void setM_src(const string &m_src);

    void setM_dst(const string &m_dst);

    void setM_date(const Date &m_date);

    void setCrewForFlight(const list<Employee *> &crewForFlight);

    void setPlane(Plane *);

    virtual ~FlightFactory();

private:
    string m_src, m_dst;
    Date m_date;
    list<Employee *> m_crewForFlight;
    Plane *m_plane;
    list<MyFlight *> listToFree;
};


#endif //EX2_FLIGHTFACTORY_H
