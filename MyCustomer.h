//
// Created by cs on 11/24/18.
//

#ifndef EX2_MYCUSTOMER_H
#define EX2_MYCUSTOMER_H

#include "interface.h"
#include "MyReservation.h"


class MyCustomer : public Customer {
public:

//############Getters############
    virtual string getFullName();

    virtual int getPriority();

    virtual list<Reservation *> getReservations();

    virtual string getID();

//############Setters############
    void setM_ID(const string &m_ID);

    void setM_fullName(const string &m_fullName);

    void setM_priority(int m_priority);

    void addRes(Reservation *);

    virtual ~MyCustomer() = default;

private:
    list<Reservation *> m_res;
    string m_ID, m_fullName;
    int m_priority; //from 1 to 5
};


#endif //EX2_MYCUSTOMER_H
