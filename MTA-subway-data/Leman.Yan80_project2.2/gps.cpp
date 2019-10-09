/******************************************************************************
  Title          : gps.cpp
  Author         : Leman Yan
  Created on     : April 8, 2019
  Description    : The implementation to a GPS class that encapsulates GPS points
  Purpose        :
  Usage          :
  Build with     : The haversine implementation is attributed to Stewart Weiss.
  Modifications  :

******************************************************************************/
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#include "gps.h"

const double R = 6372.8;
const double TO_RAD= M_PI / 180.0;

/*
GPS::GPS()
{
	longitude=0;
	latitude=0;
}
*/

GPS::GPS( double lon, double lat) throw(BadPoint)
{
	if( (lon >= -180 && lon <= 180) && (lat >= -90 && lat <= 90) ) //Valid values for lon & lat
	{
		longitude=lon;
		latitude=lat;
	}
	else
	{
		throw(BadPoint());
	}
}

GPS::GPS( const GPS & location)
{
	if( (location.longitude >= -180 && location.longitude <= 180) && (location.latitude >= -90 && location.latitude <= 90) ) //Valid values for lon & lat
	{
		longitude=location.longitude;
		latitude=location.latitude;
	}
	else
	{
		throw(BadPoint());
	}
}

void GPS::operator=(const GPS & location )
{
 longitude=location.longitude;
 latitude=location.latitude;
}

//private member function
double haversine(double lat1, double lon1, double lat2, double lon2) 
{
  lat1 = TO_RAD * lat1;
  lat2 = TO_RAD * lat2;
  lon1 = TO_RAD * lon1;
  lon2 = TO_RAD * lon2;
  double dLat = (lat2 - lat1) / 2;
  double dLon = (lon2 - lon1) / 2;
  double a = sin(dLat);
  double b = sin(dLon);
  return 2 * R * asin(sqrt(a*a + cos(lat1) * cos(lat2)*b*b));
}

double distance_between( GPS point1, GPS point2)
{
	return haversine(point1.latitude, point1.longitude, point2.latitude, point2.longitude);
}


ostream & operator<< ( ostream & out, GPS point )
{
	out<<"POINT( "<<point.longitude<<" "<<point.latitude<<")";
	return out; 
}





