/******************************************************************************
Title : tree.cpp
Author : Leman Yan
Created on : March 11,2019
Description : Tree Class
Purpose : Store values inside a tree object
Usage : Store data 


******************************************************************************/ 

#include <iostream>
#include <string>
#include <sstream> 
#include <iomanip>
#include<bits/stdc++.h> 

using namespace std;

#include "tree.h"

Tree::Tree()
{
	tree_id=0;
	tree_dbh=0;
	status="";
	health="";
	spc_common="";
	zipcode=0;
	address="";
	boroname="";
	latitude=0;
	longitude=0;


}

                       

/*
	Count the commas in the string. If less than 40 commas then make an empty tree
	If see a " then wait for another " to ignore the commas inside the quotes
	If there is a comma then count++ and also reset the string value
	convert strings into numbers
	Ex: NoDamage,Volunteer,"RootOther,BranchLights",No,No,Yes,No,No,N

*/
Tree::Tree(const string & str)
{

	string value;
	
	int count=0; //count commas

	for(int i=0; i<str.length() ; i++)
	{
		if(str[i]=='"') //Beginning Quote
		{
			for(int j=0; j<str.length()-i ; j++) //Add all the values in the quotes including the comma, but we dont want to count that comma towards the comma count
			{	
				value=value+str[i+j];

				if((j>0)  && (str[i+j]=='"')) //Ending Quote && Not the first quote
				{
					i=i+j;		//Update i;
					break;
				}
			}
		}


		if(str[i]!=',')
		{
			value=value+str[i];

		}

		if(str[i]==',')
		{
			count++; 

			if(1==count) //Pos 1 int tree_id
			{
				stringstream pos1(value);
				pos1 >> tree_id;
			}

			if(4==count) //Pos 4 int tree_dbh
			{
				stringstream pos4(value);
				pos4 >> tree_dbh;
			}

			if(7==count) //Pos 7 string status
			{
				status=value;

				if(status != "Alive" && status != "Dead" && status != "Stump" && status !="") //Invalid entry
				{
					tree_id=0;
					tree_dbh=0;
					status="";
					health="";
					spc_common="";
					zipcode=0;
					address="";
					boroname="";
					latitude=0;
					longitude=0;
					
					break;
				}
			}

			if(8==count) //Pos 8 string health
			{
				health=value;

				if(health != "Good" && health != "Fair" && health != "Poor" && health !="")
				{
					tree_id=0;
					tree_dbh=0;
					status="";
					health="";
					spc_common="";
					zipcode=0;
					address="";
					boroname="";
					latitude=0;
					longitude=0;

					break;
				}
			}

			if(10==count) //Pos 10 string spc_common
			{
				spc_common=value;
			}

			if(25==count) //Pos 25 string address
			{
				address=value;
			}

			if(26==count) //Pos 26 int zipcode
			{
				stringstream pos25(value);
				pos25 >> zipcode;
			}

			if(30==count) //Pos 30 string boroname
			{
				boroname=value;
				
				if(boroname != "Manhattan" && boroname != "Bronx" && boroname != "Brooklyn" && boroname != "Queens" && boroname != "Staten Island")
				{
					tree_id=0;
					tree_dbh=0;
					status="";
					health="";
					spc_common="";
					zipcode=0;
					address="";
					boroname="";
					latitude=0;
					longitude=0;
				
					break;
				}

			}

			if(38==count) //Pos 38 double latitude
			{
				stringstream pos38(value);
				pos38 >> latitude;
			}

			if(39==count) //Pos 39 double longitude
			{
				stringstream pos39(value);
				pos39 >> longitude;
			}
			value="";	
		}	
	}	
	
	if(count<40)
	{
		tree_id=0;
		tree_dbh=0;
		status="";
		health="";
		spc_common="";
		zipcode=0;
		address="";
		boroname="";
		latitude=0;
		longitude=0;

	}


}

Tree::Tree(int id, int diam,  string stat, string hlth, string name, 
	int zip, string addr, string boro, double lat, double longtd)
{
	tree_id=id;
	tree_dbh=diam;
	status=stat;
	health=hlth;
	spc_common=name;
	zipcode=zip;
	address=addr;
	boroname=boro;
	latitude=lat;
	longitude=longtd;


}

