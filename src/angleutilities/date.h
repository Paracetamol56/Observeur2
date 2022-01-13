#ifndef DATE_H
#define DATE_H

#include <math.h>

class Date
{
public:
    unsigned int m_day = 0;
    unsigned int m_month = 0;
    unsigned int m_year = 0;

    unsigned int m_hour = 0;
    unsigned int m_minute = 0;
    unsigned int m_second = 0;

    Date(unsigned int day = 0, unsigned int month = 0, unsigned int year = 0,
         unsigned int hour = 0, unsigned int minute = 0, unsigned int second = 0);

    double toJulianDay();
    double toGMST(); // (Mean Greenwich Sidereal Time)
};

#endif // DATE_H
