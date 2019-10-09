/******************************************************************************
  Title          : hash_table.h
  Author         : Leman Yan
  Created on     : April 8, 2019
  Description    : Interface description for a hash table class
  Purpose        : To define the minimal requirements of a hash table
  Usage          : Derive a concrete hash table class from this interface
  Build with     : no building
  Modifications  :



******************************************************************************/
#include <iostream>
#include "_hash_table.h"
#include "_hash_item.h"

#include <vector>

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

using namespace std;

// The INITIAL_SIZE should be large enough that it will not need to be
// resized, but you might want to implement resizing in your class.
#define INITIAL_SIZE 6151

enum lazy_deletion {Deleted=-1, Empty=0, Active=1};
/*
ACTIVE: it has an item in it
EMPTY: it has no item in it
DELETED: it had an item that was deleted it can be re-used

hash_table.h:37:10: warning: non-static data member initializers only available with -std=c++11 or -std=gnu++11
*/

//Used to construct hash table itself
struct Table
{
	__ItemType obj;
	int tag;

	Table();

};

class HashTable : public __HashTable
{
public:

	//Default constructor
	HashTable();

	//Make a HashTable of a given size
	HashTable(int size);	

    ~HashTable();

    /** find() searches in table for given item
     *  @precondition: item's key value is initialized
     *  @postcondition: if matching item is found, it is filled with value from
     *                  table.
     *  @param  ItemType [in,out] item : item to search for
     *  @return int 0 if item is not in table, and 1 if it is
     */
    //int find   ( __ItemType & item ) const; Removed const qualifier
    int find   ( __ItemType & item );


    /** insert() inserts the given item into the table
     *  @precondition: item is initialized
     *  @postcondition: if item is not in table already, it is inserted
     *  @param  ItemType [in] item : item to insert
     *  @return int 0 if item is not inserted in table, and 1 if it is
     */
    int insert ( __ItemType item   );

    /** remove() removes the specified  item from the table, if it is there
     *  @precondition: item's key is initialized
     *  @postcondition: if item was in table already, it is removed and copied
     *                  into the parameter, item
     *  @param  ItemType [in, out] item : item to remove
     *  @return int 0 if item is not removed from the table, and 1 if it is
     */
    int remove ( __ItemType  item );


    /** size() returns the number of items in the table
     *  @precondition: none
     *  @postcondition: none
     *  @return int the number of items in the table
     */
    int size() const;

    /** listall() lists all items currently in the table
     *  @note   This function writes each item in the tabel onto the given stream.
     *          Items should be written one per line, in whatever format the
     *          underlying _ItemType output operator formats them.
     *  @param  ostream [in,out] the stream onto which items are written
     *  @return int the number of items written to the stream
     */
    int listall ( ostream & os ) const;

private:

	vector<Table> hash_table;
	int number_of_items;
	int total_size;

	/*	resize() doubles the size of the arrray to a number that is a prime.
		Insert everything from the old hash table to the new hash table
	*/
	void resize();

	/*	hash uses Division Based Hashing
		h(x) = x % M
		@returns a hash value to put the item inside the hash table		
	*/
	unsigned int hash(unsigned int num) const;

	/* is_prime checks if a number is a prime or not
		@return 1 if num is prime 0 if not
	*/
	bool is_prime(int num) const;

	/*
		next_prime finds the next prime number after num
		@return a number that is a prime number that is greater than num
	*/
	int next_prime(int num) const;

};
#endif /* _HASH_TABLE_H_ */
