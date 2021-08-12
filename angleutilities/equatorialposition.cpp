#include "equatorialposition.h"

EquatorialPosition::EquatorialPosition(Angle rightAscension, Angle declination)
    : m_rightAscension(rightAscension), m_declination(declination)
{
}

Angle EquatorialPosition::getRightAscension() const
{
    return m_rightAscension;
}

Angle EquatorialPosition::getDeclination() const
{
    return m_declination;
}

void EquatorialPosition::setRightAscension(Angle rightAscension)
{
    m_rightAscension = rightAscension;
}

void EquatorialPosition::setDeclination(Angle declination)
{
    m_declination = declination;
}

Angle EquatorialPosition::getDistance(EquatorialPosition *other)
{
    // DISTANCE = arccos(sin(δ1)*sin(δ2)+ cos(δ1)*cos(δ2)*cos(α1 - α2))

    double distanceRad = acos(
        sin(m_declination.getTotalRadian()) * sin(other->getDeclination().getTotalRadian()) + cos(m_declination.getTotalRadian()) * cos(other->getDeclination().getTotalRadian()) * cos(m_rightAscension.getTotalRadian() - other->getRightAscension().getTotalRadian()));

    return Angle(distanceRad * 180.00 / PI);
}


HorizontalPosition EquatorialPosition::toHorizontalPosition(double julianDay, Angle latitude, Angle longitude)
{
    double julianday = 2451558.50000;
    double midnight = std::floor(julianday) + 0.5;
    double days_since_midnight = julianday - midnight;
    double hours_since_midnight = days_since_midnight * 24;
    double days_since_epoch = julianday - 2451545.0;
    double centuries_since_epoch = days_since_epoch / 36525;
    double whole_days_since_epoch = midnight - 2451545.0;

    double GMST = 6.697374558
                + 0.06570982441908 * whole_days_since_epoch
                + 1.00273790935 * hours_since_midnight
                + 0.000026 * centuries_since_epoch * centuries_since_epoch;

    qDebug() << GMST;

    return HorizontalPosition(Angle(0.00), Angle(0.00));
}
