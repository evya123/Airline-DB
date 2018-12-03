//
// Created by cs on 11/27/18.
//

#ifndef EX2_RESERVATIONFACTORY_H
#define EX2_RESERVATIONFACTORY_H

#include "AbsFactory.h"
#include "../MyReservation.h"

class ReservationFactory : public AbsFactory<Reservation> {
public:
    virtual MyReservation *create();

    void setM_customer(MyCustomer *m_customer);

    void setM_flight(MyFlight *m_flight);

    void setCls(Classes cls);

    void setMax_baggage(int max_baggage);

    virtual ~ReservationFactory();

private:
    list<MyReservation *> listToFree;
    Classes m_cls;
    int m_max_baggage;
    MyCustomer *m_customer;
    MyFlight *m_flight;
};


#endif //EX2_RESERVATIONFACTORY_H
