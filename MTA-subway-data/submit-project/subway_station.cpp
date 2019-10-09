/******************************************************************************
  Title          : subway_station.cpp
  Author         : Leman Yan
  Created on     : May 6, 2019
  Description    : Implementation file for the SubwayStation object
  Purpose        : Encapsulates data and methods of a subway station
  Usage          :
  Build with     :
  Modifications  :

******************************************************************************/


#include "subway_station.h"


/** SubwayStation() is a default constructor
* It should initialize any private members with suiatbel default values.
*/
SubwayStation::SubwayStation(): m_parent_id(-1), portal_unique_name("")
{
	cout<<"SubwayStation default constructor"<<endl;
}


/** This is a constructor that creates a SubwayStation object from a portal
* It makes the portal the embedded portal.
*/
SubwayStation::SubwayStation(SubwayPortal portal )
{
	cout<<"SubwayStation parameter constructor"<<endl;


	this->portal=portal;
	portal_unique_name=portal.name();
	m_parent_id=-1;
	m_station_names.insert(portal.station_name);
}

/** set_parent() sets the parent id of the station
* @param int [in] the id of the parent
*/
void SubwayStation::set_parent(int newparent)
{
	cout<<"set_parent called"<<endl;

	m_parent_id=newparent;

}

/** add_child() adds a new child to the station's list of children
* @param int [in] the index of the child to add
*/
void SubwayStation::add_child(int child)
{
	cout<<"add_child called"<<endl;

	children.push_back(child);
}

/** A friend function that determines when two stations are connected
* @param SubwayStation [in] s1
* @param SubwayStation [in] s2
* @return bool true iff s1 and s2 are connected according to rules defined
* in the assignment specification
*/
bool SubwayStation::connected(SubwayStation s1, SubwayStation s2)
{
	cout<<"connected"<<endl;

	return same_station(s1.portal, s2.portal);
}

/** add_station_name() adds a new name to station
* @Note: It does not add a name if it is already in the set of names for
* the station.
* @param string [in] newname is name to be added
* @return 1 if name is added and 0 if not
*/
int SubwayStation::add_station_name(string newname)
{
	cout<<"add_station_name called"<<endl;

	//Inserted
	//pair<iterator,bool> insert ( const value_type& x );
	//One way to check success of a insert is to compare size() before and after.
	if(m_station_names.insert(newname).second == 1)
	{
		return 1;
	}

	//Not inserted
	return 0;
}

/** names() returns a list of the names of the station as a list of strings
*/
list<string> SubwayStation::names() const
{
	cout<<"names called"<<endl;
    
	list<string> names_of_station;

    set <string> :: iterator itr; 

    for (itr = m_station_names.begin(); itr != m_station_names.end(); ++itr) 
    { 
        names_of_station.push_back(*itr); 
    } 

	return names_of_station;
}

// primary_name() is the first station name in its set of names
string SubwayStation::primary_name() const
{
	cout<<"primary_name called"<<endl;
	if(0 != m_station_names.size())
	{
		return *(m_station_names.begin());
	}
	return 0;
}

// parent_id() is the index in the array of the parent of the station
int SubwayStation::parent_id() const
{
	cout<<"parent_id called"<<endl;

	return m_parent_id;
}

/** portal_list() returns a list of the ids in the list of the portals in
* this station set
*/
list<int> SubwayStation::portal_list() const
{
	cout<<"portal_list called"<<endl;

	return children;
}

// returns the name of the embedded portal
string SubwayStation::portal_name() const
{
	cout<<"portal_name called"<<endl;

	return portal_unique_name;
}

// returns the portal that is embedded in this station object
void SubwayStation::get_portal(SubwayPortal &p ) const
{
	p=portal;

}