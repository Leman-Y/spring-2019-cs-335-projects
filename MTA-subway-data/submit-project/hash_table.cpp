/******************************************************************************
  Title          : hash_table.cpp
  Author         : Leman Yan
  Created on     : April 8, 2019
  Description    : Interface description for a hash table class
  Purpose        : To define the minimal requirements of a hash table
  Usage          : Derive a concrete hash table class from this interface
  Build with     : no building
  Modifications  :



******************************************************************************/
#include <iostream>
#include "hash_table.h"

using namespace std;


Table::Table()
{
	tag=Empty;
}

HashTable::HashTable()
{
	hash_table.resize(INITIAL_SIZE);
	number_of_items=0;
	total_size=INITIAL_SIZE;
}

HashTable::HashTable(int size)
{
	int prime_number;
	number_of_items=0;

	if(1==is_prime(size) ) //Check if the size is prime
	{	
		hash_table.resize(size);
		total_size=size;

	}
	else				//Size is not prime so find a prime after it
	{
		prime_number=next_prime(size);
		hash_table.resize(prime_number);
		total_size=prime_number;	

	}
	
}

HashTable::~HashTable()
{}

//Using quadratic probing
int HashTable::find   ( __ItemType & item ) //const
{

	for(int probe=0;;probe++)
	{
		if(hash_table[hash(item.code()+probe*probe)].obj == item && hash_table[hash(item.code()+probe*probe)].tag == Active)
		{
			//5/10/19 New modification. Set the item's position as the object's position
			int position=hash_table[hash(item.code()+probe*probe)].obj.get_pos();
			item.set_pos(position);
			return 1; //Item is in table and is Active
		}
		else if(hash_table[hash(item.code()+probe*probe)].obj == item && hash_table[hash(item.code()+probe*probe)].tag == Deleted)
		{
			return 0; //Item is in table but it is Deleted
		}
		else if(hash_table[hash(item.code()+probe*probe)].tag == Empty)
		{
			return 0; //We do not need to search anymore. The item is not in the table
		}
	} 

}

int HashTable::insert ( __ItemType item   )
{


	if(find(item)==1) //Item is already in the table. Not necessary to insert
	{
		return 0;
	}
	for(int probe=0;;probe++)
	{
		//Item is in table and is Deleted. We need to reinitialize it to Active
		if(hash_table[hash(item.code()+probe*probe)].obj == item && hash_table[hash(item.code()+probe*probe)].tag == Deleted)
		{
			hash_table[hash(item.code()+probe*probe)].tag=Active;
			number_of_items++;

			//If I did hash_table.size() there would be a conflict of interest for some reason
			if(total_size/2==number_of_items) //Resize if table is half empty
			{
				resize();
			}

			return 1; 
		}
		//Another item but it is deleted
		else if(hash_table[hash(item.code()+probe*probe)].tag == Deleted)
		{
			hash_table[hash(item.code()+probe*probe)].tag=Active;
			hash_table[hash(item.code()+probe*probe)].obj=item;
			number_of_items++;

			if(total_size/2==number_of_items) 
			{
				resize();
			}

			return 1; 
		}
		//Empty slot so just insert the item
		else if(hash_table[hash(item.code()+probe*probe)].tag == Empty)
		{
			hash_table[hash(item.code()+probe*probe)].tag=Active;
			hash_table[hash(item.code()+probe*probe)].obj=item;
			number_of_items++;

			if(total_size/2==number_of_items) 
			{
				resize();
			}

			return 1;
		}				
	} 


}


int HashTable::remove ( __ItemType  item )
{

	if(0==find(item))	//Item not found so return 0
	{
		return 0;
	}
	for(int probe=0;;probe++)
	{
		if(hash_table[hash(item.code()+probe*probe)].obj == item && hash_table[hash(item.code()+probe*probe)].tag == Active)
		{
			hash_table[hash(item.code()+probe*probe)].tag=Deleted;
			number_of_items--;

			return 1;
		}		
	}
}


int HashTable::size() const
{
	return number_of_items;
}


int HashTable::listall ( ostream & os ) const
{

	for(int i=0; i<hash_table.size();i++)
	{
		if(hash_table[i].tag==Active) //Only print items that are Active
		{
			os<<hash_table[i].obj<<endl;
		}
	}

	return number_of_items;
}




////////////////////////////////Private////////////////////////////////////


void HashTable::resize()
{

	vector<Table> new_table(next_prime(hash_table.size()*2) ); //Brand new table with empty items and tag as Empty

	total_size=new_table.size();	//Reset the values
	number_of_items=0;

	vector<Table> old_table=hash_table;
	hash_table=new_table;

	for(int i=0; i<old_table.size(); i++)	//Insert everything that is active from the old_table to the new hash table
	{
		if(old_table[i].tag == Active)
		{
			insert(old_table[i].obj);
		}
	}


}

unsigned int HashTable::hash(unsigned int num) const
{
	return num%total_size;	//There was a bug earlier, because I was using hash_table.size() and total_size. Stick to one or the other.
}


/* is_prime checks if a number is a prime or not
	@return 1 if num is prime 0 if not
*/
bool HashTable::is_prime(int num) const
{
	//Not prime
	if(num <=1)
	{
		return 0;
	}	
	//Prime
	if( num == 2 || num == 3 || num == 5 || num==7)
	{
		return 1; 
	}
	//Not Prime
	if( (0==num%2) || (0==num%3) || (0==num%5) || (0==num%7) ) 
	{
		return 0; 
	}

	for(int i=11; i<num/2+1 ; i++)
	{	
		//Not prime
		if(num%i==0)
		{
			return 0;
		}
	}
	//Prime
	return 1;

 
}

int HashTable::next_prime(int num) const
{
	
	int prime_number=num+1;	//Next number
	while(0==is_prime(prime_number))
	{
		prime_number++;
	}
	return prime_number;
}








