//
// Created by cs on 11/29/18.
//

#include "WriteReadObj.h"
#include <iostream>
#include "MyImplementation.h"
#include <algorithm>


//################################# To File #################################
bool WriteReadObj::eMapToFile(const string &filename,
                              const map <Jobs, map<string, Employee *>> &fileMap) {
    ofstream ofile;
    ofile.open(filename.c_str());
    if (!ofile)
        return false;           //file does not exist and cannot be created.
    auto iter = fileMap.begin();
    for (iter; iter != fileMap.end(); ++iter) {
        ofile << iter->first << ":\n";
        for (pair < string, Employee * > p : iter->second) {
            MyEmployee *tmp = dynamic_cast<MyEmployee *>(p.second);
            ofile << p.first << "|" << tmp->getBirthYear()
                  << "|";
            if (tmp->getEmployer() == nullptr)
                ofile << "NoEmployer" << "|" << tmp->getSeniority() << "\n";
            else
                ofile << tmp->getEmployer()->getID() << "|" << tmp->getSeniority() << "\n";
        }
    }
    return true;
}

bool WriteReadObj::pMapToFile(const string &filename, const map<int, map<string, Plane *>> &fileMap) {
    ofstream ofile;
    ofile.open(filename.c_str());
    if (!ofile)
        return false;           //file does not exist and cannot be created.
    auto iter = fileMap.begin();
    for (iter; iter != fileMap.end(); ++iter) {
        ofile << iter->first << ":\n";
        ofile << "Crew_Needed: \n";
        for (pair<Jobs, int> cP: iter->second.begin()->second->getCrewNeeded())
            ofile << cP.first << "|" << cP.second << "|";
        ofile << "\n";
        MyPlane *tmp;
        for (pair < string, Plane * > p : iter->second) {
            tmp = dynamic_cast<MyPlane *>(p.second);
            ofile << p.first << "|" << tmp->getMaxFirstClass()
                  << "|" << tmp->getMaxEconomyClass() << "|" << tmp->getModelNumber() << "\n";
        }

    }
    return true;
}

bool WriteReadObj::rMapToFile(const string &filename, const map<string, Reservation *> &fileMap) {
    ofstream ofile;
    ofile.open(filename.c_str());
    if (!ofile)
        return false;           //file does not exist and cannot be created.
    auto iter = fileMap.begin();
    for (pair < string, Reservation * > pR : fileMap) {
        Reservation *tmp = pR.second;
        ofile << pR.first << "|" << tmp->getCustomer()->getID() << "|"
              << tmp->getFlight()->getID() << "|" << tmp->getClass() << "|" << tmp->getMaxBaggage() << "\n";
    }
    return true;
}

bool WriteReadObj::fMapToFile(const string &filename, const map <Date, map<string, Flight *>> &fileMap) {
    ofstream ofile;
    ofile.open(filename.c_str());
    if (!ofile)
        return false;           //file does not exist and cannot be created.
    auto iter = fileMap.begin();
    for (iter; iter != fileMap.end(); ++iter) {
        ofile << iter->first.getDate() << ":\n";
        for (pair < string, Flight * > pF : iter->second) {
            Flight *tmp = pF.second;
            ofile << pF.first << "|" << tmp->getSource() << "|" << tmp->getDestination() << "\n";
            for (auto it : tmp->getAssignedCrew())
                ofile << it->getID() << "|";
            ofile << "\n";
            ofile << dynamic_cast<MyFlight *>(tmp)->getPlane()->getID() << "\n";
        }
    }
    return true;
}

bool WriteReadObj::cMapToFile(const string &filename, const map<string, Customer *> &fileMap) {
    ofstream ofile;
    ofile.open(filename.c_str());
    if (!ofile)
        return false;           //file does not exist and cannot be created.
    auto iter = fileMap.begin();
    for (iter; iter != fileMap.end(); ++iter) {
        ofile << iter->first << "|" << iter->second->getFullName() << "|" <<
              iter->second->getPriority() << "\n";
    }
    return true;
}

