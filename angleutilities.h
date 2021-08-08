#ifndef ANGLEUTILITIES_H
#define ANGLEUTILITIES_H

// Utilities
#include <QString>
#include <math.h>

// Error handling
#include "errorhandler.h"

// Define an angle
class Angle
{
private:
    double m_totalDegree = 0.00;

public:
    Angle(double totalDegree = 0.00);
    Angle(bool isHour = false, int degree = 0, int minute = 0, double seconde = 0);
    Angle(QString strAngle = "");

    double getTotalDegree() const;
    double getTotalHour() const;
    void setTotalDegree(double totalDegree);

    int getDegree() const;
    int getDegreeMinute() const;
    double getDegreeSecond() const;
    QString getDegreeAngle() const;

    int getHour() const;
    int getHourMinute() const;
    double getHourSecond() const;
    QString getHourAngle() const;
};

// Define a celestial position in equatorial coordinate system
class Position
{
private:
    Angle m_rightAscension;
    Angle m_declination;

public:
    Position(Angle rightAscension, Angle declination);

    Angle getRightAscension() const;
    Angle getDeclination() const;
    void setRightAscension(Angle);
    void setDeclination(Angle);

    Angle getDistance(Angle *other = nullptr);
};

#endif // ANGLEUTILITIES_H
