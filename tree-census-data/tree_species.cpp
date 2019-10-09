/******************************************************************************
Title : tree_species.cpp
Author : Leman Yan
Created on : March 11,2019
Description : Tree Species Class
Purpose : Be able to put species names into the class
Usage : Store data 


******************************************************************************/ 
#include <string>
#include <iostream>
#include <list>
#include <bits/stdc++.h> 

#include "tree_species.h"

using namespace std;

/*
	-My lexigrographical comparison does not work > , <, a<b but tree > wayne. How is that possible?
	- < , > might also compare the length which messes me up
*/

TreeSpecies::TreeSpecies()
{
 total_names=0;

}

TreeSpecies::~TreeSpecies()
{

}

//Reference: https://stackoverflow.com/questions/644673/fast-way-to-copy-one-vector-into-another
void TreeSpecies::print_all_species(ostream & out) const
{
	for(int i=0 ; i<names.size(); i++)
	{
		out << names[i]<<endl;
	}

}


int TreeSpecies::number_of_species() const
{
	
	return total_names;
}


/*
Reference: https://stackoverflow.com/questions/14297185/comparing-strings-lexicographically
	string compare_t1=t1.spc_common;
	string compare_t2=t2.spc_common;

    transform(compare_t1.begin(), compare_t1.end(), compare_t1.begin(), ::tolower); 


	if("treeeee"<"wayne")	//This compares the length as well
	{
		cout<<"treeeee<wayne "<<endl;
	}
	if("treeeee">"wayne")
	{
		cout<<"treeeeee>wayne"<<endl;
	}
	if(string("treeeee")<string("wayne"))	//This syntax actually compares the two string lexigraphically
	{
		cout<<"treeeee<wayne "<<endl;
	}
	if(string("treeeee")>string("wayne"))
	{
		cout<<"treeeeee>wayne"<<endl;
	}
*/
/*
	Issue: This add_species will add Douglas-fir and Douglas fir. I do not check hypens
*/
int TreeSpecies::add_species( const string & species) 
{
	string lowerc_name=species;

    transform(lowerc_name.begin(), lowerc_name.end(), lowerc_name.begin(), ::tolower); 

	if(0==names.size())	//Empty vector
	{
		names.push_back(lowerc_name);
		total_names+=1;
		return 1;
	}

	for(int index=0; index < names.size() ; index++) //Check if the species name is already in the vector
	{
		if(lowerc_name == names[index])
		{
			return 0;
		}
	}

	//Species is not in container
	if(lowerc_name < names[0]) //If the species' name is before the first name at the vector then put it in the front
	{	//Name's ascii value is higher than lowerc_name's
		names.insert(names.begin(), lowerc_name);
		total_names+=1;
		return 1;
	}

	if(string(lowerc_name) > string(names[names.size()-1]) )	//Check if the species' name is after the last name in the vector
	//Forgot to do -1 which led to segmentation fault error. Was going out of bounds of the vector. 
	{
		names.push_back(lowerc_name);
		total_names+=1;
		return 1;
	}

	for(int i=0; i<names.size() ; i++)
	{
		if( (string(lowerc_name) > string(names[i]) ) && (string(lowerc_name) < string(names[i+1]))  )
		{
			names.insert(names.begin()+i+1, lowerc_name);	//Add one because you want to add it in between the two not in front of the first
			break;
		}

	}

	total_names+=1;
	return 1;
}
/*
	vector<string> names;

	int total_names;

	int count_spaces_and_hyphens(string name) const;
*/

