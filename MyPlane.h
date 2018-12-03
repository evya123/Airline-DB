
#ifndef EX2_PLANE_H
#define EX2_PLANE_H


#include "interface.h"

class MyPlane : public Plane {
public:
    MyPlane();

//############Getters############
    virtual int getModelNumber();

    virtual string getID();

    virtual map<Jobs, int> getCrewNeeded();

    virtual int getMaxFirstClass();

    virtual int getMaxEconomyClass();

    list <Date> &getFlightDates();

    bool isOccupied(Date &d);

//############Setters############
    void setM_modelNumber(int m_modelNumber);

    void setM_maxFirstClass(int m_maxFirstClass);

    void setM_maxEconomyClass(int m_maxEconomyClass);

    void setM_ID(const string &m_ID);

    void setM_crewNeeded(const map<Jobs, int> &m_crewNeeded);

    void addFlightDate(Date &d);

    virtual ~MyPlane();

private:
    int m_modelNumber, m_maxFirstClass, m_maxEconomyClass;
    string m_ID;
    list <Date> m_flightDates;
    map<Jobs, int> m_crewNeeded; //Indicate what number of type Jobs is needed.
};


#endif //EX2_PLANE_H
