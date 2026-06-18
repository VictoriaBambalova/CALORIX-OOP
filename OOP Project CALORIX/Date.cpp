#include "Date.h"

#include <ctime>
#include <sstream>

Date::Date() : day(1), month(1), year(2000) {}

Date::Date(int day, int month, int year)
    : day(day), month(month), year(year) {
}

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

void Date::setDay(int day) {
    this->day = day;
}

void Date::setMonth(int month) {
    this->month = month;
}

void Date::setYear(int year) {
    this->year = year;
}

std::string Date::toString() const {
    std::ostringstream out;

    if (year < 10) {
        out << "000";
    }
    else if (year < 100) {
        out << "00";
    }
    else if (year < 1000) {
        out << "0";
    }

    out << year << "-";

    if (month < 10) {
        out << "0";
    }

    out << month << "-";

    if (day < 10) {
        out << "0";
    }

    out << day;

    return out.str();
}

Date Date::today() {
    std::time_t now = std::time(nullptr);
    std::tm localTime;

#ifdef _WIN32
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif

    return Date(
        localTime.tm_mday,
        localTime.tm_mon + 1,
        localTime.tm_year + 1900
    );
}

Date Date::fromString(const std::string& str) {
    int year = 2000;
    int month = 1;
    int day = 1;

    char dash1;
    char dash2;

    std::istringstream in(str);
    in >> year >> dash1 >> month >> dash2 >> day;

    return Date(day, month, year);
}