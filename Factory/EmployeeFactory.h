//
// Created by cs on 11/27/18.
//

#ifndef EX2_EMPLOYEEFACTORY_H
#define EX2_EMPLOYEEFACTORY_H

#include "../MyEmployee.h"
#include "AbsFactory.h"


class EmployeeFactory : public AbsFactory<MyEmployee> {
public:
    virtual MyEmployee *create();

    void setM_title(Jobs m_title);

    void setM_date(const string &m_date);

    void setM_seniority(int m_seniority);

    void setM_employer(Employee *e);

    virtual ~EmployeeFactory();

private:
    Jobs m_title;
    string m_date;
    int m_seniority;
    Employee *m_employer;
    list<MyEmployee *> listToFree;
};


#endif //EX2_EMPLOYEEFACTORY_H
