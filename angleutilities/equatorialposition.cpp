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


HorizontalPosition EquatorialPosition::toHorizontalPosition(unsigned int day, unsigned int month, unsigned int year, unsigned int hour, unsigned int minute, unsigned int second)
{
    // Get observer position on earth
    QSettings settings;

    // Keys stored in settings :
    /*
     * "theme" ("dark" or "light")
     * group "position" :
     *      - latitude (double totalDegree)
     *      - longitude (double totalDegree)
     *      - altitude (int)
     */

    Angle latitude(0.00);
    Angle longitude(0.00);

    settings.beginGroup("position");
    if (settings.contains("latitude") && settings.contains("longitude"))
    {
        latitude = Angle(settings.value("latitude").toDouble());
        if (settings.value("latitudeDirection").toString() == "S")
        {
            latitude.setTotalDegree(0.00 - latitude.getTotalDegree());
        }

        longitude = Angle(settings.value("longitude").toDouble());
        if (settings.value("longitudeDirection") == "O")
        {
            longitude.setTotalDegree(360.00 - longitude.getTotalDegree());
        }
    }
    else
    {
        //todo : error
    }
    settings.endGroup();

    // Create date object
    Date date(day, month, year, hour, minute, second);
    // Greenwich Mean Sidereal Time in hour
    double gmst = date.toGMST();
    // Local sideral time in hour
    double lst = std::fmod(gmst - longitude.getTotalHour() * (24.0 / 360.0), 24);
    // Local hour angle in degree
    Angle lha((lst - m_rightAscension.getTotalHour()) * 15);

    // Compute azimuth and altitude
    // Altitude a
    Angle a(0.00);
    a.setTotalRadian(asin(sin(m_declination.getTotalRadian()) * sin(latitude.getTotalRadian()) + cos(m_declination.getTotalRadian()) * cos(latitude.getTotalRadian()) * cos(lha.getTotalRadian())));
    // Azimuth A
    Angle A(0.00);
    A.setTotalRadian(asin(- sin(lha.getTotalRadian() * cos(m_declination.getTotalRadian()) / cos(a.getTotalRadian()))));

    HorizontalPosition horizontalCoordinates(A, a);

    return horizontalCoordinates;
}

















