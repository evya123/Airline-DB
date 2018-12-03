//

#include "MyImplementation.h"

MyImplementation::MyImplementation() {
    m_ioObj.loadCounters(COUNTERS_FILE_NAME);
    initFactory();

}

Employee *MyImplementation::addEmployee(int seniority, int birth_year, string employer_id, Jobs title) {
    loadToDB();
    m_eFactory->setM_seniority(seniority);
    m_eFactory->setM_date(to_string(birth_year));
    m_eFactory->setM_title(title);
    //Checks if the employer is registered, if so returns his pointer. otherwise nullptr
    Employee *employer = checkIfRegistered(employer_id);

    m_eFactory->setM_employer(employer);
    MyEmployee *ret = new MyEmployee();
    m_listToFree.push_back(ret);
    ret = m_eFactory->create();
    //Checks if this type of job is already exist. if so, append to the right map.
    //Otherwise create the right pair and insert it.
    auto it = m_eMap.find(title);
    if (it != m_eMap.end()) {
        it->second.insert(make_pair(ret->getID(), ret));
        return ret;
    }
    map < string, Employee * > tmp;
    tmp.insert(make_pair(ret->getID(), ret));
    m_eMap.insert(make_pair(title, tmp));
    return ret;
}

Employee *MyImplementation::getEmployee(string id) {
    loadToDB();
    auto it = m_eMap.begin();
    while (it != m_eMap.end()) {
        auto employerIt = it->second.find(id);
        if (employerIt != it->second.end())
            return employerIt->second;
        it++;
    }
    return nullptr;
}

Plane *MyImplementation::addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {
    loadToDB();
    m_pFactory->setModel_number(model_number);
    m_pFactory->setCrew_needed(crew_needed);
    m_pFactory->setMax_passangers(max_passangers);
    Plane *ret = m_pFactory->create();
    auto it = m_pMap.find(model_number);
    if (it != m_pMap.end()) {
        it->second.insert(make_pair(ret->getID(), ret));
        return ret;
    }
    map < string, Plane * > tmp;
    tmp.insert(make_pair(ret->getID(), ret));
    m_pMap.insert(make_pair(model_number, tmp));
    return ret;
}

Plane *MyImplementation::getPlane(string id) {
    loadToDB();
    auto it = m_pMap.begin();
    while (it != m_pMap.end()) {
        auto ret = it->second.find(id);
        if (ret != it->second.end())
            return ret->second;
        it++;
    }
    return nullptr;
}

Flight *MyImplementation::addFlight(int model_number, Date date, string source, string destination) {
    loadToDB();
    setExtractFromPlain(model_number, date);
    ///Set the values ready for creating the object
    m_fFactory->setM_dst(destination);
    m_fFactory->setM_src(source);
    m_fFactory->setM_date(date);
    m_fFactory->setCrewForFlight(m_details.crewForFlight);
    m_details.crewForFlight.clear();
    m_fFactory->setPlane(m_details.p);
    Flight *ret = m_fFactory->create();
    //check if there are any flights on this date. If so, add this flight to the right pair,
    //if not, create a pair!
    auto fIt = m_fMap.find(date);
    if (fIt == m_fMap.end()) {
        map < string, Flight * > tmp;
        tmp.insert(make_pair(ret->getID(), ret));
        m_fMap.insert(make_pair(date, tmp));
        return ret;
    }
    fIt->second.insert(make_pair(ret->getID(), ret));
    return ret;
}

Flight *MyImplementation::getFlight(string id) {
    loadToDB();
    auto it = m_fMap.begin();
    while (it != m_fMap.end()) {
        auto fIt = it->second.find(id);
        if (fIt != it->second.end())
            return fIt->second;
        ++it;
    }
    return nullptr;
}