bool WriteReadObj::saveCounters(const string &filename) {
    ofstream ofile;
    ofile.open(filename.c_str());
    if (!ofile)
        return false;
    ofile << to_string(m_helper.getEcounter()) << "|" <<
          to_string(m_helper.getCcounter()) << "|" <<
          to_string(m_helper.getFcounter()) << "|" <<
          to_string(m_helper.getPcounter()) << "|" <<
          to_string(m_helper.getRcounter()) << "\n";

    return true;
}

bool WriteReadObj::saveAll(map <Jobs, map<string, Employee *>> &eMap, map<string, Customer *> &cMap,
                           map<string, Reservation *> &rMap, map <Date, map<string, Flight *>> &fMap,
                           map<int, map<string, Plane *>> &pMap) {
    eMapToFile(EMPLOYEES_FILE_NAME, eMap);
    pMapToFile(PLANE_FILE_NAME, pMap);
    rMapToFile(RESERVATION_FILE_NAME, rMap);
    fMapToFile(FLIGHTS_FILE_NAME, fMap);
    cMapToFile(CUSTOMERS_FILE_NAME, cMap);
    saveCounters(COUNTERS_FILE_NAME);
}
//################################# From File #################################

bool WriteReadObj::eMapFromFile(const string &filename, map <Jobs, map<string, Employee *>> &fileMap) {
    genericBuild(fileMap, buildEmployees(fileToVec(filename)));

}

bool WriteReadObj::cMapFromFile(const string &filename, map<string, Customer *> &fileMap, list<Customer *> &toRes) {
    genericBuild(fileMap, buildCustomers(fileToVec(filename), toRes));
}

bool WriteReadObj::rMapFromFile(const string &filename, map<string, Reservation *> &fileMap,
                                list<Customer *> &fromCustomerBuild, list<MyFlight *> &fToRes) {
    genericBuild(fileMap, buildReservations(fileToVec(filename), fromCustomerBuild, fToRes));
}

bool WriteReadObj::pMapFromFile(const string &filename, map<int, map<string, Plane *>> &fileMap,
                                list<MyPlane *> &pToFl) {
    genericBuild(fileMap, buildPlanes(fileToVec(filename), pToFl));
}

bool WriteReadObj::fMapFromFile(const string &filename, map <Date, map<string, Flight *>> &fileMap,
                                list<MyFlight *> &fToRes, list<MyPlane *> &pFromPl) {
    genericBuild(fileMap, buildFlights(fileToVec(filename), fToRes, pFromPl));
}

bool WriteReadObj::loadCounters(const string &filename) {
    ifstream ifile;
    ifile.open(filename.c_str());
    if (!ifile)
        return false;   //could not read the file.
    string line;
    vector <string> v_str;
    ifile >> line;
    splitString(v_str, line, '|');
    auto it = v_str.begin();

    m_helper.setEcounter(stoi(*it));
    it++;
    m_helper.setCcounter(stoi(*it));
    it++;
    m_helper.setFcounter(stoi(*it));
    it++;
    m_helper.setPcounter(stoi(*it));
    it++;
    m_helper.setRcounter(stoi(*it));

    return true;
}

bool WriteReadObj::loadAll(map <Jobs, map<string, Employee *>> &eMap, map<string, Customer *> &cMap,
                           map<string, Reservation *> &rMap, map <Date, map<string, Flight *>> &fMap,
                           map<int, map<string, Plane *>> &pMap) {
    //Each build will add another layer to one of the build below him
    list < MyPlane * > pToFlt;
    pMapFromFile(PLANE_FILE_NAME, pMap, pToFlt); //first to load. No dependencies
    list < MyFlight * > fToRes;
    fMapFromFile(FLIGHTS_FILE_NAME, fMap, fToRes,
                 pToFlt); //To be loaded before employees in order to get employed by date list
    list < Customer * > toRes;
    cMapFromFile(CUSTOMERS_FILE_NAME, cMap, toRes); //Need to be loaded before reservations.
    rMapFromFile(RESERVATION_FILE_NAME, rMap, toRes, fToRes);
    eMapFromFile(EMPLOYEES_FILE_NAME,
                 eMap); //Must be loaded after loading Flights! uses the crew member to decide if employed and when.
}

