/******************************************************************************
  Title          : subway_station.h
  Author         : Leman Yan
  Created on     : May 6, 2019
  Description    : Interface file for the SubwayStation object
  Purpose        : Encapsulates data and methods of a subway station
  Usage          :
  Build with     :
  Modifications  :

******************************************************************************/

#ifndef __SUBWAY_STATION_H__
#define __SUBWAY_STATION_H__

#include "subway_portal.h"

#include <set>
#include <list> 
#include <iterator> 

class SubwayStation
{
public:
	/** SubwayStation() is a default constructor
	* It should initialize any private members with suiatbel default values.
	*/
	SubwayStation();

	/** This is a constructor that creates a SubwayStation object from a portal
	* It makes the portal the embedded portal.
	*/
	SubwayStation(SubwayPortal portal );

	/** set_parent() sets the parent id of the station
	* @param int [in] the id of the parent
	*/
	void set_parent(int newparent);

	/** add_child() adds a new child to the station's list of children
	* @param int [in] the index of the child to add
	*/
	void add_child(int child);

	/** A friend function that determines when two stations are connected
	* @param SubwayStation [in] s1
	* @param SubwayStation [in] s2
	* @return bool true iff s1 and s2 are connected according to rules defined
	* in the assignment specification
	*/
	bool connected(SubwayStation s1, SubwayStation s2);

	/** add_station_name() adds a new name to station
	* @Note: It does not add a name if it is already in the set of names for
	* the station.
	* @param string [in] newname is name to be added
	* @return 1 if name is added and 0 if not
	*/
	int add_station_name(string newname);
	
	/** names() returns a list of the names of the station as a list of strings
	*/
	list<string> names() const;

	// primary_name() is the first station name in its set of names
	string primary_name() const;

	// parent_id() is the index in the array of the parent of the station
	int parent_id() const;

	/** portal_list() returns a list of the ids in the list of the portals in
	* this station set
	*/
	list<int> portal_list() const;

	// returns the name of the embedded portal
	string portal_name() const;

	// returns the portal that is embedded in this station object
	void get_portal(SubwayPortal &p ) const;

private:
	int m_parent_id;

	set<string> m_station_names;
	list<int> children;
	string portal_unique_name;
	SubwayPortal portal;
};

#endif /* __SUBWAY_STATION_H__ */
