//
// Created by cs on 11/24/18.
//

#include <iostream>
#include "MyCustomer.h"

string MyCustomer::getFullName() {
    return m_fullName;
}

int MyCustomer::getPriority() {
    return m_priority;
}

list<Reservation *> MyCustomer::getReservations() {
    return m_res;
}

string MyCustomer::getID() {
    return m_ID;
}

void MyCustomer::setM_ID(const string &ID) {
    m_ID = ID;
}

void MyCustomer::setM_fullName(const string &fullName) {
    m_fullName = fullName;
}

void MyCustomer::setM_priority(int priority) {
    if (priority > 5 || priority < 1)
        throw invalid_argument("priority must be between 1 to 5");
    m_priority = priority;
}

void MyCustomer::addRes(Reservation *res) {
    m_res.push_back(res);
}
