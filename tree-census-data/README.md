# Tree Census Data Project 

## Summary 
I built a C++ application, which allowed users to query NYC Open Data (2015 Street Tree Census) and obtain information from more than 680,000 trees in NYC using an AVL tree. I also applied the Haversine Formula to analyze data on trees such as the trees’ species, location, and distance from a given GPS location. Through my application, a user would be able to figure out through the program how many trees of a given species there are borough by borough, or which trees are within a distance of a given GPS location. The user will be able to specify a fragment of a species common name, such as oak and the program will display the frequency of occurrence of all types of oak trees throughout the city, such as pin oaks, sawtooth oaks, scarlet oaks, and white oaks. A user could also just input a specific species like White Oak and that would print out the number of White Oaks in the city. 

## How To Run?
1. Download repository
2. Usage: type in ./goldversion input_file command_file

	There are many commands you can run on the input file like list all trees, list all trees in a zipcode, tree info, etc

	```./goldversion input_file command_file```

	```./goldversion 100_trees.csv ./commandfiles/listall_cmmd_01```

	```./goldversion manhattan_trees.csv ./commandfiles/listall_cmmd_01```
