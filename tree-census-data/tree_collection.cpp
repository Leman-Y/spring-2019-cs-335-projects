/******************************************************************************
Title : tree_species.cpp
Author : Leman Yan
Created on : March 11,2019
Description : Tree Collection Class
Purpose : Store trees into this data set
Usage : Store data 


******************************************************************************/ 

#include "tree_collection.h"
#include "avl.cpp"
#include <cmath>

const double R = 6372.8;             // radius os Earth in km

const double TO_RAD = M_PI / 180.0;  // conversion of degrees to rads


TreeCollection::TreeCollection() : tree_count(0)
{
    boro_names[0].name = "Manhattan";
    boro_names[0].count = 0;
    boro_names[1].name = "Bronx";
    boro_names[1].count = 0;
    boro_names[2].name = "Brooklyn";
    boro_names[2].count = 0;
    boro_names[3].name = "Queens";
    boro_names[3].count = 0;
    boro_names[4].name = "Staten Island";
    boro_names[4].count = 0;
}

TreeCollection::TreeCollection(Tree& new_tree) : tree_count(0)
{
    boro_names[0].name = "Manhattan";
    boro_names[0].count = 0;
    boro_names[1].name = "Bronx";
    boro_names[1].count = 0;
    boro_names[2].name = "Brooklyn";
    boro_names[2].count = 0;
    boro_names[3].name = "Queens";
    boro_names[3].count = 0;
    boro_names[4].name = "Staten Island";
    boro_names[4].count = 0;

    add_tree(new_tree);
}

TreeCollection::~TreeCollection()
{
}


int TreeCollection::total_tree_count()
{
    return tree_count;

} // end of total_tree_count()


int TreeCollection::count_of_tree_species(const string& species_name)
{
    int count = 0;

    for(int i = 0; i < tree_info.size(); i++)
    {
        if(tree_info[i].name == species_name)
            count++;
    }

    return count;

} // end of count_of_tree_species()


int TreeCollection::count_of_tree_species_in_boro(const string& species_name,
                                                   const string& boro_name)
{
    // convert species_name and boro_name into uppercase
    string upper_species_name = species_name;
    string upper_boro_name = boro_name;

    for(int i = 0; i < upper_species_name.size(); i++)
        upper_species_name[i] = toupper(upper_species_name[i]);

    for(int i = 0; i < upper_boro_name.size(); i++)
        upper_boro_name[i] = toupper(upper_boro_name[i]);

    int count = 0;

    // search through tree_info for the matching elements
    for(int i = 0; i < tree_info.size(); i++)
    {
        if(tree_info[i].upper_name == upper_species_name &&
        tree_info[i].boro == upper_boro_name)
            count++;
    }

    return count;

} // end of count_of_tree_species_in_boro()


int TreeCollection::get_counts_of_trees_by_boro(const string& species_name,
                                                boro tree_count[5])
{
    bool exists = false; // keeps track of whether species_name exists or not

    string upper_species_name = species_name;

    for(int i = 0; i < upper_species_name.size(); i++)
        upper_species_name[i] = toupper(upper_species_name[i]);

    for(int i = 0; i < tree_info.size(); i++)
    {
        if(tree_info[i].upper_name == upper_species_name)
        {
            exists = true;

            // Increment the count of the appropriate borough
            if(tree_info[i].boro == "MANHATTAN")
            {
                tree_count[0].name = "Manhattan";
                tree_count[0].count++;
            }

            else if(tree_info[i].boro == "BRONX")
            {
                tree_count[1].name = "Bronx";
                tree_count[1].count++;
            }

            else if(tree_info[i].boro == "BROOKLYN")
            {
                tree_count[2].name = "Brooklyn";
                tree_count[2].count++;
            }

            else if(tree_info[i].boro == "QUEENS")
            {
                tree_count[3].name = "Queens";
                tree_count[3].count++;
            }

            else if(tree_info[i].boro == "STATEN ISLAND")
            {
                tree_count[4].name = "Staten Island";
                tree_count[4].count++;
            }
        }
    }

    if(exists) // if species_name was found
        return tree_count[0].count + tree_count[1].count + tree_count[2].count +
        tree_count[3].count + tree_count[4].count;
    else
        return 0;

} // end of get_counts_of_trees_by_boro()


int TreeCollection::count_of_trees_in_boro(const string& boro_name)
{
    string upper_boro = boro_name;

    for(int i = 0; i < upper_boro.size(); i++)
        upper_boro[i] = toupper(upper_boro[i]);

    if(upper_boro == "MANHATTAN")
        return boro_names[0].count;

    else if(upper_boro == "BRONX")
        return boro_names[1].count;

    else if(upper_boro == "BROOKLYN")
        return boro_names[2].count;

    else if(upper_boro == "QUEENS")
        return boro_names[3].count;

    else if(upper_boro == "STATEN ISLAND")
        return boro_names[4].count;

    else
        return 0;

} // end of count_of_trees_in_boro()


