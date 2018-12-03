//
// Created by cs on 11/24/18.
//

#ifndef EX2_MYFLIGHT_H
#define EX2_MYFLIGHT_H

#include "interface.h"
#include "MyPlane.h"
#include "MyEmployee.h"

class MyFlight : public Flight {
public:
    MyFlight();

    virtual ~MyFlight();

//############Getters############
    virtual int getModelNumber();

    virtual list<Reservation *> getReservations();

    virtual list<Employee *> getAssignedCrew();

    virtual Date getDate();

    virtual string getSource();

    virtual string getDestination();

    virtual string getID();

    MyPlane *getPlane();

    bool checkEnoughSits(Classes);

//############Setters############
    void setM_plane(MyPlane *m_plane);

    void setM_res(const list<Reservation *> &m_res);

    void addCrewMember(MyEmployee *);

    void setM_currentCrew(const list<Employee *> &currentCrew);

    void setM_flightDate(const Date &m_flightDate);

    void setM_src(const string &m_src);

    void setM_dst(const string &m_dst);

    void setM_ID(const string &m_ID);

    void addReservation(Reservation *);

private:
    MyPlane *m_plane;
    list<Reservation *> m_res;
    list<Employee *> m_currentCrew;
    Date m_flightDate;
    string m_src, m_dst, m_ID;


};


#endif //EX2_MYFLIGHT_H