//################################# Helpers #################################
map <Jobs, map<string, Employee *>> WriteReadObj::buildEmployees(const vector <string> &vec) {
    map <Jobs, map<string, Employee *>> m_eMap;
    if (vec.empty())
        return m_eMap;
    map < string, Employee * > m_eMap2;
    auto jobIt = vec.begin();
    auto detailIt = vec.begin();
    detailIt++;
    while (jobIt != vec.end()) {
        Jobs title = getTitle(stoi(*jobIt));
        while ((*detailIt).find(":") == string::npos) {
            MyEmployee *tmp = new MyEmployee();
            tmp->setTitle(title);
            tmp->set_ID(*detailIt);
            detailIt++;
            tmp->set_Date(*detailIt);
            tmp->set_Employer(nullptr);
            detailIt += 2;
            tmp->set_seniority(stoi(*detailIt));

            if (!m_employedByDate.empty()) {
                for (pair < MyFlight * , map < string, list < string >> > p: m_employedByDate) {
                    for (pair <string, list<string>> innerP : p.second) {
                        list<string>::iterator employedIt;
                        employedIt = find(innerP.second.begin(), innerP.second.end(), tmp->getID());
                        if (employedIt != innerP.second.end()) {
                            tmp->setFlightDate(innerP.first);
                            p.first->addCrewMember(tmp);
                        }
                    }
                }
            }
            m_listToFree.push_back(tmp);
            m_eMap2.insert(make_pair(tmp->getID(), tmp));
            if ((++detailIt) == vec.end())
                break;
        }
        m_eMap.insert(make_pair(title, m_eMap2));
        m_eMap2.clear();
        jobIt = detailIt;
        if (jobIt == vec.end())
            break;
        ++detailIt;
    }

    jobIt = vec.begin();
    detailIt = vec.begin();
    auto iter = m_eMap.begin();
    auto searchIter = m_eMap.begin();
    detailIt += 3;
    jobIt++;
    while (jobIt != vec.end()) {
        if ((*detailIt) != "NoEmployer") {
            while (searchIter != m_eMap.end()) {
                auto tmpIt = searchIter->second.find(*detailIt);
                if (tmpIt == searchIter->second.end())
                    searchIter++;
                else {
                    auto tmpIt2 = iter->second.find(*jobIt);
                    if (tmpIt2 == iter->second.end())
                        iter++;
                    else {
                        dynamic_cast<MyEmployee *>(iter->second.find(*jobIt)->second)
                                ->set_Employer(tmpIt->second);
                        break;
                    }
                }
            }
            if ((detailIt += 2) == vec.end())
                break;
            if ((*detailIt).find(":") != string::npos)
                detailIt++;
            jobIt = detailIt;
            detailIt += 2;
        } else {
            if ((detailIt += 2) == vec.end())
                break;
            if ((*detailIt).find(":") != string::npos)
                detailIt++;
            jobIt = detailIt;
            detailIt += 2;
        }
        searchIter = m_eMap.begin();
        iter = m_eMap.begin();
    }

    return m_eMap;

}

map<string, Customer *> WriteReadObj::buildCustomers(const vector <string> &vec, list<Customer *> &toRes) {
    map < string, Customer * > ret;
    if (vec.empty())
        return ret;
    auto idIt = vec.begin();
    auto detailIt = vec.begin();
    while (idIt != vec.end()) {
        MyCustomer *tmp = new MyCustomer();
        tmp->setM_ID(*detailIt);
        detailIt++;
        string fName = *detailIt;
        ++detailIt;
        tmp->setM_fullName(fName + " " + *detailIt);
        detailIt++;
        tmp->setM_priority(stoi(*detailIt));
        toRes.push_back(tmp);
        m_listToFree.push_back(tmp);
        ret.insert(make_pair(*idIt, tmp));
        if (++detailIt == vec.end())
            break;
        idIt = detailIt;
    }

    return ret;
}

