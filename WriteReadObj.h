//
// Created by cs on 11/29/18.
//

#ifndef EX2_WRITEREADOBJ_H
#define EX2_WRITEREADOBJ_H

#include <fstream>
#include <functional>
#include "string"
#include "map"
#include "interface.h"
#include "Factory/IdFactory.h"
#include "vector"
#include "MyFlight.h"
#include "MyCustomer.h"

using namespace std;

class WriteReadObj {
public:
    //################################# To File #################################
    bool eMapToFile(const string &filename, const map <Jobs, map<string, Employee *>> &fileMap);

    bool pMapToFile(const string &filename, const map<int, map<string, Plane *>> &fileMap);

    bool rMapToFile(const string &filename, const map<string, Reservation *> &fileMap);

    bool fMapToFile(const string &filename, const map <Date, map<string, Flight *>> &fileMap);

    bool cMapToFile(const string &filename, const map<string, Customer *> &fileMap);

    bool saveCounters(const string &filename);

    bool saveAll(map <Jobs, map<string, Employee *>> &, map<string, Customer *> &, map<string, Reservation *> &,
                 map <Date, map<string, Flight *>> &, map<int, map<string, Plane *>> &);

    //################################# From File #################################
    bool eMapFromFile(const string &filename, map <Jobs, map<string, Employee *>> &fileMap);

    bool pMapFromFile(const string &filename, map<int, map<string, Plane *>> &fileMap,
                      list<MyPlane *> &);

    bool rMapFromFile(const string &filename, map<string, Reservation *> &fileMap, list<Customer *> &,
                      list<MyFlight *> &fToRes);

    bool fMapFromFile(const string &filename, map <Date, map<string, Flight *>> &fileMap,
                      list<MyFlight *> &, list<MyPlane *> &);

    bool cMapFromFile(const string &filename, map<string, Customer *> &fileMap, list<Customer *> &);

    bool loadCounters(const string &filename);

    bool loadAll(map <Jobs, map<string, Employee *>> &, map<string, Customer *> &, map<string, Reservation *> &,
                 map <Date, map<string, Flight *>> &, map<int, map<string, Plane *>> &);

    virtual ~WriteReadObj();

private:
    //################################# Helpers #################################
    template<class K, class U>
    void genericBuild(map <K, U> &, const map <K, U> &);

    map <Jobs, map<string, Employee *>> buildEmployees(const vector <string> &vec);

    map<string, Customer *> buildCustomers(const vector <string> &vec, list<Customer *> &);

    map<string, Reservation *> buildReservations(const vector <string> &vec,
                                                 list<Customer *> &,
                                                 list<MyFlight *> &);

    map<int, map<string, Plane *>> buildPlanes(const vector <string> &vec, list<MyPlane *> &);

    map <Date, map<string, Flight *>> buildFlights(const vector <string> &vec,
                                                   list<MyFlight *> &,
                                                   list<MyPlane *> &);

    Jobs getTitle(int key);

    Classes getClass(int key);

    void splitString(vector <string> &v_str, const string &str, char ch);

    vector <string> fileToVec(const string &filename);

    Customer *createDummyC(MyCustomer *);

    Flight *createDummyF(MyFlight *);

    template<class T>
    void destroy(list<T *> &);

    list<ID *> m_listToFree;
    map<MyFlight *, map < string, list < string>>>
    m_employedByDate;
    IdFactory m_helper;
};


#endif //EX2_WRITEREADOBJ_H
