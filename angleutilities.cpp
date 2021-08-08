#include "angleutilities.h"


///
/// Constructor (from a double)
/// \brief Angle::Angle
/// \param totalDegree
///
Angle::Angle(double totalDegree)
{
    m_totalDegree = totalDegree;
}


///
/// Constructor (from three values and a bool to choose between hour angle and degree angle)
/// \brief Angle::Angle
/// \param isHour
/// \param degree
/// \param minute
/// \param seconde
///
Angle::Angle(bool isHour, int degree, int minute, double seconde)
{
    if (isHour == true)
    {
        m_totalDegree = ( degree * 15 ) + ( minute / 60 ) + ( seconde / 3600 );
    }
    else
    {
        m_totalDegree = degree + ( minute / 60 ) + ( seconde / 3600 );
    }
}


///
/// Constructor (from a string, eg: "00h00m00.00s" or "00°00'00.00""
/// \brief Angle::Angle
/// \param strAngle
///
Angle::Angle(QString strAngle)
{
    if (strAngle.count() == 12)
    {
        if (strAngle.at(2) == 'h')
        {
            int hour = strAngle.mid(0, 1).toInt();
            int minute = strAngle.mid(3, 4).toInt();
            double seconde = strAngle.mid(6, 10).toDouble();
            m_totalDegree = ( hour * 15 ) + ( minute / 60 ) + ( seconde / 3600 );
        }
        else if (strAngle.at(2) == "°")
        {
            int degree = strAngle.mid(0, 1).toInt();
            int minute = strAngle.mid(3, 4).toInt();
            double seconde = strAngle.mid(6, 10).toDouble();
            m_totalDegree = degree + ( minute / 60 ) + ( seconde / 3600 );
        }
        else
        {
            //error
        }
    }
}


///
/// \brief Angle::getTotalDegree
/// \return Total degree
///
double Angle::getTotalDegree() const
{
    return m_totalDegree;
}


///
/// \brief Angle::getTotalHour
/// \return Total hour
///
double Angle::getTotalHour() const
{
    return (m_totalDegree / 15);
}


///
/// \brief Angle::setTotalDegree
/// \param totalDegree
///
void Angle::setTotalDegree(double totalDegree)
{
    m_totalDegree = totalDegree;
}


///
/// \brief Angle::getDegree
/// \return Degree part from degree angle
///
int Angle::getDegree() const
{
    return std::trunc(m_totalDegree);
}


///
/// \brief Angle::getDegreeMinute
/// \return Minute part from degree angle
///
int Angle::getDegreeMinute() const
{
    return (std::trunc((m_totalDegree - getDegree()) * 60));
}


///
/// \brief Angle::getDegreeSecond
/// \return Second part from degree angle
///
double Angle::getDegreeSecond() const
{
    return ((((m_totalDegree - getDegree()) * 60) - getDegreeMinute()) * 60);
}


///
/// \brief Angle::getDegreeAngle
/// \return Degree angle in the form of string eg: "00°00'00.00""
///
QString Angle::getDegreeAngle() const
{
    QString strAngle =
            QString::number(getDegree()).rightJustified(2, 0)
            + "°"
            + QString::number(getDegreeMinute()).rightJustified(2, 0)
            + "'"
            + QString::number(getDegreeSecond(), 'f', int(getHourSecond() * 100.0) % 10 ? 2 : 1).rightJustified(4, 0)
            + "\"";
    return strAngle;
}


///
/// \brief Angle::getDegree
/// \return Hour part from hour angle
///
int Angle::getHour() const
{
    return std::trunc(m_totalDegree / 15);
}


///
/// \brief Angle::getHourMinute
/// \return Minute part from hour angle
///
int Angle::getHourMinute() const
{
    return std::trunc(((m_totalDegree / 15) - getHour()) * 60);
}


///
/// \brief Angle::getHourSecond
/// \return Second part from hour angle
///
double Angle::getHourSecond() const
{
    return (((((m_totalDegree / 15) - getHour()) * 60) - getHourMinute()) * 60);
}


///
/// \brief Angle::getHourAngle
/// \return Hour angle in the form of string eg: "00h00m00.00s"
///
QString Angle::getHourAngle() const
{
    QString strAngle =
            QString::number(getHour()).rightJustified(2, 0)
            + "h"
            + QString::number(getHourMinute()).rightJustified(2, 0)
            + "m"
            + QString::number(getHourSecond(), 'f', int(getHourSecond() * 100.0) % 10 ? 2 : 1).rightJustified(4, 0)
            + "s";
    return strAngle;
}




























