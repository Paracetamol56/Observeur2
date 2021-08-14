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
    HorizontalPosition horizontalCoordinates(0.00, 0.00);

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

    if (settings.contains("position"))
    {
        settings.beginGroup("position");
        latitude = Angle(settings.value("latitude").toString());
        if (settings.value("latitudeDirection").toString() == "S")
        {
            latitude.setTotalDegree(0.00 - latitude.getTotalDegree());
        }

        longitude = Angle(settings.value("longitude").toString());
        if (settings.value("longitudeDirection") == "O")
        {
            longitude.setTotalDegree(360.00 - longitude.getTotalDegree());
        }
        settings.endGroup();
    }
    else
    {
        //todo : error
    }

    // Create date object
    Date date(day, month, year, hour, minute, second);
    // Compute the julian day for the specified date
    double julianDay = date.Date::toJulianDay();

    double timeT = (std::trunc(julianDay) - 2451545.0 + (julianDay - std::trunc(julianDay))) / 36525;

    double gmst = date.toGMST();

    double deltaNutation;

    // Compute epsilon
    double epsilon;
    {
        double Ls = 280.4565 + timeT * 36000.7698   + timeT * timeT * 0.000303;
        Ls = Ls >= 0 ? (Ls - (long)(Ls * 0.0027777778) * 360) : ((Ls - (long)(Ls * 0.0027777778) * 360) + 360);

        double Lm = 218.3164 + timeT * 481267.8812  - timeT * timeT * timeT * 0.001599;
        Lm = Lm >= 0 ? (Lm - (long)(Lm * 0.0027777778) * 360) : ((Lm - (long)(Lm * 0.0027777778) * 360) + 360);

        double Ms = 357.5291 + timeT * 35999.0503   - timeT * timeT * timeT * 0.000154;
        Ms = Ms >= 0 ? (Ms - (long)(Ms * 0.0027777778) * 360) : ((Ms - (long)(Ms * 0.0027777778) * 360) + 360);

        double Mm = 134.9634 + timeT * 477198.8675  + timeT * timeT * 0.008721;
        Ms = Mm >= 0 ? (Mm - (long)(Mm * 0.0027777778) * 360) : ((Mm - (long)(Mm * 0.0027777778) * 360) + 360);

        double omega = 125.0443 - timeT * 1934.1363 + timeT * 0.008721;
        omega = omega >= 0 ? (omega - (long)(omega * 0.0027777778) * 360) : ((omega - (long)(omega * 0.0027777778) * 360) + 360);

        // Delta Phi
        double dNutation =
        -(17.1996 + 0.01742 * timeT) * std::sin(omega)
        -(1.3187  + 0.00016 * timeT) * std::sin(2 * Ls)
        - 0.2274 * std::sin(2 * Lm)
        + 0.2062 * std::sin(2 * omega)
        +(0.1426  - 0.00034 * timeT) * std::sin(Ms)
        + 0.0712 * std::sin(Mm)
        -(0.0517  - 0.00012 * timeT) * std::sin(2*Ls+Ms)
        - 0.0386 * std::sin(2 * Lm-omega)
        - 0.0301 * std::sin(2 * Lm+Mm)
        + 0.0217 * std::sin(2 * Ls-Ms)
        - 0.0158 * std::sin(2 * Ls-2*Lm+Mm)
        + 0.0129 * std::sin(2 * Ls-omega)
        + 0.0123 * std::sin(2 * Lm-Mm);

        deltaNutation = dNutation;

        // Delta Eps
        double dObliquity =
        +(9.2025  + 0.00089 * timeT) * std::cos(omega)
        +(0.5736  - 0.00031 * timeT) * std::cos(2*Ls)
        + 0.0977 * std::cos(2*Lm)
        - 0.0895 * std::cos(2*omega)
        + 0.0224 * std::cos(2*Ls+Ms)
        + 0.0200 * std::cos(2*Lm-omega)
        + 0.0129 * std::cos(2*Lm + Mm)
        - 0.0095 * std::cos(2*Ls-Ms)
        - 0.0070 * std::cos(2*Ls-omega);

        double eps0 = ((double)23 * 3600 + (double)26 * 60 + (double)21.448) - timeT * 46.8150 - timeT * timeT * 0.00059+ timeT * timeT * timeT * 0.001813;

        epsilon = eps0 + dObliquity;
        epsilon = (double)(epsilon) * 0.0002777778;
    }



    // Apparent sideral time in hours
    double theta0 = gmst + (deltaNutation / 15 * std::cos(epsilon)) / 3600;

    // Geographic latitude in floating degrees
    double phi = latitude.getTotalDegree();

    // Local angle in floating degrees
    double H = (theta0 - longitude.getTotalHour() - m_rightAscension.getTotalHour()) * 15;

    horizontalCoordinates.setAzimuth(Angle((std::atan2(std::sin(H), std::cos(H)*std::sin(phi)-std::tan(m_declination.getTotalDegree())*std::cos(phi))) * 57.2957795131 + 180));

    horizontalCoordinates.setAltitude(Angle((std::asin(std::sin(phi)*std::sin(m_declination.getTotalDegree()) + std::cos(phi)*std::cos(m_declination.getTotalDegree())*std::cos(H))) * 57.2957795131));

    return horizontalCoordinates;
}

















