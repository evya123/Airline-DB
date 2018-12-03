//
// Created by cs on 11/26/18.
//

#ifndef EX2_IDFACTORY_H
#define EX2_IDFACTORY_H

#include "../interface.h"

enum Types {
    EID, PID, FID, CID, RID
};


class IdFactory {
public:
    virtual string createID(Types type);

//############Getters############
    int getEcounter();

    int getCcounter();

    int getFcounter();

    int getRcounter();

    int getPcounter();

//############Setters############
    void setEcounter(int);

    void setCcounter(int);

    void setFcounter(int);

    void setRcounter(int);

    void setPcounter(int);

    virtual ~IdFactory();
};

#endif //EX2_IDFACTORY_H
