#ifndef EQUATORIALPOSITION_H
#define EQUATORIALPOSITION_H

// Utilities
#include <QString>
#include <math.h>
#include "angleutilities/angle.h"
#include "angleutilities/horizontalposition.h"
#include "angleutilities/date.h"

#define PI 3.14159265358979323846264338327950288419716939937510582

// Debug output
#include <QDebug>

// Error handling
#include "errorhandler.h"

#include <QSettings>

// Define a celestial position in equatorial coordinate system
class EquatorialPosition
{
private:
    Angle m_rightAscension;
    Angle m_declination;

public:
    EquatorialPosition(Angle rightAscension, Angle declination);

    Angle getRightAscension() const;
    Angle getDeclination() const;
    void setRightAscension(Angle rightAscension);
    void setDeclination(Angle declination);

    Angle getDistance(EquatorialPosition *other = nullptr);

    HorizontalPosition toHorizontalPosition(Date date);
};

#endif // EQUATORIALPOSITION_H
