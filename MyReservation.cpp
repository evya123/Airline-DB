
#include "MyReservation.h"

MyReservation::MyReservation() {
    m_maxBaggage = 0;
    m_customer = nullptr;
    m_flight = nullptr;
}

string MyReservation::getID() {
    return m_id;
}

Customer *MyReservation::getCustomer() {
    return m_customer;
}

Flight *MyReservation::getFlight() {
    return m_flight;
}

Classes MyReservation::getClass() {
    return m_class;
}

int MyReservation::getMaxBaggage() {
    return m_maxBaggage;
}

void MyReservation::setM_maxBaggage(int maxBaggage) {
    m_maxBaggage = maxBaggage;
}

void MyReservation::setM_customer(Customer *customer) {
    m_customer = customer;
}

void MyReservation::setM_flight(Flight *flight) {
    m_flight = flight;
}

void MyReservation::setM_class(Classes cls) {
    m_class = cls;
}

void MyReservation::setM_id(const string &id) {
    m_id = id;
}

MyReservation::~MyReservation() {

}
