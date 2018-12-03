//
// Created by cs on 11/26/18.
//

#include "IdFactory.h"

//##########Global Counters##########
int e_counter = 1; //Employee counter
int p_counter = 1; //Plane counter
int f_counter = 1; // Flight counter
int c_counter = 1; // Customer counter
int r_counter = 1; //Reservation counter
//####################################

string IdFactory::createID(Types type) {
    string tmp;
    switch (type) {
        case EID :
            tmp = "EID" + to_string(e_counter);
            e_counter++;
            return tmp;
        case CID:
            tmp = "CID" + to_string(c_counter);
            c_counter++;
            return tmp;
        case PID :
            tmp = "PID" + to_string(p_counter);
            p_counter++;
            return tmp;
        case FID :
            tmp = "FID" + to_string(f_counter);
            f_counter++;
            return tmp;
        case RID:
            tmp = "RID" + to_string(r_counter);
            r_counter++;
            return tmp;
        default:
            throw runtime_error("Creating ID error!");
    }
}

IdFactory::~IdFactory() {

}

int IdFactory::getEcounter() {
    return e_counter;
}

int IdFactory::getCcounter() {
    return c_counter;
}

int IdFactory::getFcounter() {
    return f_counter;
}

int IdFactory::getRcounter() {
    return r_counter;
}

int IdFactory::getPcounter() {
    return p_counter;
}

void IdFactory::setEcounter(int e) {
    e_counter = e;
}

void IdFactory::setCcounter(int c) {
    c_counter = c;
}

void IdFactory::setFcounter(int f) {
    f_counter = f;
}

void IdFactory::setRcounter(int r) {
    r_counter = r;
}

void IdFactory::setPcounter(int p) {
    p_counter = p;
}
