/**
 * Created on Tue Jul 31 2021
 * 
 * Copyright (c) 2021 - Mathéo G - All Right Reserved
 * 
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Observeur2 */

#include "horizontalposition.h"

HorizontalPosition::HorizontalPosition(Angle azimuth, Angle altitude)
    : m_azimuth(azimuth), m_altitude(altitude)
{
}

Angle HorizontalPosition::getAzimuth() const
{
    return m_azimuth;
}

Angle HorizontalPosition::getAltitude() const
{
    return m_altitude;
}

void HorizontalPosition::setAzimuth(Angle azimuth)
{
    m_azimuth = azimuth;
}

void HorizontalPosition::setAltitude(Angle altitude)
{
    m_altitude = altitude;
}

Angle HorizontalPosition::getDistance(HorizontalPosition *other)
{
    // DISTANCE = arccos(sin(δ1)*sin(δ2)+ cos(δ1)*cos(δ2)*cos(α1 - α2))

    double distanceRad = acos(
        sin(m_altitude.getTotalRadian()) * sin(other->getAltitude().getTotalRadian()) + cos(m_altitude.getTotalRadian()) * cos(other->getAltitude().getTotalRadian()) * cos(m_azimuth.getTotalRadian() - other->getAzimuth().getTotalRadian()));

    return Angle(distanceRad * 180.00 / PI);
}