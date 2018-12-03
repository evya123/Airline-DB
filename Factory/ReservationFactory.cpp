//
// Created by cs on 11/27/18.
//

#include "ReservationFactory.h"


void ReservationFactory::setCls(Classes cls) {
    m_cls = cls;
}

void ReservationFactory::setMax_baggage(int max_baggage) {
    m_max_baggage = max_baggage;
}

void ReservationFactory::setM_customer(MyCustomer *customer) {
    m_customer = customer;
}

void ReservationFactory::setM_flight(MyFlight *flight) {
    m_flight = flight;
}

MyReservation *ReservationFactory::create() {
    MyReservation *ret = new MyReservation();
    ret->setM_id(m_idFactory.createID(RID));
    ret->setM_class(m_cls);
    ret->setM_maxBaggage(m_max_baggage);
    ret->setM_customer(m_customer);
    ret->setM_flight(m_flight);
    listToFree.push_back(ret);
    return ret;
}

ReservationFactory::~ReservationFactory() {
    for (auto it : listToFree)
        delete (it);

}
