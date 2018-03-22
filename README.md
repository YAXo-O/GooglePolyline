# GooglePolylineCoder
Lib for Google Polyline encoding/decoding.
Based on a [js version](https://github.com/mapbox/polyline).

# Installation
To install simply copy contents of GooglePolylineCoder to 
your project (*.pro file is not required).

# Usage
Use of GPoint is not compulsory. The class is used inside encode 
function and no users are obliged to use it on their own.

## Encoding
```C++
std::string encode(double longitude, double latitude, double factor = 1e5);
```
To encode your point simply pass its longitude and latitude to 
encode() function. The factor parameter is optional and by default
is set to 1e5 (as is in [Google's documentation](https://developers.google.com/maps/documentation/utilities/polylinealgorithm)).
Don't forget that when you encode a route you only have to encode the first point and then you encode difference 
between the next points (check link above for more info).

## Decoding
```C++
void decode(const std::string &polyline, pointCallback callback, double factor = 1e5) throw(std::invalid_argument); // (1)
void decode(const std::string &polyline, DecoderFunctor *functor, double factor = 1e5) throw(std::invalid_argument); // (2)
```
To decode use either of the versions of decode() from above.
Polyline parameter is a string representing encoded route, factor as in decode is optional and is set to 1e5 as suggested by Google.
Exception is thrown when factor is set to zero.
The difference between decode() functoins is in the way thay treat a point. 

Version (1) sends a newly decoded point as 
arguments of a callback function. A callback function's prototype:
```C++
void pointCallback(double longitude, double latitude);
```

Version (2) sends a newly decoded point as arguments of operator() of a functor.
Functors are expected for more difficult tasks with decoded points. To create a new functor simply inherit a new class from DecoderFunctor
and implement its operator():
```C++
void operator()(double longitude, double latitude);
```

