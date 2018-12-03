//
// Created by cs on 11/27/18.
//

#ifndef EX2_ABSFACTORY_H
#define EX2_ABSFACTORY_H

#include "IdFactory.h"

template<typename T>
class AbsFactory {
protected:
    virtual T *create() = 0;

    virtual ~AbsFactory() {};
    IdFactory m_idFactory;
};

#endif //EX2_ABSFACTORY_H