map<string, Reservation *> WriteReadObj::buildReservations(const vector <string> &vec, list<Customer *> &lst,
                                                           list<MyFlight *> &fToRes) {
    map < string, Reservation * > ret;
    if (vec.empty())
        return ret;
    auto idIt = vec.begin();
    auto detailIt = vec.begin();
    while (idIt != vec.end()) {
        MyReservation *tmp = new MyReservation();
        tmp->setM_id(*detailIt);
        ++detailIt;
        auto customerIt = lst.begin();
        while (customerIt != lst.end()) {
            if (dynamic_cast<MyCustomer *>(*customerIt)->getID() == *detailIt) {
                dynamic_cast<MyCustomer *>(*customerIt)->addRes(tmp);
                tmp->setM_customer(createDummyC(dynamic_cast<MyCustomer *>(*customerIt)));
            }
            customerIt++;
        }
        ++detailIt;

        auto flightIt = fToRes.begin();
        while (flightIt != fToRes.end()) {
            if ((*flightIt)->getID() == *detailIt) {
                tmp->setM_flight(createDummyF((*flightIt)));
                (*flightIt)->addReservation(tmp);
            }
            flightIt++;
        }
        ++detailIt;
        tmp->setM_class(getClass(stoi(*detailIt)));
        detailIt++;
        tmp->setM_maxBaggage(stoi(*detailIt));
        m_listToFree.push_back(tmp);
        ret.insert(make_pair(*idIt, tmp));
        if (++detailIt == vec.end())
            break;
        idIt = detailIt;
    }
    return ret;
}

map<int, map<string, Plane *>> WriteReadObj::buildPlanes(const vector <string> &vec, list<MyPlane *> &lst) {
    map<int, map<string, Plane *>> m_pMap;
    if (vec.empty())
        return m_pMap;
    map < string, Plane * > m_pMap2;
    bool checked = false;
    auto modelIt = vec.begin();
    auto detailIt = vec.begin();
    ++detailIt;
    while (modelIt != vec.end()) {
        while ((*detailIt).find(":") == string::npos) {
            MyPlane *tmp = new MyPlane();
            map<Jobs, int> neededCrew;
            if (!checked) {
                for (int i = 0; i < 5; ++i) {
                    Jobs j = getTitle(stoi(*detailIt));
                    int howMany = stoi(*(++detailIt));
                    neededCrew.insert((make_pair(j, howMany)));
                    ++detailIt;
                }
                checked = true;
            }
            tmp->setM_crewNeeded(neededCrew);
            tmp->setM_ID((*detailIt));
            tmp->setM_maxFirstClass(stoi(*(++detailIt)));
            tmp->setM_maxEconomyClass(stoi(*(++detailIt)));
            tmp->setM_modelNumber(stoi(*(++detailIt)));
            lst.push_back(tmp);
            m_listToFree.push_back(tmp);
            m_pMap2.insert(make_pair((tmp->getID()), tmp));
            if ((++detailIt) == vec.end())
                break;
        }
        checked = false;
        string tmpS = *modelIt;
        auto tmpIt = tmpS.begin();
        tmpS.erase(remove(tmpIt, tmpS.end(), ':'), tmpS.end());
        m_pMap.insert(make_pair(stoi(tmpS), m_pMap2));
        m_pMap2.clear();
        modelIt = detailIt;
        if (modelIt == vec.end())
            break;
        ++detailIt;
    }
    return m_pMap;
}

