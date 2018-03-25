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

std::string encodeNumber(int number)
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

std::string gpolyline::encode(gpolyline::GPoint point)
{
    point <<= 1;
    if(point.getLongitude() < 0)
        point.inverseLongitude();
    if(point.getLatitude() < 0)
        point.inverseLatitude();

    std::string result = "";
    result += encodeNumber(point.getLatitude());
    result += encodeNumber(point.getLongitude());

    return result;
}

std::string gpolyline::encode(double longitude, double latitude, double factor)
{
    gpolyline::GPoint p(gpolyline::round(longitude*factor), gpolyline::round(latitude*factor));

    return gpolyline::encode(p);
}

int decodeNumber(const std::string &polyline, std::size_t &index)
{
    std::int8_t byte = 0;
    int shift = 0;
    int result = 0;

    do
    {
        byte = polyline[index++] - 63;
        result |= (byte & 0x1f) << shift;
        shift += 5;
    }
    while(byte >= 0x20);

    return ((result & 1) ? ~(result >> 1) : (result >> 1));

}

void gpolyline::decode(const std::string &polyline, gpolyline::pointCallback callback, double factor) throw(std::invalid_argument)
{
    if(factor == 0)
        throw std::invalid_argument("Factor can't be zero!");

    std::size_t index = 0;
    std::size_t length = polyline.size();
    while(index < length)
    {
        int latitude = decodeNumber(polyline, index);
        int longitude = decodeNumber(polyline, index);

        callback(double(longitude)/factor, double(latitude)/factor);
    }
}

void gpolyline::decode(const std::string &polyline, gpolyline::DecoderFunctor *functor, double factor) throw(std::invalid_argument)
{
    if(factor == 0)
        throw std::invalid_argument("Factor can't be zero!");

    std::size_t index = 0;
    std::size_t length = polyline.size();
    while(index < length)
    {
        int latitude = decodeNumber(polyline, index);
        int longitude = decodeNumber(polyline, index);

        functor->operator ()(double(longitude)/factor, double(latitude)/factor);
    }
}
