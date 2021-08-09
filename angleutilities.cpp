#include "angleutilities.h"


/// Constructor (from a double)
Angle::Angle(double totalDegree)
{
    m_totalDegree = totalDegree;
}


// Constructor (from three values and a bool to choose between hour angle and degree angle)
Angle::Angle(bool isHour, int degree, int minute, double seconde)
{
    try
    {
        if (isHour == true)
        {
            if (degree < -360 || degree > 360)
                throw Error(ErrorPriority::Warning, ErrorType::InvalidAngleInput, "Entrée incorrect pour construire cette angle,\ndegré en dehors de l'intervalle");

            if (minute < 0 || minute >= 60)
                throw Error(ErrorPriority::Warning, ErrorType::InvalidAngleInput, "Entrée incorrect pour construire cette angle,\nminute en dehors de l'intervalle");

            if (seconde < 0 || seconde >= 60)
                throw Error(ErrorPriority::Warning, ErrorType::InvalidAngleInput, "Entrée incorrect pour construire cette angle,\nseconde en dehors de l'intervalle");
        }
        else
        {
            if (degree < 0 || 24 >= 360)
                throw Error(ErrorPriority::Warning, ErrorType::InvalidAngleInput, "Entrée incorrect pour construire cette angle,\ndegré en dehors de l'intervalle");

            if (minute < 0 || minute >= 60)
                throw Error(ErrorPriority::Warning, ErrorType::InvalidAngleInput, "Entrée incorrect pour construire cette angle,\nminute en dehors de l'intervalle");

            if (seconde < 0 || seconde >= 60)
                throw Error(ErrorPriority::Warning, ErrorType::InvalidAngleInput, "Entrée incorrect pour construire cette angle,\nseconde en dehors de l'intervalle");
        }

        if (isHour == true)
        {
            m_totalDegree = ( degree * 15 ) + ( minute / 60 ) + ( seconde / 3600 );
        }
        else
        {
            m_totalDegree = degree + ( minute / 60 ) + ( seconde / 3600 );
        }
    }
    catch (Error e)
    {
        e.printMessage();
    }
}


// Constructor (from a string, eg: "00h00m00.00s" or "00°00'00.00"")
Angle::Angle(QString strAngle)
{
    try
    {
        if (strAngle.count() >= 12 && strAngle.count() < 14)
        {
            bool isHour = false;
            size_t indexD = 0, indexM = 0;

            // Index of 'h' or '°'
            if (strAngle.count('h') == 1)
            {
                indexD = strAngle.indexOf('h');
                isHour = true;
            }
            else if (strAngle.count(QChar(176)) == 1)
                indexD = strAngle.indexOf(QChar(176));
            else
                throw Error(ErrorPriority::Warning, ErrorType::InvalidAngleString, "Chaine incorrect pour construire cette angle,\ncharactère 'h' ou '°' manquant");

            if (isHour == true)
            {
                // Index of 'm'
                if (strAngle.count('m') == 1)
                    indexM = strAngle.indexOf('m');
                else
                    throw Error(ErrorPriority::Warning, ErrorType::InvalidAngleString, "Chaine incorrect pour construire cette angle,\ncharactère 'm' manquant");

                // Index of 's'
                if (strAngle.count('s') != 1)
                    throw Error(ErrorPriority::Warning, ErrorType::InvalidAngleString, "Chaine incorrect pour construire cette angle,\ncharactère 's' manquant");
            }
            else
            {
                // Index of '\''
                if (strAngle.count(QChar(39)) == 1)
                    indexM = strAngle.indexOf(QChar(39));
                else
                    throw Error(ErrorPriority::Warning, ErrorType::InvalidAngleString, "Chaine incorrect pour construire cette angle,\ncharactère '\'' manquant");

                // Index of '\"'
                if (strAngle.count(QChar(34)) != 1)
                    throw Error(ErrorPriority::Warning, ErrorType::InvalidAngleString, "Chaine incorrect pour construire cette angle,\ncharactère '\"' manquant");
            }

            if (isHour == true)
            {
                setHour(strAngle.mid(0, indexD).toInt());
                setHourMinute(strAngle.mid(indexD + 1, 2).toInt());
                setHourSecond(strAngle.mid(indexM + 1, 5).toDouble());
            }
            else
            {
                setDegree(strAngle.mid(0, indexD).toInt());
                setDegreeMinute(strAngle.mid(indexD + 1, 2).toInt());
                setDegreeSecond(strAngle.mid(indexM + 1, 5).toDouble());
            }
        }
        else
        {
            throw Error(ErrorPriority::Warning, ErrorType::InvalidAngleString, "Chaine incorrect pour construire cette angle,\ntaille impossible");
        }
    }
    catch (Error e)
    {
        e.printMessage();
    }
}


double Angle::getTotalDegree() const
{
    return m_totalDegree;
}


double Angle::getTotalHour() const
{
    if (m_totalDegree >= 0.00)
    {
        return m_totalDegree / 15;
    }
    else
    {
        return (360.00 + m_totalDegree) / 15;
    }
}


void Angle::setTotalDegree(double totalDegree)
{
    if (totalDegree <= -360.00 || totalDegree >= 360.00)
    {
        throw Error(ErrorPriority::Warning, ErrorType::AngleError, QString("Il est impossible d'utiliser cette valeur de degré pour un angle : " + QString::number(totalDegree)));
        return;
    }

    m_totalDegree = totalDegree;
}


