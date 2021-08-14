#include "date.h"

Date::Date(unsigned int day, unsigned int month, unsigned int year,
           unsigned int hour, unsigned int minute, unsigned int second)
    : m_day(day), m_month(month), m_year(year)
    , m_hour(hour), m_minute(minute), m_second(second)
{}


double Date::toJulianDay()
{
    if( m_month <= 2 )
    {
        m_year = m_year - 1;
        m_month = m_month + 12;
    }

    long A = int(m_year / 100.0);
    long B = 2 - A + int(A / 4);

    // Julian day part
    int julianDayDay  = int(365.25*(m_year+4716)) + int(30.6001*(m_month+1)) + (int)(m_day) + B - 1524.5;
    // Julian time part
    double julianDayTime = 0.5 + m_hour / 24 + m_minute / 1440 + m_second / 86400;

    // Adjust day and time if needed
    if( julianDayTime >= 1 )
    {
        julianDayTime -=1;

        julianDayDay += 1;
    }

    double julianDay =julianDayDay + julianDayTime;

    return (julianDay);
}


double Date::toGMST()
{
    double meanGreenwichSiderealTime;

    Date date0 = *this;
    date0.m_hour = 0;
    date0.m_minute = 0;
    date0.m_second = 0;
    double julianDay0 = date0.toJulianDay();

    double timeT0 = (std::trunc(julianDay0) - 2451545.0 + (julianDay0 - std::trunc(julianDay0))) / 36525;
    double timeT0Squared = timeT0*timeT0;
    double timeT0Cubed = timeT0Squared*timeT0;

    // Sideral time at midnight
    double theta0 = 100.46061837 + (36000.770053608*timeT0) + (0.000387933*timeT0Squared) - (timeT0Cubed/38710000);
    theta0 = (theta0) >= 0 ? ((theta0) - (long)((theta0) * 0.0027777778) * 360) : (((theta0) - (long)((theta0) * 0.0027777778) * 360) + 360);
    theta0 = theta0 * 0.0666666667;

    // Sideral time of day
    double thetaH = 1.00273790935 * ((double)m_hour * 3600 + (double)m_minute * 60 + (double)m_second);
    thetaH = (double)thetaH * 0.0002777778;

    // Add time at midnight and time of day
    meanGreenwichSiderealTime = theta0 + thetaH;
    meanGreenwichSiderealTime = meanGreenwichSiderealTime >= 0 ? (meanGreenwichSiderealTime - (long)(meanGreenwichSiderealTime * 0.0416666667) * 24) : (meanGreenwichSiderealTime + 24);

    return meanGreenwichSiderealTime;
}
