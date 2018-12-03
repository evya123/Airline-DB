# Airline DB

C++ based project, that mimic a real airline DB. 

## Getting Started

In order to use the program, compile using g++ (c++1y or greater). 
Now you have the option to add any of the folowing object :
1) Employee
2) Plane
3) Flight
4) Customer
5) Reservation
 
Currently, no deleteion, still developing this function. 
Known bugs:
1) After one test, the output file are created fine. On the seconed run there is a bug
loading crew members for a flight.
2) Becasue of dynamic cast while creating customer, there is a loss of bytes.

### Installing

compile using this command: g++ *.h -I . -I ./Factory *.cpp Factory/*.cpp Factory/*.h
In order to run the tests, just run the output file or use an IDE and run the main.cpp

## Versioning
Version # : v1.0 

## Authors

* **Evyatar Shtern** - *Initial work* - [Evyatar](https://github.com/evya123)
## Date
* **12/03/18**
