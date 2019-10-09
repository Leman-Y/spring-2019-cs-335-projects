/******************************************************************************
  Title          : gps.h
  Author         : Stewart Weiss
  Created on     : April 18, 2018
  Description    : The interface to a GPS class that encapsulates GPS points
  Purpose        :
  Usage          :
  Build with     : Haversine private member function is added. 
  Modifications  : The haversine implementation is attributed to Stewart Weiss.

******************************************************************************/
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

#ifndef __GPS_H__
#define __GPS_H__

struct BadPoint{};


class GPS
{
public:
    //GPS();


    /** GPS() constructor
     *  If the longitude or latitude is out of range, it throws a BadPoint
     *  error.
     */
    GPS( double lon = 0, double lat = 0) throw (BadPoint);

    /** GPS() copy constructor
     *  If the longitude or latitude is out of range, it throws a BadPoint
     *  error.
     */
    GPS( const GPS & location);

    /** operator=() is the overloaded assignment operator)
     *  Copies the values in location to the current GPS object.
     *  @postcondition this* has the same values as location
     *  @param GPS [in] location]
     */
    void operator=(const GPS & location );

    /** distance_between() computes the distance between two points on a sphere
     *  given by their latitudes and longitudes expressed in decimal degrees.
     *  Distance is measured in kilometers.
     *  @precondition
     *  @param  GPS [in] point1
     *  @param  GPS [in] point2
     *  @return double  kilometer distance between two points
     */
    friend double distance_between( GPS point1, GPS point2);

    /** operator<<() prints the point in the same format as it is in the
     * input file, POINT( fixed_decimal fixed_decimal)
     */
    friend ostream & operator<< ( ostream & out, GPS point );


private:
    double longitude;
    double latitude;

	double haversine(double lat1, double lon1, double lat2, double lon2);
};


#endif /* __GPS_H__ */

