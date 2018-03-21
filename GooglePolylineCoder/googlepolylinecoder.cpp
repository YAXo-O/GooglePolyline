#include <stdexcept>
#include "googlepolylinecoder.h"

gpolyline::GPoint::GPoint(int _longitude, int _latitude): longitude(_longitude), latitude(_latitude)
{
}

gpolyline::GPoint::GPoint(const gpolyline::GPoint &other): longitude(other.longitude), latitude(other.latitude)
{
}

gpolyline::GPoint &gpolyline::GPoint::operator=(const gpolyline::GPoint &other)
{
    longitude = other.longitude;
    latitude = other.latitude;

    return *this;
}

gpolyline::GPoint &gpolyline::GPoint::operator*=(double factor)
{
    longitude *= factor;
    latitude *= factor;

    return *this;
}

gpolyline::GPoint &gpolyline::GPoint::operator/=(double factor) throw(std::invalid_argument)
{
    if(factor == 0)
        throw std::invalid_argument("Zero division!");

    longitude /= factor;
    longitude /= factor;

    return *this;
}

gpolyline::GPoint &gpolyline::GPoint::operator+=(const gpolyline::GPoint &other)
{
    longitude += other.longitude;
    latitude += other.latitude;

    return *this;
}

gpolyline::GPoint &gpolyline::GPoint::operator-=(const gpolyline::GPoint &other)
{
    longitude -= other.longitude;
    latitude -= other.latitude;

    return *this;
}

gpolyline::GPoint &gpolyline::GPoint::operator<<=(unsigned shiftRate)
{
    longitude <<= shiftRate;
    latitude <<= shiftRate;

    return *this;
}

gpolyline::GPoint &gpolyline::GPoint::operator>>=(unsigned shiftRate)
{
    longitude >>= shiftRate;
    latitude >>= shiftRate;

    return *this;
}

gpolyline::GPoint gpolyline::GPoint::operator*(double factor) const
{
    return gpolyline::GPoint(longitude*factor, latitude*factor);
}

gpolyline::GPoint gpolyline::GPoint::operator/(double factor) const throw(std::invalid_argument)
{
    if(factor == 0)
        throw std::invalid_argument("Zero division!");

    return gpolyline::GPoint(longitude/factor, latitude/factor);
}

gpolyline::GPoint gpolyline::GPoint::operator+(const gpolyline::GPoint &other) const
{
    return gpolyline::GPoint(longitude + other.longitude, latitude + other.latitude);
}

gpolyline::GPoint gpolyline::GPoint::operator-(const gpolyline::GPoint &other) const
{
    return gpolyline::GPoint(longitude - other.longitude, latitude - other.latitude);
}

gpolyline::GPoint gpolyline::GPoint::operator<<(unsigned shiftRate)
{
    return gpolyline::GPoint(longitude << shiftRate, latitude << shiftRate);
}

gpolyline::GPoint gpolyline::GPoint::operator>>(unsigned shiftRate)
{
    return gpolyline::GPoint(longitude >> shiftRate, latitude >> shiftRate);
}

void gpolyline::GPoint::setLongitude(int _longitude)
{
    longitude = _longitude;
}

void gpolyline::GPoint::setLatitude(int _latitude)
{
    latitude = _latitude;
}

int gpolyline::GPoint::getLongitude() const
{
    return longitude;
}

int gpolyline::GPoint::getLatitude() const
{
    return latitude;
}

void gpolyline::GPoint::inverseLongitude()
{
    longitude = ~longitude;
}

void gpolyline::GPoint::inverseLatitude()
{
    latitude = ~latitude;
}

int gpolyline::round(double value)
{
    return value >= 0 ? int(value + .5f) : int(value - .5f);
}

std::string gpolyline::encode(gpolyline::GPoint point)
{
    point <<= 1;
    if(point.getLongitude() < 0)
        point.inverseLongitude();
    if(point.getLatitude() < 0)
        point.inverseLatitude();

    std::string result = "";
    result += gpolyline::encodeNumber(point.getLongitude());
    result += gpolyline::encodeNumber(point.getLatitude());

    return result;
}

std::string gpolyline::encodeNumber(int number)
{
    std::string result = "";
    while(number >= 0x20)
    {
        result += (0x20 | (number & 0x1f)) + 63; //  0x1f == 0001 1111 => block of five
        number >>= 5;
    }
    result += number + 63;

    return result;
}

std::string gpolyline::encode(double longitude, double latitude, double factor)
{
    gpolyline::GPoint p(gpolyline::round(longitude*factor), gpolyline::round(latitude*factor));

    return gpolyline::encode(p);
}