void Angle::setTotalHour(double totalHour)
{
    if (totalHour < 0.00 || totalHour >= 24.00)
    {
        throw Error(ErrorPriority::Warning, ErrorType::AngleError, QString("Il est impossible d'utiliser cette valeur d'heure pour un angle : " + QString::number(totalHour)));
        return;
    }

    m_totalDegree = totalHour * 15;
}


// Return Degree part from degree angle
int Angle::getDegree() const
{
    return std::trunc(m_totalDegree);
}


// Return Minute part from degree angle
int Angle::getDegreeMinute() const
{
    return std::abs(std::trunc((m_totalDegree - getDegree()) * 60));
}


// Return Second part from degree angle
double Angle::getDegreeSecond() const
{
    return ((std::abs((m_totalDegree - getDegree()) * 60) - getDegreeMinute()) * 60);
}


// Return Degree angle in the form of string eg: "00°00'00.00""
QString Angle::getDegreeAngle() const
{
    QString strAngle =
            QString::number(getDegree()).rightJustified(2, '0')
            + QChar(176)
            + QString::number(getDegreeMinute()).rightJustified(2, '0')
            + QChar(39)
            + QString::number(getDegreeSecond(), 'f', 2).rightJustified(5, '0')
            + QChar(34);
    return strAngle;
}


void Angle::setDegree(int degree)
{
    if (degree <= -360 || degree >= 360)
    {
        throw Error(ErrorPriority::Warning, ErrorType::AngleError, QString("Il est impossible d'utiliser cette valeur de degré pour un angle : " + QString::number(degree)));
        return;
    }

    m_totalDegree -= getDegree();
    m_totalDegree += degree;
}


void Angle::setDegreeMinute(int minute)
{
    if (minute < 0 || minute >= 60)
    {
        throw Error(ErrorPriority::Warning, ErrorType::AngleError, QString("Il est impossible d'utiliser cette valeur de minute pour un angle : " + QString::number(minute)));
        return;
    }

    if (m_totalDegree >= 0)
    {
        m_totalDegree -= (double)getDegreeMinute() / 60.00;
        m_totalDegree += (double)minute / 60.00;
    }
    else
    {
        m_totalDegree += (double)getDegreeMinute() / 60.00;
        m_totalDegree -= (double)minute / 60.00;
    }
}


void Angle::setDegreeSecond(double second)
{
    if (second < 0.00 || second >= 60.00)
    {
        throw Error(ErrorPriority::Warning, ErrorType::AngleError, QString("Il est impossible d'utiliser cette valeur de seconde pour un angle : " + QString::number(second)));
        return;
    }

    if (m_totalDegree >= 0)
    {
        m_totalDegree -= getDegreeSecond() / 3600;
        m_totalDegree += second / 3600;
    }
    else
    {
        m_totalDegree += getDegreeSecond() / 3600;
        m_totalDegree -= second / 3600;
    }
}


// Return Hour part from hour angle
int Angle::getHour() const
{
    if (m_totalDegree >= 0.00)
    {
        return std::trunc(m_totalDegree / 15);
    }
    else
    {
        return std::trunc((360.00 + m_totalDegree) / 15);
    }
}


// Return Minute part from hour angle
int Angle::getHourMinute() const
{
    return std::abs(std::trunc((getTotalHour() - std::trunc(getTotalHour())) * 60));
}


// Return Second part from hour angle
double Angle::getHourSecond() const
{
    return (std::abs((getTotalHour() - std::trunc(getTotalHour())) * 60) - getHourMinute()) * 60;
}


// Return Hour angle in the form of string eg: "00h00m00.00s"
QString Angle::getHourAngle() const
{
    QString strAngle =
            QString::number(getHour()).rightJustified(2, '0')
            + "h"
            + QString::number(getHourMinute()).rightJustified(2, '0')
            + "m"
            + QString::number(getHourSecond(), 'f', 2).rightJustified(5, '0')
            + "s";
    return strAngle;
}


void Angle::setHour(int hour)
{
    if (hour < 0 || hour >= 24)
    {
        throw Error(ErrorPriority::Warning, ErrorType::AngleError, QString("Il est impossible d'utiliser cette valeur d'heure pour un angle : " + QString::number(hour)));
        return;
    }

    m_totalDegree -= 15 * getHour();
    m_totalDegree += 15 * hour;
}


void Angle::setHourMinute(int minute)
{
    if (minute < 0 || minute >= 60)
    {
        throw Error(ErrorPriority::Warning, ErrorType::AngleError, QString("Il est impossible d'utiliser cette valeur dde minute pour un angle : " + QString::number(minute)));
        return;
    }

    m_totalDegree -= 15 * (double)getHourMinute() / 60.00;
    m_totalDegree += 15 * (double)minute / 60.00;
}


void Angle::setHourSecond(double seconde)
{
    if (seconde < 0.00 || seconde >= 60.00)
    {
        throw Error(ErrorPriority::Warning, ErrorType::AngleError, QString("Il est impossible d'utiliser cette valeur de seconde pour un angle : " + QString::number(seconde)));
        return;
    }

    m_totalDegree -= 15 * getHourSecond() / 3600;
    m_totalDegree += 15 * seconde / 3600;
}