Customer *MyImplementation::addCustomer(string full_name, int priority) {
    loadToDB();
    m_cFactory->setFull_name(full_name);
    m_cFactory->setPriority(priority);
    MyCustomer *ret = m_cFactory->create();
    m_cMap.insert(make_pair(ret->getID(), ret));
    return ret;
}

Customer *MyImplementation::getCustomer(string id) {
    loadToDB();
    auto it = m_cMap.find(id);
    if (it == m_cMap.end())
        return nullptr;
    return it->second;
}

Reservation *MyImplementation::addResevation(string customerId, string flightId, Classes cls, int max_baggage) {
    loadToDB();
    //Check if customer id exist , if so, returns a pointer.
    // If not, throw an exception
    MyCustomer *customer = checkCustomerExist(customerId);
    //Check if there are enough sits in the right Class, if not, throw exception.
    //Otherwise returns a pointer to the flight
    MyFlight *rightFlight = enoughSits(flightId, cls);

    //Set the values ready for creating the object
    m_rFactory->setCls(cls);
    m_rFactory->setMax_baggage(max_baggage);
    m_rFactory->setM_customer(createDummyC(customer));
    m_rFactory->setM_flight(createDummyF(rightFlight));
    Reservation *ret = m_rFactory->create();
    m_rMap.insert(make_pair(ret->getID(), ret));
    //Insert the reservation to customer
    customer->addRes(ret);
    rightFlight->addReservation(ret);
    return ret;
}

Reservation *MyImplementation::getReservation(string id) {
    loadToDB();
    auto it = m_rMap.find(id);
    if (it == m_rMap.end())
        return nullptr;
    return it->second;
}

list<Employee *> MyImplementation::getCrew(map<Jobs, int> &neededCrew, Date &date) {
    list < Employee * > ret;
    // get the sum of workers
    int sum = 0;
    for (pair<Jobs, int> p : neededCrew)
        sum += p.second;
    //for every Job, check if available
    for (pair<Jobs, int> jobs : neededCrew) {
        int memberFound = 0, membersNeeded = jobs.second;
        if (!membersNeeded)
            continue;
        auto it = m_eMap.find(jobs.first); // will receive a iterator to pair<Jobs, map<string, Employee>>
        if (it == m_eMap.end()) { //Didn't find a crew, throw exception
            throw logic_error("No available crew on this date!");
        } //Did find the right crew!
        for (pair < string, Employee * > employee : it->second) {
            if (isEmployeeAvailableOn(date, dynamic_cast<MyEmployee *>(employee.second))) {
                ret.push_back(employee.second);
                if (++memberFound == membersNeeded)
                    break;
            }
        }
    }
    if (ret.size() != sum) { //There is not enough crew members available, throw exception
        throw logic_error("No available crew on this date!");;
    }
    return ret;
}

bool MyImplementation::isEmployeeAvailableOn(Date &d, MyEmployee *e) {
    if (e->getM_flightDate().empty()) {
        e->setFlightDate(d);
        return true;
    }
    auto tmpIter = e->getM_flightDate().begin();
    while (tmpIter != e->getM_flightDate().end()) {
        if (*tmpIter == d)
            return false;
        tmpIter++;
    }
    e->setFlightDate(d);
    return true;
}

MyFlight *MyImplementation::enoughSits(string &flightId, Classes &cls) {
    auto it = m_fMap.begin();
    while (it != m_fMap.end()) {
        auto fIt = it->second.find(flightId); //For every date, check if this flight exist.
        if (fIt != it->second.end()) { //flight was found!
            MyFlight *tmpF = dynamic_cast<MyFlight *>(fIt->second);
            if (tmpF->checkEnoughSits(cls)) {
                return dynamic_cast<MyFlight *>(fIt->second);
            }
            throw logic_error("Not enough sits!");
        }
        it++;
    }
    throw logic_error("Oops...Something went wrong. Flight was not found!");
}

MyCustomer *MyImplementation::checkCustomerExist(string &customerId) {
    auto it = m_cMap.find(customerId);
    if (it != m_cMap.end())
        return dynamic_cast<MyCustomer *>(it->second);
    throw logic_error("ERROR: customer is not exist!");
}

