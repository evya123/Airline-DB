
#ifndef EX2_MYRESERVATION_H
#define EX2_MYRESERVATION_H

#include "interface.h"
#include "MyCustomer.h"
#include "MyFlight.h"

class MyReservation : public Reservation {
public:
    MyReservation();

//############Getters############
    virtual Customer *getCustomer();

    virtual Flight *getFlight();

    virtual Classes getClass();

    virtual int getMaxBaggage();

    virtual string getID();

//############Setters############
    void setM_maxBaggage(int m_maxBaggage);

    void setM_id(const string &m_id);

    void setM_customer(Customer *customer);

    void setM_flight(Flight *flight);

    void setM_class(Classes cls);

    virtual ~MyReservation();

private:
    int m_maxBaggage; //How many suitcases allowed
    Customer *m_customer;
    Flight *m_flight;
    Classes m_class; //which class the customer wants
    string m_id;
};


#endif //EX2_MYRESERVATION_H
