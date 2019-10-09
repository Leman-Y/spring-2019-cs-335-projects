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



SubwayStation::SubwayStation(): m_parent_id(-1), portal_unique_name("")
{
	//cout<<"SubwayStation default constructor"<<endl;
}



SubwayStation::SubwayStation(SubwayPortal portal )
{
	//cout<<"SubwayStation parameter constructor"<<endl;


	this->portal=portal;
	portal_unique_name=portal.name();
	m_parent_id=-1;
	m_station_names.insert(portal.station_name);
}


void SubwayStation::set_parent(int newparent)
{
	//cout<<"set_parent called"<<endl;

	m_parent_id=newparent;

}


void SubwayStation::add_child(int child)
{
	//cout<<"add_child called"<<endl;

	children.push_back(child);
}


bool SubwayStation::connected(SubwayStation s1, SubwayStation s2)
{
	//cout<<"connected"<<endl;

	return same_station(s1.portal, s2.portal);
}


int SubwayStation::add_station_name(string newname)
{
	//cout<<"add_station_name called"<<endl;

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


list<string> SubwayStation::names() const
{
	//cout<<"names called"<<endl;
    
	list<string> names_of_station;

    set <string> :: iterator itr; 

    for (itr = m_station_names.begin(); itr != m_station_names.end(); ++itr) 
    { 
        names_of_station.push_back(*itr); 
    } 

	return names_of_station;
}

string SubwayStation::primary_name() const
{
	//cout<<"primary_name called"<<endl;
	if(0 != m_station_names.size())
	{
		return *(m_station_names.begin());
	}
	return 0;
}

int SubwayStation::parent_id() const
{
	//cout<<"parent_id called"<<endl;

	return m_parent_id;
}

list<int> SubwayStation::portal_list() const
{
	//cout<<"portal_list called"<<endl;

	return children;
}

string SubwayStation::portal_name() const
{
	//cout<<"portal_name called"<<endl;

	return portal_unique_name;
}

void SubwayStation::get_portal(SubwayPortal &p ) const
{
	p=portal;

}