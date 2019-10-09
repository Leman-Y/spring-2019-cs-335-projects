/******************************************************************************
  Title          : subway_system.cpp
  Author         : Leman Yan
  Created on     : May 7, 2019
  Description    : Implementation file for the SubwaySystem object
  Purpose        : Encapsulates data and methods of a subway system
  Usage          :
  Build with     : no build
  Modifications  : Union and Find function was taken from Stewart Weiss

******************************************************************************/

#include "subway_system.h"
#include "gps.h"


SubwaySystem::SubwaySystem()
{
}

SubwaySystem::~SubwaySystem()
{

}



int SubwaySystem::add_portal(SubwayPortal portal)
{
	//cout<<"add_portal called"<<endl;

	SubwayStation station_object(portal);

	int initial_size=subway_array.size();

	//Might need to check if we have past our limit

	//Portal doesn't have a valid name
	if(portal.name() == "")
	{
		return 0;
	}

	//No duplicate in the hash table
	__ItemType portal_item(portal.name(),subway_array.size()); 
	if(1 == portals.insert(portal_item) )
	{
		//
		subway_array.push_back(station_object);
		array_of_subway_portals.push_back(portal);
	}
	else
	{
		return 0;
	}

}


void SubwaySystem::list_all_stations(ostream & out)
{
	//cout<<"list_all_stations called"<<endl;
	out<<stations.listall(out);
}

void SubwaySystem::list_all_portals(ostream & out, string station_name)
{
	//cout<<"list_all_portals called"<<endl;

	out<<portals.listall(out);

}


void SubwaySystem::list_stations_of_route( ostream & out, route_id route)
{
	//cout<<"list_stations_of_route called"<<endl;


}


int  SubwaySystem::form_stations()
{

	//No data to form anything
	if(0==subway_array.size())
	{
		return 0;
	}

	//No need to check last element in the array
	for(int i=0; i< (subway_array.size()-1); i++)
	{
		for(int j=i+1; j<subway_array.size(); j++)
		{
			if(1 == subway_array[0].connected(subway_array[i],subway_array[j]) )
			{
				//Find the roots and union the two sets
				int first=find(i);
				int second=find(j);
				union_sets(first,second);
			}
		}
	}

	/* After we union and form all the sets. We need to update each station's private variables
	* 	set<string> m_station_names;
	*	list<int> children;
	*
	*/
	/*
		I think I might have gotten this wrong. Even though find find's the parent id. It doesnt give me the 
		index of the parent, because it will be a negative number in the end. 
	*/
	for(int index=0; index<subway_array.size(); index++)
	{
		//If your own parent id is < 0. Then add your own station to the list
		//subway_array[index].add_station_name(subway_array[index])

		//Get the parent id aka find the index of this station's parent. 
		//Then add this station to the parent
		int parent_id = find(index);
		subway_array[parent_id].add_station_name(subway_array[index].primary_name());
		if(parent_id < -1 ) // <-1 to make sure you are not your own child
		{
			subway_array[parent_id].add_child(index);	
		}
		
	}

	//Now all the station names and children have been added. Hash the roots to the hash table.
	for(int index=0; index<subway_array.size(); index++)
	{
		if(subway_array[index].parent_id()<0)
		{
			//I might need to declare an itemtype then insert it
			__ItemType station(subway_array[index].primary_name(), index);
			//Insert into hash table
			stations.insert(station);
		}
	}



	return 0;
}

bool SubwaySystem::get_portal(string name_to_find, SubwayPortal & portal) 
{
	//cout<<"get_portal called"<<endl;

	SubwayPortal empty_portal;

	//Find the portal with the unique name. Return the pos of the portal index in the array
	__ItemType portal_item(name_to_find,-1);
	if(1 == portals.find(portal_item) )
	{
		//portal_item's position has been manipulated by find. So get the pos
		int portal_index=portal_item.get_pos();
		portal=array_of_subway_portals[portal_index];
		return 1;
	}
	portal=empty_portal;
	return 0;
}

string SubwaySystem::nearest_portal( double latitude, double  longitude) 
{
	//cout<<"nearest_portal called"<<endl;

	string empty="";
	
	//No portals so return empty string
	if(array_of_subway_portals.size()==0)
	{
		return empty;
	}
	GPS other_portal(longitude, latitude);
	int minimum_distance=distance_between(array_of_subway_portals[0].p_location(),other_portal);
	int index_of_nearest_portal=0;
	for(int i=0; i<array_of_subway_portals.size(); i++)
	{
		if(distance_between(array_of_subway_portals[i].p_location(),other_portal)<minimum_distance)
		{
			minimum_distance=distance_between(array_of_subway_portals[i].p_location(),other_portal);
			index_of_nearest_portal=i;
		}
	}
	
	return array_of_subway_portals[index_of_nearest_portal].name();
}

string SubwaySystem::nearest_routes( double latitude, double  longitude)
{	
	string empty="";

	return empty;
}

void SubwaySystem::union_sets(int root1, int root2)
{
    if ( root1 != root2 ) {
        if ( subway_array [ root2 ].parent_id() < subway_array [ root1 ].parent_id() ) {
            // root2 is deeper
            subway_array [ root2 ].set_parent(subway_array [ root2 ].parent_id() + subway_array [ root1 ].parent_id() );
            subway_array [ root1 ].set_parent(root2);
        } else {
            // root1 is deeper
            subway_array [ root1 ].set_parent(subway_array [ root1 ].parent_id() + subway_array [ root2 ].parent_id() );
            subway_array [ root2 ].set_parent( root1 );
        }
    }
}

int SubwaySystem::find( int x )
{
    if ( subway_array[ x ].parent_id() < 0 )
        return x ;
    else
    	subway_array [ x ].set_parent( find ( subway_array [ x ].parent_id() )  );
    	return  find ( subway_array [ x ].parent_id() );
}