

#include <iostream>
#include <set> 
#include <iterator> 

#include "subway_station.h"

#include <fstream>
using namespace std;


void showlist(list <string> g) 
{ 
    list <string> :: iterator it; 
    for(it = g.begin(); it != g.end(); ++it) 
        cout <<  *it <<endl;
} 

void showset(set<string> a)
{
    set <string > :: iterator itr; 
    for (itr = a.begin(); itr != a.end(); ++itr) 
    { 
        cout << *itr <<endl;
    } 
}

int main()
{
    SubwayPortal bmt("BMT,4 Avenue,4 Avenue-25th St,40.660397,-73.998091,R,,,,,,,,,,,Stair,YES,,YES,FULL,,FALSE,,FALSE,4th Ave,25th St,SE,2,40.660323,-73.997952,\"(40.660397, -73.998091)\",\"(40.660323, -73.997952)\"");

    ifstream inFile;
    inFile.open("subwaydata_newstationnames.csv");
    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    string str;
    getline(inFile,str);

    inFile.close();

    //If I put the string into subway portal it segfaults me
    SubwayPortal first(str);

    SubwayPortal second(str);

    cout<<first<<endl;

    SubwayStation times;

    SubwayStation grand(first);

    SubwayStation central(second);

    cout<<grand.connected(grand,central)<<endl;
    cout<<grand.connected(grand,times)<<endl;

    grand.add_station_name("14th St");

    list<string> feedback;
    feedback=grand.names();

    showlist(feedback);

    cout<<grand.primary_name()<<endl;

    set<string> strings;

    strings.insert("11th st");
    strings.insert("yogabba ave");
    strings.insert("99th st");
    strings.insert("zergth st");


    cout<<"-------------------"<<endl;

    showset(strings);

    grand.set_parent(23);

    cout<<times.parent_id()<<endl;
    cout<<grand.parent_id()<<endl;

    cout<<times.portal_name()<<endl;
    cout<<grand.portal_name()<<endl;

    SubwayPortal nothing_inside;

    cout<<nothing_inside<<endl;

    grand.get_portal(nothing_inside);

    cout<<nothing_inside<<endl;


    cout<<"compiles"<<endl;

	return 0;
}