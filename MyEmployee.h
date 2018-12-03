
#ifndef EX2_EMPLOYEE_H
#define EX2_EMPLOYEE_H

#include <string>
#include "interface.h"

#define ALLOWED_CHAR "0123456789EID"
using namespace std;

class MyEmployee : public Employee {
public:

    MyEmployee();

//############Getters############
    virtual int getSeniority();

    virtual int getBirthYear();

    virtual Employee *getEmployer();

    virtual Jobs getTitle();

    virtual string getID();

    const list <Date> &getM_flightDate() const;

//############Setters############
    void set_seniority(int seniority);

    void set_Date(string date);

    void set_Employer(Employee *employer);

    void setTitle(const Jobs title);

    void setFlightDate(const Date &d);

    void set_ID(string idNumber);

    virtual ~MyEmployee();

private:
    int m_seniority = 0; //How many years he has worked
    Employee *m_employer = nullptr;
    string m_date; //yyyy/mm/dd
    list <Date> m_flightDates;
    string m_ID;
    Jobs m_title;

};


#endif //EX2_EMPLOYEE_H