Employee *MyImplementation::checkIfEmployeeExist(string &employerID) {
    auto it = m_eMap.begin();
    while (it != m_eMap.end()) {
        auto employerIt = it->second.find(employerID);
        if (employerIt != it->second.end())
            return employerIt->second;
        it++;
    }
    return nullptr;
}

void MyImplementation::setExtractFromPlain(int modelNumber, Date &date) {
    list < Employee * > crewForFlight;
    bool foundFlag = true;
    crewForFlight.clear();
    //Check for matching plane in the plane list. If not found, throw exception.
    auto it = m_pMap.find(modelNumber);
    if (it == m_pMap.end())
        throw logic_error("No matching plane with the current model number!");
    else { //Plane of this model is found. Now check for available crew and extract it.
        auto pIt = it->second.begin();
        while (pIt != it->second.end() && foundFlag) {
            for (pair < string, Plane * > pPlane : it->second) {
                if (!(dynamic_cast<MyPlane *>(pPlane.second)->isOccupied(date))) { //There is a free plane on this date
                    dynamic_cast<MyPlane *>(pPlane.second)->addFlightDate(date);
                    map<Jobs, int> crew = (dynamic_cast<MyPlane *>(pPlane.second)->getCrewNeeded());
                    m_details.crewForFlight = getCrew(crew, date);
                    m_details.p = pPlane.second;
                    foundFlag = false;
                    break;
                }
            }
            ++pIt;
        }
    }
    if (foundFlag)
        throw logic_error("There are no free planes on this date!");
}

MyCustomer *MyImplementation::createDummyC(MyCustomer *cP) {
    MyCustomer *dummyCustomer = new MyCustomer();
    dummyCustomer->setM_ID(cP->getID());
    dummyCustomer->setM_fullName(cP->getFullName());
    dummyCustomer->setM_priority(cP->getPriority());
    m_listToFree.push_back(dummyCustomer);
    return dummyCustomer;
}

MyFlight *MyImplementation::createDummyF(MyFlight *fP) {
    MyFlight *dummyFlight = new MyFlight();
    dummyFlight->setM_ID(fP->getID());
    dummyFlight->setM_currentCrew(fP->getAssignedCrew());
    dummyFlight->setM_plane(fP->getPlane());
    dummyFlight->setM_dst(fP->getDestination());
    dummyFlight->setM_src(fP->getSource());
    dummyFlight->setM_flightDate(fP->getDate());
    m_listToFree.push_back(dummyFlight);
    return dummyFlight;
}

Employee *MyImplementation::checkIfRegistered(string employer_id) {
    //Checks if the employer is registered, if so returns his pointer. otherwise nullptr
    Employee *employer;
    if (employer_id.find_first_not_of("EID0123456789") != string::npos)
        employer = nullptr;
    else
        employer = checkIfEmployeeExist(employer_id);
    return employer;
}

void MyImplementation::initFactory() {
    m_pFactory = new PlaneFactory();
    m_rFactory = new ReservationFactory();
    m_cFactory = new CustomerFactory();
    m_fFactory = new FlightFactory();
    m_eFactory = new EmployeeFactory();
}

void MyImplementation::loadToDB() {
    if (!loadedOrNot) {
        m_ioObj.loadAll(m_eMap, m_cMap, m_rMap, m_fMap, m_pMap);
        loadedOrNot = true;
    }
}

void MyImplementation::destroy() {
    for (auto it : m_listToFree)
        delete (it);
    delete (m_rFactory);
    delete (m_fFactory);
    delete (m_eFactory);
    delete (m_pFactory);
    delete (m_cFactory);
}

void MyImplementation::exit() {
    m_ioObj.saveAll(m_eMap, m_cMap, m_rMap, m_fMap, m_pMap);
    destroy();

}

