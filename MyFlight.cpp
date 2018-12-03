
#include "MyFlight.h"

MyFlight::MyFlight() : m_flightDate("9999-12-31") {
    m_plane = nullptr;
    m_res.clear();
    m_currentCrew.clear();
}

int MyFlight::getModelNumber() {
    return m_plane->getModelNumber();
}

list<Reservation *> MyFlight::getReservations() {
    return m_res;
}

list<Employee *> MyFlight::getAssignedCrew() {
    return m_currentCrew;
}

Date MyFlight::getDate() {
    return m_flightDate;
}

string MyFlight::getSource() {
    return m_src;
}

string MyFlight::getDestination() {
    return m_dst;
}

string MyFlight::getID() {
    return m_ID;
}

bool MyFlight::checkEnoughSits(Classes cls) {
    switch (cls) {
        case FIRST_CLASS:
            return m_plane->getMaxFirstClass() > m_res.size();
        case SECOND_CLASS:
            return m_plane->getMaxEconomyClass() > m_res.size();
        default:
            throw invalid_argument("Class type is invalid! try again!");
    }
}

void MyFlight::setM_plane(MyPlane *plane) {
    m_plane = plane;
}

void MyFlight::setM_res(const list<Reservation *> &res) {
    m_res = res;
}

void MyFlight::setM_currentCrew(const list<Employee *> &currentCrew) {
    m_currentCrew = currentCrew;
}

void MyFlight::addCrewMember(MyEmployee *e) {
    m_currentCrew.push_back(e);
}

void MyFlight::setM_flightDate(const Date &flightDate) {
    m_flightDate = flightDate;
}

void MyFlight::setM_src(const string &src) {
    m_src = src;
}

void MyFlight::setM_dst(const string &dst) {
    m_dst = dst;
}

void MyFlight::setM_ID(const string &ID) {
    m_ID = ID;
}

void MyFlight::addReservation(Reservation *r) {
    m_res.push_back(r);
}

MyFlight::~MyFlight() {
}

MyPlane *MyFlight::getPlane() {
    return m_plane;
}
