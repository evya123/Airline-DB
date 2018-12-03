//
// Created by cs on 11/27/18.
//

#ifndef EX2_CUSTOMERFACTORY_H
#define EX2_CUSTOMERFACTORY_H

#include "AbsFactory.h"
#include "../MyCustomer.h"


class CustomerFactory : public AbsFactory<MyCustomer> {
public:
    virtual MyCustomer *create();

    void setFull_name(const string &full_name);

    void setPriority(int m_priority);

    virtual ~CustomerFactory();

private:
    list<MyCustomer *> listToFree;
    string m_full_name;
    int m_priority;
};


#endif //EX2_CUSTOMERFACTORY_H
