# GooglePolylineCoder
Lib for Google Polyline encoding/decoding

# Installation
To install simply copy contents of GooglePolylineCoder to 
your project (*.pro file is not required).

# Usage
Use of GPoint is not compulsory. The class is used inside encode 
function and no users are obliged to use it on their own.

## Encoding
To encode your point simply pass its longitude and latitude to 
encode() function. The factor parameter is optional and by default
is set to 1e5 (as is in [Google's documentation](https://developers.google.com/maps/documentation/utilities/polylinealgorithm)).
Don't forget, that when you encode a route you only have to encode the first point, and then you encode difference 
between the next points (check link above for more info).

## Decoding
To decode polyline pass it to decode() function. Decode() also expects a callback function that will be executed every time
a new point is decoded. The prototype for this callback:

```c++
void callback(double longitude, double latitude);
```

Be aware, that the first point is decoded as is, the rest points in route are not exact coordinates, but shifts relative to a previous point.
The factor parameter is optional and by default is set to 1e5.
