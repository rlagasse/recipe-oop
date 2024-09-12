//recipe.h
// stores one single recipe record
/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Rachel Madeline Lagasse
// St.# : 301395285
// Email: rlagasse@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////
//

#include "cmpt_error.h" 
#include <iostream>    
#include <fstream>     
#include <string>     
#include <algorithm>   
#include <cassert>      

using namespace std;

// creates one record of database, stored in database.h dynamic array
class Recipe 
{
private:
	string recipe_name;
	string menu_category;
	string author;
	int servings;

public: 
	Recipe() //default constructor, needed to create empty arr of type Recipe; database.h
	{}

	Recipe(string name, string category, string  a, int serv) 
	: recipe_name(name), menu_category(category), author(a), servings(serv)
	{   
	}

	// getter, return name of recipe
	string get_name() const
	{
		return recipe_name;
	}

	// getter, return category
	string get_category() const
	{
		return menu_category;
	}

	// return name of author
	string get_author() const
	{
		return author;
	}

	// return name of author
	int get_servings() const
	{
		return servings;
	}

	// return formatted record, used for listing and sending to file database.txt when ended
	string formatted_record() const
	{
		return recipe_name + "," + menu_category + "," + author + "," + to_string(servings) + ",";
	}

}; //end of Recipe class