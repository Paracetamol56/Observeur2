#ifndef EQUATORIALPOSTITION_H
#define EQUATORIALPOSTITION_H


///
/// \brief The HourAngle class
///
class HourAngle
{
private:
    int m_hour;
    int m_minute;
    double m_second;

public:
    HourAngle(int h, int m, double s);
    HourAngle(double hour);

    int getHour() const;
    int getMinute() const;
    double getSecond() const;

    double getTotalHour() const;
    double getTotalMinute() const;
    double getTotalSecond() const;

    void setHour(int h);
    void setMinute(int m);
    void setSecond(double s);
};


///
/// \brief The DegreeAngle class
///
class DegreeAngle
{
public:
    DegreeAngle();
};


///
/// \brief The RadianAngle class
///
class RadianAngle
{
public:
    RadianAngle();
};


///
/// \brief The EquatorialPostition class
///
class EquatorialPostition
{
private:
    HourAngle m_rightAscension;
    DegreeAngle m_declination;

public:
    EquatorialPostition(HourAngle ra, DegreeAngle dec);

    HourAngle getRightAscension() const;
    DegreeAngle getDeclination() const;

    void setRightAscension(HourAngle);
    void setDeclination(DegreeAngle);
};

#endif // EQUATORIALPOSTITION_H
