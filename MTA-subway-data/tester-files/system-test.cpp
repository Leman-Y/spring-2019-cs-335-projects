
#include <iostream>
#include <array>
#include <vector>

#include "subway_system.h"

using namespace std;



#define num 50

//const int MAX_STATIONS = 2048;

/*
g++ -std=c++11 system-test.cpp subway_station.cpp subway_portal.cpp gps.cpp subway_route.o hash_table.cpp _hash_item.cpp subway_system.cpp


*/

class A
{
public:
	
	int app()
	{
		return 99;
	}

};

class B
{
	int bop()
	{
		return yer.app();
	}
private:
	A yer;

};

int main()
{
	SubwaySystem matrix;

	SubwayPortal one("BMT,4 Avenue,4 Avenue-25th St,40.660397,-73.998091,R,,,,,,,,,,,Stair,YES,,YES,FULL,,FALSE,,FALSE,4th Ave,25th St,SE,2,40.660323,-73.997952,\"(40.660397, -73.998091)\",\"(40.660323, -73.997952)");
	SubwayPortal two("BMT,4 Avenue,4 Avenue-25th St,40.660397,-73.998091,R,,,,,,,,,,,Stair,YES,,YES,FULL,,FALSE,,FALSE,4th Ave,25th St,SE,2,40.660323,-73.997952,\"(40.660397, -73.998091)\",\"(40.660323, -73.997952)");


	matrix.add_portal(one);

	matrix.form_stations();

	matrix.list_all_stations(cout);

	matrix.list_all_portals(cout, "4 Avenue");


	cout<<"compiles"<<endl;

	return 0;
}
