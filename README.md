# GooglePolylineCoder
Lib for Google Polyline encoding/decoding

# Installation
To install simply copy contents of GooglePolylineCoder to 
your project (*.pro file is not required).

# Usage
Use of GPoint is not compulsory. The class is used inside encode 
function and no users are obliged to use it on their own.
To encode your point simply pass its longitude and latitude to 
encode() function. The factor parameter is optional and by default
is set to 1e5 (as is in [Google's documentation](https://developers.google.com/maps/documentation/utilities/polylinealgorithm)).
Don't forget, that when you encode a route you only have to encode the first point, and then you encode difference 
between the next points (check link above for more info).
