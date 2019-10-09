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


SubwaySystem::SubwaySystem()
{
	cout<<"SubwaySystem constructor"<<endl;
}

SubwaySystem::~SubwaySystem()
{

}


/** add_portal()  adds the given portal to the array of portals
 *  It also creates a hash table entry for this portal that points to
 *  its location in the array.
 *  @param  SubwayPortal [in] portal: an initialized portal
 *  @return int  1 if successful, 0 if portal is not added.
 */
int SubwaySystem::add_portal(SubwayPortal portal)
{
	cout<<"add_portal called"<<endl;

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

	/*
	//Subway station with portal has been added to the array
	if(subway_array.size() > initial_size)
	{

		return 1;
	}	
	else
	{
		return 0;

	}
	*/
	
}

/** list_all_stations() lists all subway station names on the given stream
 *  @param [inout] ostream out is an open output stream
 */
void SubwaySystem::list_all_stations(ostream & out)
{
	cout<<"list_all_stations called"<<endl;
	out<<stations.listall(out);
}

/** list_all_portals() lists all portals to a given station on given stream
 *  @param [inout] ostream is an open output stream
 *  @param [in]  string station_name is the exact name of a station,
 *          which must be the name of the set of portal names. These can
 *          be obtained from the output of list_all_stations().
 * Should also remove extra white spaces since string is passed
 * Nassau St & Frankfort St at SE corner
 * Nassau St   &   Frankfort   St  at  SE  corner
 */
void SubwaySystem::list_all_portals(ostream & out, string station_name)
{
	cout<<"list_all_portals called"<<endl;

	out<<portals.listall(out);

}

/** list_stations_of_route() lists all station names on the given route on
 *          the given output stream
 *  @param [inout] ostream is an open output stream
 *  @param [in]  route_id route is the name of the subway route whose
 *          stations are to be printed onto the stream
 */
void SubwaySystem::list_stations_of_route( ostream & out, route_id route)
{
	cout<<"list_stations_of_route called"<<endl;


}


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
int  SubwaySystem::form_stations()
{
	cout<<"form_stations called"<<endl;

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

/** get_portal() searches for a portal whose name equals name_to_find
 *  @param string [in]  name_to_find is the portal name to look up
 *  @param SubwayPortal & [out] is filled with the data from the Portal
 *         if it is found, or is an empty Portal whose name is ""
 *  @return bool true if anf only if the portal is found
 */
bool SubwaySystem::get_portal(string name_to_find, SubwayPortal & portal) 
{
	cout<<"get_portal called"<<endl;

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


/** nearest_portal() returns a string representation of the portal that
 *  is nearest to the given point
 *  @param  double [in]  latitude of point
 *  @param  double [in]  longitude of point
 *  @return string       portal's name (as defined in subway_portal.h)
 */
string SubwaySystem::nearest_portal( double latitude, double  longitude) 
{
	cout<<"nearest_portal called"<<endl;

	string empty="";
	/*
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
		if(distance_between(array_of_subway_portals[i],other_portal)<minimum_distance)
		{
			minimum_distance=other_portal.distance_between(array_of_subway_portals[i],other_portal);
			index_of_nearest_portal=i;
		}
	}
	return array_of_subway_portals[index_of_nearest_portal];
	*/
	return empty;
}

/** nearest_routes() returns a string representation of the routes that
 *  are nearest to the given point
 *  @param  double [in]  latitude of point
 *  @param  double [in]  longitude of point
 *  @return string       representation of set of routes
 */
string SubwaySystem::nearest_routes( double latitude, double  longitude)
{

	cout<<"nearest_routes called"<<endl;
	
	string empty="";

	return empty;
}

/* * Union two disjoint sets .
* Assume root1 and root2 are distinct and represent set names .
* @param root1 is the root of set 1.
* @param root2 is the root of set 2.
*/
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
/* *
* Perform a recursive find with path compression .
* Error checks omitted again for simplicity .
* @param x is the element to be found
* @return the set containing x .
*/
int SubwaySystem::find( int x )
{
    if ( subway_array[ x ].parent_id() < 0 )
        return x ;
    else
    	subway_array [ x ].set_parent( find ( subway_array [ x ].parent_id() )  );
    	return  find ( subway_array [ x ].parent_id() );
}