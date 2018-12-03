#include <iostream>
#include "CustomerFactory.h"

void CustomerFactory::setFull_name(const string &full_name) {
    m_full_name = full_name;
}

void CustomerFactory::setPriority(int priority) {
    m_priority = priority;
}

MyCustomer *CustomerFactory::create() {
    MyCustomer *ret = new MyCustomer();
    ret->setM_ID(m_idFactory.createID(CID));
    ret->setM_fullName(m_full_name);
    ret->setM_priority(m_priority);
    listToFree.push_back(ret);
    return ret;
}

CustomerFactory::~CustomerFactory() {
    for (auto it : listToFree)
        delete (it);
}

