#include "MyPlane.h"

MyPlane::MyPlane() {
    m_crewNeeded.clear();
}

int MyPlane::getModelNumber() {
    return m_modelNumber;
}

map<Jobs, int> MyPlane::getCrewNeeded() {
    return m_crewNeeded;
}

int MyPlane::getMaxFirstClass() {
    return m_maxFirstClass;
}

int MyPlane::getMaxEconomyClass() {
    return m_maxEconomyClass;
}

list <Date> &MyPlane::getFlightDates() {
    return m_flightDates;
}

MyPlane::~MyPlane() {

}

string MyPlane::getID() {
    return m_ID;
}

bool MyPlane::isOccupied(Date &d) {
    auto it = m_flightDates.begin();
    while (it != m_flightDates.end()) {
        if (*it == d)
            return true;
        ++it;
    }
    return false;
}

void MyPlane::setM_modelNumber(int modelNumber) {
    m_modelNumber = modelNumber;
}

void MyPlane::setM_maxFirstClass(int maxFirstClass) {
    m_maxFirstClass = maxFirstClass;
}

void MyPlane::setM_maxEconomyClass(int maxEconomyClass) {
    m_maxEconomyClass = maxEconomyClass;
}

void MyPlane::setM_ID(const string &ID) {
    m_ID = ID;
}

void MyPlane::setM_crewNeeded(const map<Jobs, int> &crewNeeded) {
    m_crewNeeded = crewNeeded;
}

void MyPlane::addFlightDate(Date &d) {
    m_flightDates.push_back(d);
}
