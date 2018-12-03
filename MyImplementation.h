//
// Created by cs on 11/25/18.
//

#ifndef EX2_MYIMPLEMENTATION_H
#define EX2_MYIMPLEMENTATION_H

#include "interface.h"
#include "./Factory/EmployeeFactory.h"
#include "./Factory/FlightFactory.h"
#include "./Factory/CustomerFactory.h"
#include "./Factory/ReservationFactory.h"
#include "./Factory/PlaneFactory.h"
#include "WriteReadObj.h"

#define COUNTERS_FILE_NAME "counters.txt"
#define EMPLOYEES_FILE_NAME "employees.txt"
#define RESERVATION_FILE_NAME "Reservations.txt"
#define PLANE_FILE_NAME "planes.txt"
#define FLIGHTS_FILE_NAME "Flights.txt"
#define CUSTOMERS_FILE_NAME "Customers.txt"

typedef struct extractFromPlane {
    list<Employee *> crewForFlight;
    Plane *p;
} extractFromPlane;

class MyImplementation : public Ex2 {
public:
    MyImplementation();

    virtual Employee *addEmployee(
            int seniority,
            int birth_year,
            string employer_id,
            Jobs title);

    virtual Employee *getEmployee(string id);

    virtual Plane *addPlane(
            int model_number,
            map<Jobs, int> crew_needed,
            map<Classes, int> max_passangers);

    virtual Plane *getPlane(string id);

    virtual Flight *addFlight(
            int model_number,
            Date date,
            string source,
            string destination);

    virtual Flight *getFlight(string id);

    virtual Customer *addCustomer(
            string full_name,
            int priority);

    virtual Customer *getCustomer(string id);

    virtual Reservation *addResevation(
            string customerId,
            string flightId,
            Classes cls,
            int max_baggage);

    virtual Reservation *getReservation(string id);


    virtual void exit();

    virtual ~MyImplementation() {}

private:
    //#############Help function#############
    list<Employee *> getCrew(map<Jobs, int> &, Date &);

    bool isEmployeeAvailableOn(Date &, MyEmployee *);

    MyFlight *enoughSits(string &, Classes &);

    MyCustomer *checkCustomerExist(string &);

    Employee *checkIfEmployeeExist(string &);

    void setExtractFromPlain(int modelNumber, Date &);

    MyCustomer *createDummyC(MyCustomer *);

    MyFlight *createDummyF(MyFlight *);

    Employee *checkIfRegistered(string eId);

    void loadToDB();

    void initFactory();

    void destroy();

    //#### Factory for creating the data ####
    EmployeeFactory *m_eFactory;
    FlightFactory *m_fFactory;
    CustomerFactory *m_cFactory;
    ReservationFactory *m_rFactory;
    PlaneFactory *m_pFactory;

    //###### Maps for holding the data ######
    map <Jobs, map<string, Employee *>> m_eMap;
    map<int, map<string, Plane *>> m_pMap;
    map<string, Reservation *> m_rMap;
    map <Date, map<string, Flight *>> m_fMap;
    map<string, Customer *> m_cMap;

    //###### List of pointers to free #######

    list<ID *> m_listToFree;
    //###### Struct for Extracting Data ######
    extractFromPlane m_details;

    bool loadedOrNot = false;
    WriteReadObj m_ioObj;
};


#endif //EX2_MYIMPLEMENTATION_H
