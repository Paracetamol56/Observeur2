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
    void setTotalDegree(double totalDegree = 0.00);
    void setTotalHour(double totalHour = 0.00);

    // Degree angle getters
    int getDegree() const;
    int getDegreeMinute() const;
    double getDegreeSecond() const;
    QString getDegreeAngle() const;

    // Degree angle setters
    void setDegree(int degree = 0);
    void setDegreeMinute(int minute = 0);
    void setDegreeSecond(double second = 0.00);

    // Hour angle getters
    int getHour() const;
    int getHourMinute() const;
    double getHourSecond() const;
    QString getHourAngle() const;

    // Hour angle setters
    void setHour(int hour = 0);
    void setHourMinute(int minute = 0);
    void setHourSecond(double seconde = 0.00);
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
