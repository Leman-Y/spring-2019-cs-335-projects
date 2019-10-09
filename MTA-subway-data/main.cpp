/*******************************************************************************
  Title          : main.cpp
  Author         : Stewart Weiss
  Created on     : April 12, 2018
  Description    : The main program for Project3, processing MTA Subway Entrance
                   data.
  Purpose        : reads the data file and a command file, applying
                   commands to the subway entrance data.
  Usage          : project3  datafile  commandfile
  Build with     : g++ -o project3 main.cpp
  Modifications  :

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <locale>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <errno.h>
#include <limits.h>

//#include "_subway_portal.h"
//#include "_subway_system.h"

#include "subway_portal.h"
#include "subway_system.h"

// g++ -o project -std=c++11 main.cpp subway_portal.cpp subway_station.cpp subway_system.cpp subway_route.o command.cpp gps.cpp _hash_item.cpp hash_table.cpp
//I think he changed Portal to portal when he accidentally changed it at office hours.
//g++ -o project -std=c++11 main.cpp subway_portal.cpp subway_station.cpp subway_system.cpp subway_route.o  gps.cpp _hash_item.cpp hash_table.cpp
//^ dont include command.cpp


//struct Invalid_portal_Data{};


#include "command.cpp"


using namespace std;

/******************************************************************************
Data Dictionary for Input File:
 Position   Type   Name        Description
 1          uint   ObjectID    Unique identifier for subway entrance
 3          string Name        Name of this station (actually its address)
 4          string The_Geom    GPS coordinates of the form POINT(decimal decimal)
                               where first is longitude and second, latitude
 5          string Line        Representation of lines accessed at this entrance
                               See the assignment spec for details.

 ******************************************************************************/

/******************************************************************************
Commands:

list_route_stations route_identifier
    Lists the station_names of all subway stations that service the given route.

list_all_stations
    Lists the station_names of all subway stations in the subway system.

list_routes portal_name
    Lists the routes that can be accessed at this portal. Routes should be
    printed in the form "route,route,..., route" where route is a route id
    like A, B, 7, FS. portal_name is the unique string for the portal.

list_station_portals station_name
    Lists the names of all subway portals for the given station.

nearest_routes latitude longitude
    Lists the route_ids of all subway routes that are closest to the
    point (latitude, longitude). There may be more than one because two or
    more lines might be at a station that is nearest to the point, or
    because two stations might be at the same distance from the point.

nearest_portal latitude longitude
    Lists the name of the subway portal that is closest to the
    point (latitude, longitude).  The two numbers are checked for validity -
    no absolute value greater than 180 degrees is allowed. In the very unlikely
    event that two portals are exactly the same distance from the point, the
    first found is chosen.

******************************************************************************/



int main( int argc, char* argv[])
{

    ifstream        inputfile;
    ifstream        commandfile;
    string          portal_row;
    Command         command;
    string          station_name;
    string          routestr;
    bool            result;
    string          prev;
    SubwayPortal    temp_portal;
    SubwaySystem    MTA_subways;


    if ( argc < 3 ) {
        cerr << "\n Usage: " << argv[0] << " input_file  command_file" << endl;
        exit(1);
    }

    inputfile.open(argv[1]);
    if ( inputfile.fail() ) {
        cerr << "Could not open file " << argv[1] << " for reading" << endl;
        exit(1);
    }

    commandfile.open(argv[2]);
    if ( commandfile.fail() ) {
        cerr << "Could not open file " << argv[2] << " for reading" << endl;
        exit(1);
    }


    int num_portals = 0;
    SubwayPortal prev_portal;
    while( getline(inputfile, portal_row) ) {
        try {
           // cout << portal_row << endl;
            temp_portal = SubwayPortal(portal_row);
            MTA_subways.add_portal(temp_portal);
        }
        catch ( Invalid_Portal_Data d)
        {
            cerr << "bad data on line " << num_portals << endl;
        }
        num_portals++;
    }

    int number_of_stations = MTA_subways.form_stations();

    inputfile.close();


    while ( ! commandfile.eof() ) {
        if ( ! command.get_next(commandfile) ) {
            if ( ! commandfile.eof() ) {
                cerr << "Error getting command.\n";
                continue;
            }
            else
                return 1;
        }

        string        id;
        string        station_name;
        string        portal_name;
        double        longitude;
        double        latitude;

        command.get_args( id, station_name, portal_name, longitude, latitude, result);
        // cout << id << " " << station_name << " " << longitude << " " <<  latitude << "\n";

        switch ( command.type_of() )
        {
            case  list_route_stations_cmmd:
                cout << "\nStations of the " << id << " line:\n";
                MTA_subways.list_stations_of_route( cout, id);
                break;

            case  list_all_stations_cmmd:
                cout << "\nAll " << number_of_stations << " stations:" << endl;
                MTA_subways.list_all_stations(cout);
                break;

            case  list_station_portals_cmmd:
                cout << "\nEntrances at station " << "\"" << station_name << "\":\n\n";
                MTA_subways.list_all_portals(cout, station_name);
                cout << endl;
                break;

            case  list_routes_cmmd:
                MTA_subways.get_portal(portal_name, temp_portal);
                cout << "\nThe routes that can be accessed from this "
                     << "entrance are "
                     << str_from_routeset(temp_portal.routes())
                     << endl;
                break;
            case  nearest_routes_cmmd:
                routestr = MTA_subways.nearest_routes(latitude, longitude);
                if ( routestr.length() == 1 )
                    cout << "\nThe closest subway line to point ("
                     << latitude << "," << longitude << ") is the "
                     << routestr
                     << endl;
                else
                    cout << "\nThe closest subway lines to point ("
                     << latitude << "," << longitude << ") are "
                     << routestr
                     << endl;
                break;
            case  nearest_portal_cmmd:
                cout << "\nThe closest entrance to point ("
                     << latitude << "," << longitude << ") is "
                     << MTA_subways.nearest_portal(latitude, longitude)
                     << endl;
                break;
            case  bad_cmmd:
                break;
            case  null_cmmd:
            default:
                    break;
        }
    }
    commandfile.close();
    return 0;
}





