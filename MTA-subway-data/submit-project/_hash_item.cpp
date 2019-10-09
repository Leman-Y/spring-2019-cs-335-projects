/******************************************************************************
  Title          : _hash_item.cpp
  Author         : Leman Yan
  Created on     : April 8, 2019
  Description    : Defines an item type that can be used in the project
  Purpose        : To define the item type to be hashed
  Usage          :
  Build with     :
  Modifications  :
	4/9/2019 by Leman Yan - encode is taken from the chapter notes of Stewart Weiss


******************************************************************************/

#include <iostream>
#include <string>
#include<bits/stdc++.h> 

#include "_hash_item.h"

using namespace std;


__ItemType::__ItemType(): name(""), position(-1)
{
}

__ItemType::__ItemType(string s, int pos): name(s), position(pos)
{
}


void __ItemType::set(string s, int pos) 
{
	name=s;
	position=pos;
}


void __ItemType::get(string & s, int & pos)
{
	s=name;
	pos=position;
}

bool __ItemType::operator==( __ItemType rhs) const
{
	if( (name==rhs.name) )
	{
		return 1;
	}
	else
	{		
		return 0;
	}
}	

 unsigned int __ItemType::encode ( const int RADIX, const string & s)
{
	 unsigned int hashval = 0;
	for (int i = 0; i < s.length(); i++)
	hashval = s[i] + RADIX * hashval; // p(x) = s_i + x(q(x))
	return hashval;
}


 unsigned int __ItemType::code()
{
	if(name !="")	//Key is a string
	{

		string empty=name;
		transform(empty.begin(), empty.end(), empty.begin(), ::tolower); 
		return encode(27, empty);
					
	}
	else	//Key is an int. Not sure how I could give the option to assign to a different number. What number would I assign it to?
	{
		return position;
	}
}

 ostream &  operator<<( ostream & os, __ItemType item ) 
{
	
	return os<<"name "<<item.name<<" "<<"position "<<item.position;
}


void __ItemType::set_pos(int pos)
{
	position=pos;
}


int __ItemType::get_pos()
{

	return position;
}




