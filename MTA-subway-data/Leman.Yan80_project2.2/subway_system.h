/******************************************************************************
  Title          : subway_system.h
  Author         : Leman Yan
  Created on     : May 7, 2019
  Description    : Interface file for the SubwaySystem object
  Purpose        : Encapsulates data and methods of a subway system
  Usage          :
  Build with     : no build
  Modifications  :

******************************************************************************/


#ifndef __SUBWAY_SYSTEM_H__
#define __SUBWAY_SYSTEM_H__

#include <string>
#include <vector>
#include <iostream>

#include "hash_table.h"
#include "subway_station.h"


#define MAX_STATIONS  2048

//const int MAX_STATIONS = 2048;

using namespace std;


class SubwaySystem
{
public:
    
    SubwaySystem();

    ~SubwaySystem();
    

    /** add_portal()  adds the given portal to the array of portals
     *  It also creates a hash table entry for this portal that points to
     *  its location in the array.
     *  @param  SubwayPortal [in] portal: an initialized portal
     *  @return int  1 if successful, 0 if portal is not added.
     */
    int add_portal(SubwayPortal portal);

    /** list_all_stations() lists all subway station names on the given stream
     *  @param [inout] ostream out is an open output stream
     */
    void list_all_stations(ostream & out) ;

    /** list_all_portals() lists all portals to a given station on given stream
     *  @param [inout] ostream is an open output stream
     *  @param [in]  string station_name is the exact name of a station,
     *          which must be the name of the set of portal names. These can
     *          be obtained from the output of list_all_stations().
     * Should also remove extra white spaces since string is passed
	 * Nassau St & Frankfort St at SE corner
	 * Nassau St   &   Frankfort   St  at  SE  corner
     */
    void list_all_portals(ostream & out, string station_name) ;

    /** list_stations_of_route() lists all station names on the given route on
     *          the given output stream
     *  @param [inout] ostream is an open output stream
     *  @param [in]  route_id route is the name of the subway route whose
     *          stations are to be printed onto the stream
     */
    void list_stations_of_route( ostream & out, route_id route);


    /** form_stations()
     *  Note: form_stations should be called once after the array of portals
     *  has been created. It determines which portals are connected to each
     *  other and forms disjoint sets of connected stations and portals.
     *  After all sets are formed, it stores the names of the stations that
     *  name these sets (e.g., if parent trees, the ones at the root)
     *  in a hash table for station names for fast access.
     *  Finally, it sets an internal flag to indicate that the sets have been
     *  computed.
     *  @return int : number of sets created
     */
    int  form_stations();

    /** get_portal() searches for a portal whose name equals name_to_find
     *  @param string [in]  name_to_find is the portal name to look up
     *  @param SubwayPortal & [out] is filled with the data from the Portal
     *         if it is found, or is an empty Portal whose name is ""
     *  @return bool true if anf only if the portal is found
     */
    bool get_portal(string name_to_find, SubwayPortal & portal) ;


    /** nearest_portal() returns a string representation of the portal that
     *  is nearest to the given point
     *  @param  double [in]  latitude of point
     *  @param  double [in]  longitude of point
     *  @return string       portal's name (as defined in subway_portal.h)
     */
    string nearest_portal( double latitude, double  longitude) ;

    /** nearest_routes() returns a string representation of the routes that
     *  are nearest to the given point
     *  @param  double [in]  latitude of point
     *  @param  double [in]  longitude of point
     *  @return string       representation of set of routes
     */
    string nearest_routes( double latitude, double  longitude) ;

private:

    /* * Union two disjoint sets .
    * Assume root1 and root2 are distinct and represent set names .
    * @param root1 is the root of set 1.
    * @param root2 is the root of set 2.
    */
    void union_sets(int root1, int root2);

    /* *
    * Perform a recursive find with path compression .
    * Error checks omitted again for simplicity .
    * @param x is the element to be found
    * @return the set containing x .
    */
    int find( int x );

	//set<SubwayStation> subway_stations;

	//SubwayStation subway_station_array[MAX_STATIONS];

    vector<SubwayPortal> array_of_subway_portals;

	vector<SubwayStation> subway_array;

	HashTable stations;

	HashTable portals;

	vector<SubwayRoute> subway_routes;

};

#endif /* __SUBWAY_SYSTEM_H__ */

