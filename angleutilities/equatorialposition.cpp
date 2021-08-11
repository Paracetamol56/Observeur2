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