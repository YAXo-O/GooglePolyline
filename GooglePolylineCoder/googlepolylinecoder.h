#ifndef GOOGLEPOLYLINECODER_H
#define GOOGLEPOLYLINECODER_H

#include <stdexcept>
#include <string>

namespace gpolyline
{
    typedef void (*pointCallback)(double longitude, double latitude);

    class GPoint
    {
    public:
        GPoint() = default;
        GPoint(int longitude, int latitude);
        GPoint(const GPoint &other);
        ~GPoint() = default;

        GPoint &operator=(const GPoint &other);
        GPoint &operator*=(double factor);
        GPoint &operator/=(double factor) throw(std::invalid_argument);
        GPoint &operator+=(const GPoint &other);
        GPoint &operator-=(const GPoint &other);
        GPoint &operator<<=(unsigned shiftRate);
        GPoint &operator>>=(unsigned shiftRate);
        GPoint operator*(double factor) const;
        GPoint operator/(double factor) const throw(std::invalid_argument);
        GPoint operator+(const GPoint &other) const;
        GPoint operator-(const GPoint &other) const;
        GPoint operator<<(unsigned shiftRate);
        GPoint operator>>(unsigned shiftRate);

        void setLongitude(int longitude);
        void setLatitude(int latitude);
        int getLongitude() const;
        int getLatitude() const;

        void inverseLongitude();
        void inverseLatitude();

    private:
        int longitude;
        int latitude;
    };

    class DecoderFunctor
    {
    public:
        DecoderFunctor() = default;
        virtual ~DecoderFunctor() {}

        virtual void operator()(double longitude, double latitude) = 0;
    };

    int round(double value);

    std::string encode(GPoint point);
    std::string encode(double longitude, double latitude, double factor = 1e5);
    void decode(const std::string &polyline, pointCallback callback, double factor = 1e5) throw(std::invalid_argument);
    void decode(const std::string &polyline, DecoderFunctor *functor, double factor = 1e5) throw(std::invalid_argument);
}

#endif // GOOGLEPOLYLINECODER_H
