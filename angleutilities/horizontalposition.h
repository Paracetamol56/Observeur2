#ifndef HORIZONTALPOSITION_H
#define HORIZONTALPOSITION_H

// Utilities
#include <QString>
#include <math.h>
#include "angleutilities/angle.h"

#define PI 3.14159265358979323846264338327950288419716939937510582

// Debug output
#include <QDebug>

// Error handling
#include "errorhandler.h"

// Define a celestial position in horizontal coordinate system
class HorizontalPosition
{
private:
    Angle m_azimuth;
    Angle m_altitude;

public:
    HorizontalPosition(Angle azimuth, Angle altitude);

    Angle getAzimuth() const;
    Angle getAltitude() const;
    void setAzimuth(Angle azimuth);
    void setAltitude(Angle altitude);

    Angle getDistance(HorizontalPosition *other = nullptr);
};

#endif // HORIZONTALPOSITION_H
