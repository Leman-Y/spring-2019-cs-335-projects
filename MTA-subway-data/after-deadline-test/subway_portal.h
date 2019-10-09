/******************************************************************************
  Title          : subway_portal.h
  Author         : Leman Yan
  Created on     : May 4, 2019
  Description    : Interface file for the SubwayPortal object
  Purpose        : Encapsulates data and methods of a subway portal
  Usage          :
  Build with     :
  Modifications  :

******************************************************************************/

#ifndef _SUBWAY_PORTAL_H_
#define _SUBWAY_PORTAL_H_

#include <iostream>
#include <string>
#include <vector>

#include "subway_route.h"
#include "gps.h"

using namespace std;

struct Invalid_Portal_Data{};
/*	No redefinition
struct Invalid_Portal_Data {};

class SubwayStation;
*/

class SubwayStation;

class SubwayPortal //: public _SubwayPortal
{
public:
    SubwayPortal();
    SubwayPortal( string data_row );

    //~SubwayPortal();


    /** returns the distance between station and a gps location  */
    double distance_from( double latitude, double longitude);

    /** returns the distance between the two portals  */
    friend double distance_between( SubwayPortal portal1,
                                    SubwayPortal portal2);



    /** returns true if the two portals have the exact same set of routes  */
    friend bool same_routes( SubwayPortal portal1,
                             SubwayPortal portal2);

    /** returns true if the two portals belong to the same station */
    friend bool same_station( SubwayPortal portal1,
                              SubwayPortal portal2);

    friend ostream & operator<< ( ostream & out, SubwayPortal e);

    //This means SubwayStation can access the private mem vars of subway portal
    friend class SubwayStation;

    /*  Accessor  Functions */
    /**  name() returns name of portal as a unique string
     */
    string name()  const;

    /** can_access() returns true if given route is accessible
     *  @param route_set [in]  a bitstring with a 1 bit for route
     *  @return bool  true iff route is accessible from this portal
     */
    bool   can_access( route_set route ) const;

    /**  p_location() returns GPS location of portal  */
    GPS    p_location() const;

    /**  s_location() returns GPS location of portal's station */
    GPS    s_location() const;

    /**  routes() returns route set of portal */
    route_set routes() const;

	string remove_extra_spaces(string input);

	//void set_entrance_location(double longitude, double latitude);

private:

//	string remove_extra_spaces(string input);

	string portal_name;

	//data set

	string division;
	string line;

	string station_name;
	double station_latitude;
	double station_longitude;
	
	//Route1,Route2,Route3,Route4,Route5,Route6,Route7,Route8,Route9,Route10,Route11,
	string route1;
	string route2;
	string route3;
	string route4;
	string route5;
	string route6;
	string route7;
	string route8;
	string route9;
	string route10;
	string route11;

	string entrance_type;
	string entry;
	string exit_only;
	string vending;
	string staffing;
	string staff_hours;
	string ada;
	string ada_notes;
	string free_crossover;

	string north_south_street;
	string east_west_street;
	string corner;
	int id;

	double entrance_latitude;
	double entrance_longitude;
	
	GPS station_location;
	GPS entrance_location; 

	route_set portal_routes; 


};



#endif /* _SUBWAY_PORTAL_H_ */
