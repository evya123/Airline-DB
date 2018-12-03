//
// Created by cs on 11/27/18.
//

#include "EmployeeFactory.h"

void EmployeeFactory::setM_title(Jobs title) {
    m_title = title;
}

void EmployeeFactory::setM_date(const string &date) {
    m_date = date;
}

void EmployeeFactory::setM_seniority(int seniority) {
    m_seniority = seniority;
}

void EmployeeFactory::setM_employer(Employee *e) {
    m_employer = e;
}

MyEmployee *EmployeeFactory::create() {
    MyEmployee *ret = new MyEmployee();
    ret->setTitle(m_title);
    ret->set_Date(m_date);
    ret->set_seniority(m_seniority);
    ret->set_ID(m_idFactory.createID(EID));
    ret->set_Employer(m_employer);
    listToFree.push_back(ret);
    return ret;
}

EmployeeFactory::~EmployeeFactory() {
    for (auto it : listToFree)
        delete (it);
}
