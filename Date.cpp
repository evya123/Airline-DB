#include "interface.h"

#define AllowedCharGlobal "0123456789-"
#define AllowedChar "0123456789"
#define min 0
#define yearMax 9999
#define monthMax 12
#define dayMax 31
enum {
    yStart = 0, yLen = 4, mStart = 5, mLen = 2, dStart = 8, dLen = 2
};


Date::Date(string date) {
    //First we want to check if there are any unwanted chars, if so, throw exception.
    if (date.find_first_not_of(AllowedCharGlobal) != string::npos) {
        throw invalid_argument("Date is not as expected, try again!");
    }

    //Second we want to check the format is as needed.
    //For example: if the first 4 char are not numbers, throw exception (might be -yyyy-mm-dd)
    if (date.substr(yStart, yLen).find_first_not_of(AllowedChar) != string::npos) {
        throw invalid_argument("Date is not as expected, try again!");
    } else if (date.substr(mStart, mLen).find_first_not_of(AllowedChar) != string::npos) {
        throw invalid_argument("Date is not as expected, try again!");
    } else if (date.substr(dStart, dLen).find_first_not_of(AllowedChar) != string::npos) {
        throw invalid_argument("Date is not as expected, try again!");
    }

    //Third we want to check if the date make sense
    int year = stoi(date.substr(yStart, yLen));
    int month = stoi(date.substr(mStart, mLen));
    int day = stoi(date.substr(dStart, dLen));
    if (year > yearMax || year <= min)
        throw invalid_argument("Date is not as expected, try again!");
    else if (month > monthMax || month <= min)
        throw invalid_argument("Date is not as expected, try again!");
    else if (day > dayMax || day <= min)
        throw invalid_argument("Date is not as expected, try again!");

    //Date is good!
    this->date = date;
}


bool Date::operator<(const Date &d) const {

    for (int i = 0; i < date.length(); ++i) {
        if (date[i] != '-') {
            int tmp = (date[i] - '0') - (d.getDate()[i] - '0');
            if (tmp < 0)
                return true;
        }
    }
    return false;
}

bool Date::operator>(const Date &d) const {
    for (int i = 0; i < date.length(); ++i) {
        if (date[i] != '-') {
            int tmp = (date[i] - '0') - (d.getDate()[i] - '0');
            if (tmp > 0)
                return true;
        }
    }
    return false;
}

bool Date::operator==(const Date &d) const {
    return (date.compare(d.getDate()) == 0);
}