//Reference: https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=vs-2017
/*
	double num7=7.12345;

	stringstream str7;

	str7 <<setprecision (5)<< num7;

	string word=str7.str();

	cout<<word<<endl;

	Do string+=string or string+=char to add it to the end of the string
*/
ostream& operator<< (ostream & os, const Tree & t)
{
	string csv;
	
	stringstream pos1; //tree_id
	pos1 << t.tree_id;
	string word1=pos1.str();

	stringstream pos4; //tree_dbh
	pos4 << t.tree_dbh;
	string word2=pos4.str();

	
	csv=t.spc_common+csv.append(",")+word1;
	csv+=',';	
	csv+=word2;
	csv+=',';
	csv+=t.status;
	csv+=',';
	csv+=t.health;
	csv+=',';
	csv+=t.address;
	csv+=',';

	stringstream pos26; //zipcode
	pos26 << t.zipcode;
	string word3=pos26.str();

	csv+=word3;
	csv+=',';
	csv+=t.boroname;
	csv+=',';

	stringstream pos38; //latitude
	pos38 <<setprecision (5)<< t.latitude;
	string word4=pos38.str();

	stringstream pos39; //longitutde
	pos39 <<setprecision (5)<< t.longitude;
	string word5=pos39.str();

	csv+=word4;
	csv+=',';
	csv+=word5;

	os << csv;

	return os;
}

   
//Reference: https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/
/*
    // sl is the string which is converted to lowercase 
    string sl = "Jatin Goyal"; 
  
    // using transform() function and ::tolower in STL 
    transform(sl.begin(), sl.end(), sl.begin(), ::tolower); 
    cout << sl << endl; 
*/
bool operator==(const Tree & t1, const Tree & t2)
{
	string compare_t1=t1.spc_common;
	string compare_t2=t2.spc_common;

    transform(compare_t1.begin(), compare_t1.end(), compare_t1.begin(), ::tolower); 
    transform(compare_t2.begin(), compare_t2.end(), compare_t2.begin(), ::tolower); 

	if(compare_t1==compare_t2 && t1.tree_id==t2.tree_id)
	{
		return 1;

	}
	else
	{
		return 0;
	}

	
}

//Reference: https://stackoverflow.com/questions/15212820/do-and-on-c-strings-reflect-alphabetical-ordering
//string1<string2 compares the strings via ascii value. So if this statement is true than string1 is lexigraphically higher than string2.
bool operator<(const Tree & t1, const Tree & t2)
{
	string compare_t1=t1.spc_common;
	string compare_t2=t2.spc_common;

    transform(compare_t1.begin(), compare_t1.end(), compare_t1.begin(), ::tolower); 
    transform(compare_t2.begin(), compare_t2.end(), compare_t2.begin(), ::tolower); 

	if(string(compare_t1) < string(compare_t2) )
	{
		return 0; 
	}
	else if(compare_t1==compare_t2)
	{
		if(t1.tree_id < t2.tree_id)
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}

}

bool samename(const Tree & t1, const Tree & t2)
{
	string compare_t1=t1.spc_common;
	string compare_t2=t2.spc_common;

    transform(compare_t1.begin(), compare_t1.end(), compare_t1.begin(), ::tolower); 
    transform(compare_t2.begin(), compare_t2.end(), compare_t2.begin(), ::tolower); 

	if(compare_t1==compare_t2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool islessname(const Tree & t1, const Tree & t2)
{
	string compare_t1=t1.spc_common;
	string compare_t2=t2.spc_common;

    transform(compare_t1.begin(), compare_t1.end(), compare_t1.begin(), ::tolower); 
    transform(compare_t2.begin(), compare_t2.end(), compare_t2.begin(), ::tolower); 

	if(string(compare_t1 )< string(compare_t2) )
	{
		return 1;
	}

	else
	{
		return 0;
	}

}

string Tree::common_name() const
{
	return spc_common; 
}

string Tree::borough_name() const
{
	return boroname;
}

string Tree::nearest_address() const
{
	return address;
}

string Tree::life_status() const
{
	return status;
}

string Tree::tree_health() const
{
	return health;
}

int Tree::id() const
{
	return tree_id;
}

int Tree::zip_code() const
{
	return zipcode;
}

int Tree::diameter() const
{
	return tree_dbh;
}

void Tree::get_position(double & latitude,double & longitude) const
{
	latitude=Tree::latitude;
	longitude=Tree::longitude; 

}








                       
