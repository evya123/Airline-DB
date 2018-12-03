cmake_minimum_required(VERSION 3.12)
project(ex2)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex2 main.cpp MyEmployee.cpp MyEmployee.h interface.h MyPlane.cpp MyPlane.h MyFlight.cpp MyFlight.h MyCustomer.cpp MyCustomer.h MyReservation.cpp MyReservation.h MyReservation.cpp MyReservation.h Date.cpp MyImplementation.cpp MyImplementation.h Factory/IdFactory.cpp Factory/IdFactory.h Factory/EmployeeFactory.cpp Factory/EmployeeFactory.h Factory/AbsFactory.h Factory/FlightFactory.cpp Factory/FlightFactory.h Factory/CustomerFactory.cpp Factory/CustomerFactory.h Factory/ReservationFactory.cpp Factory/ReservationFactory.h Factory/PlaneFactory.cpp Factory/PlaneFactory.h WriteReadObj.cpp WriteReadObj.h)