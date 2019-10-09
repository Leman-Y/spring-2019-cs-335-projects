/******************************************************************************
Title : tree_species.h
Author : Leman Yan
Created on : March 11,2019
Description : Tree Collection Class
Purpose : Store trees into this data set
Usage : Store data 


******************************************************************************/ 


#ifndef _TREE_COLLECTION_H_
#define _TREE_COLLECTION_H_

#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <cmath>

#include "__tree_collection.h"
#include "avl.h"
#include "tree_species.h"
#include "tree.h"

class TreeCollection : public __TreeCollection
{

public:

    TreeCollection(); // Default Constructor

    TreeCollection(Tree& new_tree);

    ~TreeCollection(); // Destructor


    // Functions to override from __TreeCollection

    /** total_tree_count() returns total number of trees in data set
     *  @return int count of trees in collection
     */
    int total_tree_count();


    /** count_of_tree_species(s) returns number of trees with name s
     * @param  string species_name [in] species name to search for
     * @return int the number of trees that have the given species name
     */
    int count_of_tree_species(const string& species_name);


    /** count_of_tree_species_in_boro(s,b) returns number of trees with name s
     *                                     in boro b
     * @note This returns the number of Tree objects in the collection whose
     *       spc_common name matches the species_name specified by the
     *       parameter s.
     *       This method is case insensitive. If the method is
     *       called with a non-existent species s, the return value should be 0.
     * @param  string species_name [in] species name to search for
     * @param  string boro_name [in] species borough to look in
     * @return int the number of trees in boro that have the given species name
     */
    int count_of_tree_species_in_boro(const string& species_name,
                                       const string& boro_name);


    /** get_counts_of_trees_by_boro(s,t) puts number of trees matching name s
    *                                     in all boros into param t
    * @note This puts the number of Tree objects in the collection whose
    *       spc_common name matches the species_name specified by
    *       parameter s into the boro_name array.
    *       This method is case insensitive.
    *       If the method is called with a non-existent species s,
    *       the return value should be 0.
    * @param  string species_name [in] species name to search for
    * @param  boro boro_name[5] [in,out] array of boro structures
    * @pre    boro_name[k].count ==0 for k = 0,...,4 and
    *         boro_name[k].name is initialized with boro name[k]
    * @post   boro_name[k].count has count of trees of given species in boro[k]
    * @return int the total number of trees of given species in all boros
    */
    int get_counts_of_trees_by_boro(const string& species_name,
                                    boro tree_count[5]);


    /** count_of_trees_in_boro(b) returns number of trees of all types in boro b
    * @param  string boro_name [in] species borough to look in
    * @return int the number of trees in boro boro_name
    */
    int count_of_trees_in_boro(const string& boro_name);


    /** add_tree(t) inserts Tree t into the collection, updates species list and
    *              borough counts.
    * @param Tree new_tree [in] the tree to be inserted
    * @return int the number of trees inserted: 0 if none, 1 if inserted
    */
    int add_tree(Tree& new_tree);


    /** print_all_species(out) prints all species names on out, one per line
    *  This writes the set of all common names found in the data set to the
    *  output stream out, one per line. The species names are printed in
    *  lexicographic order, using the default string comparison ordering
    *  @param ostream& [in,out]  out  the stream to be modified
    */
    void print_all_species(ostream& out) const;


    /** print(out) prints all tree data on out, one tree per line, sorted
    *  @notes
    *  This writes the entire data set to the output stream out, one tree
    *  per line, in sorted order by tree species common name as primary key,
    *  and then by tree id as a secondary key.
    *  The members of the Tree object are  printed in the same
    *  order as they are described in the Tree class Data Dictionary, EXCEPT
    *  THAT the species common name is printed FIRST.
    *  @param ostream& [in,out]  out  the stream to be modified
    */
    void print(ostream& out) const;


    /** get_matching_species(s) returns a list<string> containing a list of all
    *                  tree species common names that match species_name.
    * @notes
    *       This method is case insensitive.
    *       The list returned by this function should not contain any
    *       duplicate names and may be empty.
    * @param string species_name [in] the partial name to match
    * @return list<string> a list of species names that match species_name
    */
    list<string> get_matching_species(const string& species_name) const;


    /** get_all_in_zipcode(z) returns a list<string> containing a list of all
    *                  tree species common names in zipcode z.
    * @notes
    *       This method is case insensitive.
    *       The list returned by this function should not contain any
    *       duplicate names and may be empty.
    * @param int zipcode [in]  the zipcode in which to search
    * @return list<string> a list of species names in zipcode
    */
    list<string> get_all_in_zipcode(int zipcode) const;


    /** get_all_near(lat,lng,dist) returns a list<string> containing a list of
    *                  all tree species within dist km of point (lat,lng)
    * @notes
    *       The list returned by this function should not contain any
    *       duplicate names and may be empty.
    * @param double latitude   [in]  the latitude
    * @param double longitude  [in]  the longitude
    * @param double distance   [in]  the distance in kilometers
    * @return list<string> a list of species names within distance km of
    *                     GPS point (latitude,logitude)
    */
    list<string> get_all_near(double latitude, double longitude,
                              double distance) const;


    /** Checks to see if the input species is already in the list
    *   @note this method is case-insensitive
    *   @param list<string> list_to_search [in],
    *          string species[in] to search for, and is assumed to be uppercase
    *          when passed in to allow for case-insensitivity
    *   @return true if species already exists, false otherwise
    */
    bool already_in_list(const list<string>& list_to_search,
                         const string& species) const;


    /** Calculates the distance in km between two sets of GPS coords using the
    *   Haversine formula
    *   @param lat1[in], lon1[in], lat2[in], lon2[in]
    *   @return the distance between the two coords
    */
    double haversine(double lat1, double lon1, double lat2, double lon2) const;

private:

    struct TreeInfo{

        string name;
        string upper_name;       // species name in uppercase
        string boro;             // boro stored in uppercase
        double latitude;
        double longitude;
        int zip;
    };


    AvlTree<Tree> collection;

    int tree_count;             // holds the total number of trees in collection

    TreeSpecies species;        // holds the species names

    vector<TreeInfo> tree_info;     // holds the tree's species names and
                                    // zipcodes as to allow for easier count of
                                    //trees of a specific species in a zipcode
                                    // and boro

    boro boro_names[5];         // holds the count of total trees in each boro

};

#endif //_TREE_COLLECTION_H_
