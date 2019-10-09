# MTA Subway Data Project 

## Summary 
Purpose of this project was to utilize MTA subway data and create a useful application out of it. I developed a C++ program where I implemented my own hash table and used disjoint sets to provide the user of the closest entrances and exits of stations, which entrances are part of the same stations, which stations are transfer points, and which stations and trains are closest to a given GPS location through 64 bit numbers and the Haversine Formula. In one sentence, my project simulates Google Maps for transportation specifically the subway and allows users to find the nearest subway stations

## How To Run?
1. Download repository
2. Usage: type in `g++ -o project -std=c++11 main.cpp subway_portal.cpp subway_station.cpp subway_system.cpp subway_route.o gps.cpp _hash_item.cpp hash_table.cpp` to create the executable file
3. Execute ./project 

	There are many commands you can run on the input file like list all stations, list station portals at a given location, list available subway routes at a given station, and list nearest portal from a given GPS coordinate

	```./project subwaydata_newstationnames.csv ./commandfiles/nearportal01_cmmd```

	```./project subwaydata_newstationnames.csv ./commandfiles/listall_cmmd```

	```./project subwaydata_newstationnames.csv ./commandfiles/listportals63Lex```