/******************************************************************************
  Title          : subway_portal.cpp
  Author         : Leman Yan
  Created on     : May 4, 2019
  Description    : Interface file for the SubwayPortal object
  Purpose        : Encapsulates data and methods of a subway portal
  Usage          :
  Build with     :
  Modifications  :

******************************************************************************/

//#include <iostream>

#include "subway_portal.h"

string SubwayPortal::remove_extra_spaces(string input)
{
	string ans;
	string word;

	for(unsigned int i=0; i<input.length(); i++)
	{
		if(input[i]==' ')
		{
			ans+=input[i];
			while(input[i+1]==' ')
			{
				i++;
			}
		}
		else
		{
			ans+=input[i];
		}
	}

	return ans;
}


SubwayPortal::SubwayPortal()
{
	//cout<<"subwayportal default constructor called"<<endl;

	portal_name="";
	line="";
	station_name="";

	station_latitude=0;
	station_longitude=0;

	north_south_street="";
	east_west_street="";
	corner="";
	id=0;

	entrance_latitude=0;
	entrance_longitude=0;

	portal_routes=0;
}

/*
SubwayPortal::~SubwayPortal()
{}
*/

SubwayPortal::SubwayPortal( string data_row )
{
	//cout<<"SubwayPortal constructor(string data_row)"<<endl;

	vector<string> data;
	string column;
	int count=0;
	for(int i=0; i<data_row.length(); i++)
	{
		/*
		if(data_row[i]=='"') Only affects last two columns 
		{
			i++; //Just skip the quote
		}
		*/
		if(data_row[i]==',')
		{
			data.push_back(column);
			column="";	
			count++;
		}
		else
		{
			column+=data_row[i];
		}
	}
	

	//If data.size()<30 you are accessing out of bounds 

	if(data.size()>30)
	{
		//string portal=data[25]+','+data[26]+','+data[27]+','+data[28];
		//portal+=(data[28]);
		portal_name=remove_extra_spaces(data[25]+','+data[26]+','+data[27]+','+data[28]); 
		
		//cout<<portal_name<<endl;

		division=data[0];
		line = data[1];

		station_name = data[2];
		station_latitude = stod(data[3]);
		station_longitude = stod(data[4]);

		entrance_type = data[16];
		entry = data[17];
		exit_only = data[18];
		vending = data[19];	
		staffing = data[20];
		staff_hours = data[21];
		ada = data[22];
		ada_notes = data[23];
		free_crossover = data[24];

		north_south_street = data[25];
		east_west_street = data[26];
		corner = data[27];
		id = stod(data[28]); 

		entrance_latitude = stod(data[29]);
		entrance_longitude = stod(data[30]);

		station_location = GPS(station_longitude, station_latitude);
		entrance_location = GPS(entrance_longitude, entrance_latitude);

		portal_routes=0;	//Define it or else you will get extremely random numbers if you dont

		//Do the routes
		for(int index=5; index<16; index++)
		{	
			if(1 == is_route_id(data[index]) )
			{
				//portal_routes+=routestring2int(data[index]); Wrong 
				long number=(1L << routestring2int(data[index]));
				portal_routes = portal_routes | number; 
			}
			
		}
	}

}

double SubwayPortal::distance_from( double latitude, double longitude)
{
	//cout<<"calling distance_from "<<latitude<<" "<<longitude<<endl;

	return  distance_between( station_location, GPS(latitude,longitude));
}

double distance_between( SubwayPortal portal1,
                                SubwayPortal portal2)
{

	return distance_between(portal1.entrance_location,portal2.entrance_location);
}



bool same_routes( SubwayPortal portal1,
                         SubwayPortal portal2)
{

	if(portal1.portal_routes == portal2.portal_routes)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//Not the right implementation. Connected relation
//Should use this function in subway station
bool same_station( SubwayPortal portal1,
                          SubwayPortal portal2)
{
	//Should I include portal1.station_name == portal2.station_name???
	if( (portal1.station_name == portal2.station_name) ||
		(	same_routes(portal1,portal2) && distance_between(portal1.station_location,portal2.station_location) <= 0.32 )  )
	{
		return 1;
	}
	return 0;
}

ostream & operator<< ( ostream & out, SubwayPortal e)
{
	out<<"entrance_location:"<<e.entrance_location;
	return out; 
}


string SubwayPortal::name()  const
{
	//cout<<"calling name()"<<endl;

	return portal_name;
}

bool   SubwayPortal::can_access( route_set route ) const
{
	//cout<<"calling can_access"<<endl;
	if( (portal_routes & route) >= 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	 
}

GPS    SubwayPortal::p_location() const
{
	return entrance_location;
}

GPS    SubwayPortal::s_location() const
{
	return station_location;
}


route_set SubwayPortal::routes() const
{
	return portal_routes;
}