int TreeCollection::add_tree(Tree& new_tree)
{
    if(new_tree.id() != 0 && new_tree.borough_name() != "")  // tree is not NULL
    {
        collection.insert(new_tree);

        species.add_species(new_tree.common_name());


        // stores the uppercase of new_tree's boro and spc_common to allow
        // for easier comparison
        string upper_boro = new_tree.borough_name();
        string upper_spc_common = new_tree.common_name();

        for(int i = 0; i < upper_boro.size(); i++)
            upper_boro = toupper(upper_boro[i]);

        for(int i = 0; i < upper_spc_common.size(); i++)
            upper_spc_common = toupper(upper_spc_common[i]);


        // create a new TreeInfo object and initialize its values

        TreeInfo new_tree_info;

        double lat, longtd;

        new_tree.get_position(lat, longtd);

        new_tree_info.name = new_tree.common_name();
        new_tree_info.upper_name = upper_spc_common;
        new_tree_info.zip = new_tree.zip_code();
        new_tree_info.boro = upper_boro;
        new_tree_info.latitude = lat;
        new_tree_info.longitude = longtd;

        tree_info.push_back(new_tree_info);

        tree_count++;

        // update the tree count for the new_tree's appropriate borough
        if(upper_boro == "MANHATTAN")
            boro_names[0].count++;

        else if (upper_boro == "BRONX")
            boro_names[1].count++;

        else if(upper_boro == "BROOKLYN")
            boro_names[2].count++;

        else if(upper_boro == "QUEENS")
            boro_names[3].count++;

        else if(upper_boro == "STATEN ISLAND")
            boro_names[4].count++;

        return 1;
    }

    else
        return 0;

} // end of add_tree()


void TreeCollection::print_all_species(ostream& out) const
{
    species.print_all_species(out);

} // end of print_all_species()


void TreeCollection::print(ostream& out) const
{
     collection.printTree();

} // end of print()


list<string> TreeCollection::get_matching_species(const string& species_name) const
{
    list<string> matching_species = species.get_matching_species(species_name);

    return matching_species;

} // end of get_matching_species()


list<string> TreeCollection::get_all_in_zipcode(int zipcode) const
{
    bool match = false;

    list<string> all_in_zip;

    for(int i = 0; i < tree_info.size(); i++)
    {
        if(tree_info[i].zip == zipcode &&
        !already_in_list(all_in_zip, tree_info[i].upper_name))
        {
            match = true;
            all_in_zip.push_back(tree_info[i].name);
        }
    }

    if(!match)
        all_in_zip.push_back(""); // return an empty string

    return all_in_zip;

} // end of get_all_in_zipcode()


list<string> TreeCollection::get_all_near(double latitude, double longitude,
                                          double distance) const
{
    list<string> all_near;

    bool match = false;

    double lat2, lon2;

    for(int i = 0; i < tree_info.size(); i++)
    {
        match = true;

        lat2 = tree_info[i].latitude;
        lon2 = tree_info[i].longitude;

        if(haversine(latitude, longitude, lat2, lon2) <= distance &&
        !already_in_list(all_near, tree_info[i].upper_name))

           all_near.push_back(tree_info[i].name);
    }

    if(!match)
        all_near.push_back(""); // return an empty string

    return all_near;

} // end of get_all_near()


bool TreeCollection::already_in_list(const list<string>& list_to_search,
                                     const string& species) const
{
    bool in_list = false;
    string temp;

    for(list<string>::const_iterator it = list_to_search.begin();
    it != list_to_search.end(); it++)
    {
        temp = *it;

        // convert temp into uppercase
        for(int i = 0; i < temp.size(); i++)
            temp[i] = toupper(temp[i]);

        for(int i = 0; i < species.size(); i++)
        {
            if(species.find(temp) != string::npos)
                in_list = true;
        }
    }

    return in_list;

} // end of already_in_list()


// code taken from program specifications
double TreeCollection::haversine(double lat1, double lon1, double lat2,
                                 double lon2) const
{
    lat1 = TO_RAD * lat1;
    lat2 = TO_RAD * lat2;
    lon1 = TO_RAD * lon1;
    lon2 = TO_RAD * lon2;

    double d_lat = (lat2 - lat1) / 2;
    double d_lon = (lon2 - lon1) / 2;
    double a = sin(d_lat);
    double b = sin(d_lat);

    return 2 * R * asin(sqrt(a*a + cos(lat1) *  cos(lat2)*b*b));

} // end of haversine()
