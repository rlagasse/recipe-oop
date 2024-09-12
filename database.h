//database.h
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
#include <cstdlib>
#include <chrono>
#include <ctime>   


class Database {
private:
	int arr_size;
	int arr_cap;
	Recipe* database_arr;


public: 
	//Q14: construct array from file input
	Database (const string& fname) // read only file
	{
		//first open of file: count # of lines, initialize dynamic array
		std::fstream file1;
		file1.open(fname);
		if (file1.fail()) // if errors existing in file are true eg. unable to open
		{
			cmpt::error("Error: invalid file name.");
		}
		string fileline;
		int sizeo = 0; //# filelines

		//count # of lines in file
		while(!file1.eof())
		{
			getline(file1,fileline); //get each line
			if (fileline != "") //check if line is empty
			{
				sizeo++;
			}
		}
		//end of file, close to reopen later
	    file1.close();

		arr_size = sizeo; //set size of arr to # of lines, each line one element
		arr_cap = arr_size + 10; //add extra room initially in array
		database_arr = new Recipe[arr_cap]; //initialize array of databases
		int array_pos_counter = 0;

	    //second open of file, read each value into Recipe class
		std::fstream file;
		file.open(fname);
		if (file.fail()) // if errors existing in file are true eg. unable to open
		{
			cmpt::error("Error: invalid file name.");
		}

        int line_count = 0;
        string line; // each file line

        int i; // int to check which word for char to increment on
        string word; //current building word
        string recipe_name;
        string category;
        string author;
        int serving_size; //initialize each field as respecitive types
        // accumulate size/capacity of integers file, read to end of file
        while(!file.eof())
        { // reading each line
        	getline(file,line);
        	i = 0; 
        	word = "";
	        for (int j = 0; j < line.size(); j++) // read through line, separate values.
	        {
	        	if (line[j] != ',')
	        	{
	        		word += line[j]; // add each char to transitioning word.
	        	}
	        	else  //reached comma, one field finished, save. move to next field
	        	{
	        		switch(i) //switching words, saving previous word
	        		{
	        			case 0: //recipe name
	        			recipe_name = word;
	        			break;
	        			case 1: // category
	        			category = word;
	        			break;
	        			case 2: // author
	        			author = word;
	        			break;
	        			case 3: // serving size, change to str.
	        			serving_size = stoi(word);
	        			//cout << "I added a number to serving!\n";
	        			break;
	        		}
	        		i++;
	        		word = ""; //reset for next word, increment i
	        	}
	        	// add line to recipe
        	} // end of line
        	// initialize record at dynamic array pos
        	database_arr[array_pos_counter] = Recipe(recipe_name, category, author, serving_size);
        	array_pos_counter++; //go to next position of array
	        line_count++;
	    } // while loop end, checking each line.

	    // read to end of file, end of file
	    file.close();
	}


	int get_size() const //getter for size of database arr
	{
		return arr_size;
	}

	int get_cap() const // getter for database arr capacity, created space for elements
	{
		return arr_cap;
	}

	Recipe* get_database() const //returns pointer to database arr, used to access record fields.
	{
		return database_arr;
	}
	//database.add_recipe(recipe_name, category, author, serving_size);
	// Citation: use append(int s) from assignment 3 as baseline
	//adds one record to database, readjust size if necessary
	void add_recipe(string recipe, string category, string author, int serving)
	{

		if (arr_size < arr_cap) // add to end of array, don't change size
		{
			arr_size++;
			database_arr[arr_size-1] = Recipe(recipe, category, author, serving);
		}
		else if (arr_size >= arr_cap) //double size of capacity
		{
			while (arr_cap <= arr_size)
			{
				arr_cap = arr_cap*2; // adjust capacity
			}
			//initialize new array to adjusted capacity
			Recipe* new_database_arr = new Recipe[arr_cap]; //modified capacity
			for (int i=0; i < arr_size;i++) //copy over existing elements
			{
				new_database_arr[i] = database_arr[i];
			}
			// add new record to old position
			new_database_arr[arr_size] = Recipe(recipe, category, author, serving);
			arr_size++; // increment size by one; adding a class value

			// delete old array from memory, redirect to new array with pointer
			delete[] database_arr;
			database_arr = new_database_arr;
		}
	}

	// deletes records (>=1) from array by resizing
	// paramters: array of arr positions to delete, sizeof this array
	void delete_records(int delete_positions[], int delete_positions_size)
	{
		//delete contents database.txt so it can properly update/be overwritten
		ofstream ofs;
		ofs.open("database.txt", ofstream::out | ofstream::trunc);
		ofs.close();
		
		//create new array not including positions from delete_positions array, delete old array
		//keep same capacity, deincrement size
		Recipe* new_database_arr = new Recipe[arr_cap]; //same capacity
		int records_removed = 0;
		int j = 0; // counter through delete_positions_size array;
		int i = 0; //position of old array
		int p = 0; //position of new array
		bool endof_delete_positions = false;
		while (i < arr_size) //loop through delete pos array
		{
			//check if position in arr_size equals int to delete, if not equsl don't add
			if (i == delete_positions[j] && !endof_delete_positions) //boolean controls end arr reached
			{
				records_removed++; //skip over that record
				j++; //check next element in removed_positions array

				//reached end of delete_pos array, avoid accessing errors with bool
				if (j == delete_positions_size) //avoid error accessing invalid pos of delete_positions[]
				{
					j--;
					endof_delete_positions = true;
				}
			}
			else
			{
				new_database_arr[p] = database_arr[i];
				p++; //set next position of new array
			}
			i++; // loop though all elements of old array
		}
		//readjust sizeof array, modified #elements
		arr_size = arr_size - delete_positions_size; // increment size by one; adding a class value

		// delete old array, replace with new array pointer
		delete[] database_arr;
		database_arr = new_database_arr;
	}

	// called when user exits program, read entire database to file
	void write_records_to_file(const string& fname)
	{
		// open filename, check if valid
		std::fstream file;
		file.open(fname);
		if (file.fail()) // if errors existing in file are true eg. unable to open
		{
			cmpt::error("Error: invalid file name when trying to open.");
		}

		// write each line (record) to file, get formatted string, save each line
		for (int i=0; i< arr_size; i++)
		{
			file << database_arr[i].formatted_record() + "\n"; //add newline for each line
		}
		file.close();
	}

	// destructor, delete dynamic array. records deleted by their destructor in recipe.h
	~Database()
	{
		delete[] database_arr;
	}
	
}; // end of Database class