map <Date, map<string, Flight *>> WriteReadObj::buildFlights(const vector <string> &vec, list<MyFlight *> &fToRes,
                                                             list<MyPlane *> &pFromPl) {
    map <Date, map<string, Flight *>> ret;
    if (vec.empty())
        return ret;
    map < string, Flight * > m_fMap2;
    auto dateIt = vec.begin();
    auto detailsIt = vec.begin();
    ++detailsIt;
    while (dateIt != vec.end()) {
        string tmpS = *dateIt;
        auto tmpIt = tmpS.begin();
        tmpS.erase(remove(tmpIt, tmpS.end(), ':'), tmpS.end());
        while ((detailsIt != vec.end()) &&
               (*detailsIt).find(":") == string::npos) {
            MyFlight *tmp = new MyFlight();
            tmp->setM_flightDate(tmpS);
            tmp->setM_ID(*detailsIt);
            ++detailsIt;
            tmp->setM_src(*detailsIt);
            tmp->setM_dst(*(++detailsIt));
            ++detailsIt;
            list <string> employed;
            while ((*detailsIt).find("EID") != string::npos) {
                employed.push_back(*detailsIt);
                ++detailsIt;
            }
            map <string, list<string>> employedByDate;
            employedByDate.insert(make_pair(tmpS, employed));
            employed.clear();
            auto pIt = pFromPl.begin();
            while (pIt != pFromPl.end()) {
                if ((*pIt)->getID() == (*detailsIt)) {
                    tmp->setM_plane(*pIt);
                    Date tmpD(tmpS);
                    (*pIt)->addFlightDate(tmpD);
                    break;
                }
                ++pIt;
            }
            ++detailsIt;
            m_employedByDate.insert(make_pair(tmp, employedByDate));
            employedByDate.clear();
            m_listToFree.push_back(tmp);
            m_fMap2.insert(make_pair((tmp->getID()), tmp));
            fToRes.push_back(tmp);
            if (detailsIt == vec.end())
                break;
        }
        ret.insert(make_pair(Date(tmpS), m_fMap2));
        m_fMap2.clear();
        dateIt = detailsIt;
        if (dateIt == vec.end())
            break;
        ++detailsIt;
    }
    return ret;
}

vector <string> WriteReadObj::fileToVec(const string &filename) {
    ifstream ifile;
    try {
        ifile.open(filename);
    }
    catch (const ifstream::failure &e) {
        cout << "Exception opening/reading file";
    }
    string details;
    vector <string> v_str;
    while (ifile >> details)
        splitString(v_str, details, '|');
    return v_str;
}

template<class K, class U>
void WriteReadObj::genericBuild(map <K, U> &loadTo, const map <K, U> &func) {
    loadTo = func;
}

Jobs WriteReadObj::getTitle(int key) {
    switch (key) {
        case 0:
            return (MANAGER);
        case 1:
            return (NAVIGATOR);
        case 2:
            return (FLY_ATTENDANT);
        case 3:
            return (PILOT);
        case 4:
            return (OTHER);
        default:
            throw invalid_argument("Invalid job argument!");
    }
}

Classes WriteReadObj::getClass(int key) {
    switch (key) {
        case 0:
            return (FIRST_CLASS);
        case 1:
            return (SECOND_CLASS);
        default:
            throw invalid_argument("Bad argument!");
    }
}

void WriteReadObj::splitString(vector <string> &v_str, const string &str, char ch) {
    string sub;
    string::size_type pos = 0;
    string::size_type old_pos = 0;
    bool flag = true;

    while (flag) {
        pos = str.find_first_of(ch, pos);
        if (pos == string::npos) {
            flag = false;
            pos = str.size();
        }
        sub = str.substr(old_pos, pos - old_pos);  // Disregard the '.'
        if (sub.empty())
            continue;
        if (sub.find("Crew_Needed") != string::npos)
            continue;
        v_str.push_back(sub);
        old_pos = ++pos;
    }
}

Flight *WriteReadObj::createDummyF(MyFlight *fP) {
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

Customer *WriteReadObj::createDummyC(MyCustomer *cP) {
    MyCustomer *dummyCustomer = new MyCustomer();
    dummyCustomer->setM_ID(cP->getID());
    dummyCustomer->setM_fullName(cP->getFullName());
    dummyCustomer->setM_priority(cP->getPriority());
    m_listToFree.push_back(dummyCustomer);
    return dummyCustomer;
}

template<class T>
void WriteReadObj::destroy(list<T *> &lst) {
    for (auto it : lst)
        delete (it);
}

WriteReadObj::~WriteReadObj() {
    destroy(m_listToFree);
}