list<string> TreeSpecies::get_matching_species(const string & partial_name) const
{
	list <string> matching_names;

	vector<string> words_of_partial;

	vector<string> words_of_tree;

	int count_of_partial_name=count_spaces_and_hyphens(partial_name); //count of spaces and hyphens in partial name

	string lowerc_name=partial_name; 	//Turn partial_name into its lowercase form
    transform(lowerc_name.begin(), lowerc_name.end(), lowerc_name.begin(), ::tolower); 

	string word=""; //For the words in the species name. Upload each word into a vector

	for(int i=0; i<names.size() ; i++)	//Iterate through the tree names in the vector
	{
		int count_of_tree_name=count_spaces_and_hyphens(names[i]);	//count of spaces and hyphens in tree name

		if(lowerc_name == names[i])		//Same name
		{
			matching_names.push_back(lowerc_name);
		}
		else if( (0==count_of_partial_name) && (0<count_of_tree_name) ) //Partial name is one word and tree name is multiple words
		{
			for(int index=0; index<names[i].length() ; index++)	//Iterate through the word in the vector of species names
			{
				if( (names[i][index]==' ') ||  (names[i][index]=='-') )	//If you find a space or hyphen add the word to the vector			
				{
					words_of_tree.push_back(word);	//Add the word to the vector
					word="";	//Reset the word
					//index++; //Skip the space No need to index since we are not adding a character in this round for the for loop
				}
				else
				{	
					word+=names[i][index];
					if(index == names[i].length()-1) //Last char
					{
						words_of_tree.push_back(word);	//Add the word to the vector
						word="";	//Reset the word
					}
				}				

			}
			for(int j=0; j<words_of_tree.size() ; j++)
			{	
				if(words_of_tree[j] == lowerc_name)
				{
					matching_names.push_back(names[i]);
					break;
				}
			}
			
			words_of_tree.clear();		//Clear the vector after use
		}
		//Issue: If there are duplicates in the tree name, then this could be wrong.
		else if( (0<count_of_partial_name) && (0<count_of_tree_name) ) //Partial name is multiple words and tree name is multiple words
		{
			//count of where to start the subsequence check
			//check if the first word of partial name is even in the tree name of words
			//put words into words_of_tree
			//put words into words_of_partial
			// string word

			//Add words of partial name into vector for partial name
			for(int index_for_partial=0; index_for_partial<partial_name.length() ; index_for_partial++)	//Iterate through the word in the vector of species names
			{
				if( (partial_name[index_for_partial]==' ') ||  (partial_name[index_for_partial]=='-') )	//If you find a space or hyphen add the word to the vector			
				{
					words_of_partial.push_back(word);	//Add the word to the vector
					word="";	//Reset the word
					//index++; //Skip the space No need to index since we are not adding a character in this round for the for loop
				}
				else
				{	
					word+=partial_name[index_for_partial];
					if(index_for_partial == partial_name.length()-1) //Last char
					{
						words_of_partial.push_back(word);	//Add the word to the vector
						word="";	//Reset the word
					}
				}				

			}
			
			//Add words of tree name into vector for tree name
			for(int index_for_species=0; index_for_species<names[i].length() ; index_for_species++)	//Iterate through the word in the vector of species names
			{
				if( (names[i][index_for_species]==' ') ||  (names[i][index_for_species]=='-') )	//If you find a space or hyphen add the word to the vector			
				{
					words_of_tree.push_back(word);	//Add the word to the vector
					word="";	//Reset the word
					//index++; //Skip the space No need to index since we are not adding a character in this round for the for loop
				}
				else
				{	
					word+=names[i][index_for_species];
					if(index_for_species == names[i].length()-1) //Last char
					{
						words_of_tree.push_back(word);	//Add the word to the vector
						word="";	//Reset the word
					}
				}				

			}

			int index_start=0;	//Used to compare partial name subsequence with the species name sequence
			for(int k=0 ; k<words_of_tree.size(); k++)
			{
				if(words_of_tree[k] == words_of_partial[0])
				{
					index_start=k;

				    //We will not go off the vector of tree name when comparing with the subsequence of partial name
					if( (index_start+words_of_partial.size()) <= words_of_tree.size() )
					{
						//Add the words into the subsequence strings then compare if they are identical. If yes then add this word to the list
						string subsequence_of_partial;
						string subsequence_of_species;

						for(int l=0; l<words_of_partial.size(); l++)
						{
							subsequence_of_partial+=words_of_partial[l];
						}
						for(int m=0; m<words_of_partial.size(); m++)
						{
							subsequence_of_species+=words_of_tree[index_start+m];
						}
						if(subsequence_of_partial==subsequence_of_species)
						{
							matching_names.push_back(names[i]);
						}
						subsequence_of_partial="";
						subsequence_of_species="";

					}
					index_start=0;

					break;
				}
			}
			words_of_partial.clear();
			words_of_tree.clear();
		}

	}
/*
	cout<<"------------"<<endl;
    list <string> :: iterator it; 
    for(it = matching_names.begin(); it != matching_names.end(); ++it) 
        cout<< *it<<endl;
	cout<<"------------"<<endl;
*/
	return matching_names;
}

//------------- Private Functions --------------------------

int TreeSpecies::count_spaces_and_hyphens(string name) const
{
	int count=0;

	for(int i=0; i<name.length(); i++)
	{
		if( (name[i]==' ') || (name[i]=='-') )
		{
			count++;
		}
	}

	return count;
}















