#include "MyEmployee.h"

MyEmployee::MyEmployee() : m_date("9999-12-31") {
    m_seniority = 0; //How many years he is working
    m_employer = nullptr;
}


int MyEmployee::getSeniority() {
    return m_seniority;
}

int MyEmployee::getBirthYear() {
    return stoi(m_date);
}

Employee *MyEmployee::getEmployer() {
    return m_employer;
}

void MyEmployee::set_seniority(int seniority) {
    if (seniority < 0)
        throw invalid_argument("seniority must be >= 0");
    m_seniority = seniority;
}

void MyEmployee::set_ID(string idNumber) {
    if (idNumber.find_first_not_of(ALLOWED_CHAR) != string::npos)
        throw invalid_argument("ID is not as expected, try again!");
    if (idNumber.length() < 0)
        throw invalid_argument("ID is not as expected, try again!");
    m_ID = idNumber;
}

MyEmployee::~MyEmployee() {

}

void MyEmployee::set_Employer(Employee *employer) {
    m_employer = employer;
}

void MyEmployee::set_Date(string d) {
    d += "-12-31";
    m_date = d;
}


void MyEmployee::setTitle(const Jobs title) {
    m_title = title;
}

void MyEmployee::setFlightDate(const Date &d) {
    m_flightDates.push_back(d);
}

Jobs MyEmployee::getTitle() {
    return m_title;
}

string MyEmployee::getID() {
    return m_ID;
}

const list <Date> &MyEmployee::getM_flightDate() const {
    return m_flightDates;
}
