#include <iostream>

//#include "_hash_item.h"
#include "_hash_item.cpp"
#include "hash_table.h"
#include "hash_table.cpp"

using namespace std;

int main()
{

	__ItemType ave("4 Avenue", 32);

	__ItemType st("4 Avenue", 22);

	cout<<ave.get_pos()<<endl;

	ave.set_pos(1999);

	cout<<ave.get_pos()<<endl;

	HashTable bruh(3);

	bruh.insert(ave);

	cout<<bruh.find(ave)<<endl;
	cout<<bruh.find(st)<<endl;

	cout<<st<<endl;


	return 0;
}