
#include <iostream>
#include <string>

#include "gps.h"

//#include "_subway_portal.h"
#include "subway_portal.h"


using namespace std;
/*
string remove_extra_spaces(string input)
{
	string ans;
	string word;

	for(int i=0; i<input.length(); i++)
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
*/
int main()
{

/*
string sen="sentence   big  boom";

double an = stod("9");
cout<<an<<endl;
*/

SubwayPortal sub ("BMT,4 Avenue,25th St,40.660397,-73.998091,R,1,F,A,B,J,5,,,,D,Stair,YES,,YES,FULL,,FALSE,,FALSE,4th Ave,25th St,SE,2,40.660323,-73.997952,\"(40.660397, -73.998091)\",\"(40.660323, -73.997952)\"");


SubwayPortal bop("IND,63rd Street,21st St,0,0,F,,,,,,,,,,,Escalator,YES,,YES,FULL,,TRUE,,TRUE,21st St,41st Ave,NW,1,40.754131,-73.942491,\"(40.754203, -73.942836)\",\"(40.754131, -73.942491)\"");

SubwayPortal empty;

	cout<<sub.distance_from(40,73)<<endl;

	cout<<empty.distance_from(40,73)<<endl;

	cout<<bop.distance_from(40,73)<<endl;

	cout<<distance_between(sub,bop)<<endl;

	cout<<same_routes(sub,bop)<<endl;

	cout<<sub<<endl;

	cout<<sub.name()<<endl;
	cout<<bop.name()<<endl;
	cout<<empty.name()<<endl;

	cout<<sub.can_access(4)<<endl;

	cout<<routestring2int("F")<<endl;
	cout<<int2route_id(15)<<endl;
	cout<<sub.can_access(15)<<endl;

	cout<<sub.routes()<<endl;
	cout<<bop.routes()<<endl;

	cout<<(32768&32768)<<endl;

	cout<<sub.can_access(32768)<<endl;
	cout<<(32768&134786082)<<endl;
	cout<<bop.can_access(32768)<<endl;
	cout<<empty.can_access(32768)<<endl;

	cout<<sub.p_location()<<endl;
	cout<<sub.s_location()<<endl;

}