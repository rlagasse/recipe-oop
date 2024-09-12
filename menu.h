//menu.h
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


#include <iostream>      
#include <fstream>      
#include <string>       
#include <algorithm>    
#include <cassert> 
#include <cstdlib>
#include <chrono>
#include <ctime>   
#include <stdio.h>
#include <ctype.h>
#include "recipe.h"
#include "database.h"
using namespace std;


// Runs main menu program, sub-menus
class Menu { 
private:
	string main_menu;
	string user_response;
	Database database;

public: 
	Menu() : user_response(" "), database("database.txt")
	{   
		cout << "Welcome to Rachel's Recipe Database!\n";
		main_menu = "Main Menu:\n\n\
		(a)dd a recipe\n\
		(f)ind a recipe\n\
		(d)elete a recipe\n\
		(l)ist recipes\n\
		(e)xit database\n";
		main_menu_page(); // run start-up main menu
	}

	void main_menu_page()
	{
		
		bool valid_response = false;

		while(!valid_response)
		{
			cout << main_menu << "\n"; // print main_menu message to user
			getline(cin, user_response);
			user_response = format_string(user_response);

			if (user_response.compare("a") == 0 || user_response.compare("add") == 0)
			{
				add_recipe(database);
			}
			else if (user_response.compare("f") == 0 || user_response.compare("find") == 0)
			{
				find_recipe(database);
			}
			else if (user_response.compare("d") == 0 || user_response.compare("delete") == 0)
			{
				delete_recipe(database);
			}
			else if (user_response.compare("l") == 0 || user_response.compare("list") == 0)
			{
				list_recipe(database);
			}
			else if (user_response.compare("e") == 0 || user_response.compare("exit") == 0)
			{
				//end of program,  save records to text file, return.
				cout << "Alright, ending program:\n";
				database.write_records_to_file("database.txt");
				cout << "Program has finished.\n";
				valid_response = true;
			}
			else 
			{
				cout << "Sorry, I did not understand. Please retype your request.\n";
			}
		}
	} // end of main_menu, returns to final_project.cpp to end program run; only called in exit

	string format_string(string& s) //removes whitespaces and lowercases responses
	{
		for (int i = 0; i < s.size(); i++)
		{
			s[i] = tolower(s[i]);
		}
		s.erase(remove(s.begin(),s.end(),' '),s.end());
		return s;
	}
	string lower_str(string s) //lowercases responses
	{
		for (int i = 0; i < s.size(); i++)
		{
			s[i] = tolower(s[i]);
		}
		return s;
	}

	// Add record to database
	void add_recipe(Database& database)
	{
		bool user_confirms = false; // user double checks entry.
		while (!user_confirms)
		{
			string recipe_name;
			string category;
			string author;
			int serving_size;

			string user_response;
			int int_user_response; //used for serving_size
			bool valid_recipe_name = false;
			bool valid_category_name = false;
			bool valid_author_name = false;
			bool valid_serving_size = false;
			
			cout << "Let's add a recipe!\n";
			cout << "Database current size: " << database.get_size() <<"\n";

			// 1. Recipe name
			while (!valid_recipe_name)
			{
				cout << "Type in name of recipe: ";
			    getline(cin, user_response); // get input
				int int_count = capitalize_string(user_response); //capitalize each word, check for # of integers.
				if (int_count != user_response.length()) //entire response is valid, if entirely type int, invalid input
				{
					valid_recipe_name = true;
				}
				else // all integer input, not valid recipe name
				{
					cout << "Invalid recipe name. Please enter a valid recipe name.\n";
				}
			} // got valid recipe name
			recipe_name = user_response;

			while (!valid_category_name)
			{
				cout << "Category options: (a)ppetizer, (b)owls & salads, (s)eafood, (e)ntree, (d)essert\n";
				cout << "Type in name of category: ";

				// get input, lowercase
			    getline(cin, user_response); 
			    user_response = format_string(user_response); //lowercase, remove whitespaces
			    valid_category_name = true;
			    // check valid input, if valid 
			    if (user_response.compare("a") == 0 || user_response.compare("appetizer") == 0)
				{
					user_response = "Appetizer"; 
				}
				else if (user_response.compare("b") == 0 || user_response.compare("bowls&salads") == 0)
				{
					user_response = "Bowls & Salads"; 
				}
				else if (user_response.compare("s") == 0 || user_response.compare("seafood") == 0)
				{
					user_response = "Seafood"; 
				}
				else if (user_response.compare("e") == 0 || user_response.compare("entree") == 0)
				{
					user_response = "Entree"; 

				}
				else if (user_response.compare("d") == 0 || user_response.compare("dessert") == 0)
				{
					user_response = "Dessert"; 
				}
				else 
				{
					cout << "Sorry, I didn't quite get that. I need a valid category.\n";
					valid_category_name = false; // stuck in while loop until valid
				}
				
			} // got valid category
			category = user_response; 

			// save authors name: no numbers, capitalize each word passed
			while (!valid_author_name)
			{
				cout << "Type in name of author: ";

			    getline(cin, user_response);
			    int whitespace_count = 0;
			    for (int i = 0; i < user_response.size(); i++) // count # whitespaces, if only empty input
			    {
			    	if (user_response[i] == ' ')
			    	{
			    		whitespace_count++;
			    	}
			    }
			    int integers_detected = capitalize_string(user_response); // capitalize each first word
			    // any integers detected, invalid for author's name.
			    if (integers_detected > 0 || user_response== "" || whitespace_count==user_response.size()) 
			    {
			    	cout << "Please retype name of author with no numbers.\n";
			    }
			    else 
			    {
			    	valid_author_name = true;
			    }
			}
			author = user_response;

			// now get serving size, must be type integer.
			while (!valid_serving_size)
			{
				cout << "Type in serving size of recipe: ";
			    getline(cin, user_response);

			    int serving_int_count = 0;

			    //remove whitespaces from response
			    user_response.erase(remove(user_response.begin(),user_response.end(),' '),user_response.end());
			    user_response = format_string(user_response);
			    //count number of integers
			    for (int i = 0; i < user_response.size(); i++)
			    {
			    	if (isdigit(user_response[i]))
			    	{
			    		serving_int_count++;
			    	}
			    }
			    //catch empty strings
			    if (user_response == "" || user_response == " ");
			    // all values are type int, valid response.
			    else if (serving_int_count == user_response.size())
			    {
			    	int_user_response = stoi(user_response);
			    	if (int_user_response < 1) //serving size is 0 or less, invalid. reask.
			    	{
			    		cout << "Serving size entered is invalid.\n";
			    	}
			    	else // valid response: type int and greater than 0: continue;
			    	{
			    		valid_serving_size = true;
			    	}
			    }
			    else //not all characters are type int. reask.
			    {
			    	cout << "Serving size entered is invalid.\n";
			    }
			}
			serving_size = int_user_response;

			cout << "I have recieved entry for: Recipe: " << recipe_name <<"; Category: " << category <<
			 "; Author: " <<  author << "; Serving size: " << serving_size << "\n";

			bool understandable_answer = false;
			 
			// check if this entry is already on file, check pre-existing record. 
			// pre-existing: all four records exactly match, recipies vary vastly
			for (int i = 0 ; i < database.get_size(); i++)
			{
				if (lower_str(database.get_database()[i].get_name()) == lower_str(recipe_name))
				{
					if (lower_str(database.get_database()[i].get_category()) == lower_str(category))
					{
						if (lower_str(database.get_database()[i].get_author()) == lower_str(author))
						{
							if (database.get_database()[i].get_servings() == serving_size)
							{
							    cout << "Sorry, that record already exists, I cannot add it to the database.\n";
							    understandable_answer = true; // reask from beginning
					            user_confirms = false;
							}

						}
					}
					
				}
			}

			string user_confirmation;
			while(!understandable_answer)
			{
				cout << "Would you like me to add this entry to the record? (y/n)\n";
				getline(cin, user_confirmation);
				user_confirmation = format_string(user_confirmation); //lowercase, remove whitespace

				// add record, end function
				if (user_confirmation.compare("y") == 0 || user_confirmation.compare("yes") == 0)
				{
					understandable_answer = true;
					user_confirms = true;
					// create recipe in database.h record, add to memory
					database.add_recipe(recipe_name, category, author, serving_size);
					cout << "Recipe successfully added!\n";
				}
				else if (user_confirmation.compare("n") == 0 || user_confirmation.compare("no") == 0)
				{
					cout << "Okay! Returning to main menu.\n";
					understandable_answer = true; // reask from beginning
					user_confirms = true;
				}
				else 
				{
					cout << "Sorry, I didn't quite get that. I need a valid category.\n";
					understandable_answer = false; // stuck in while loop until valid
				}
			} // end of understandable_answer()
			
		} // end of user_confirmation
		cout << "Returning to main menu...\n";
	} // end of add_recipe()

	// search for record in database:
	void find_recipe(Database& database)
	{
		string category_response;
		string match_type_response;
		string search_response;

		bool valid_response = false; 
		int searches_found = 0;
		cout << "Find a Recipe:\n\n";
		cout << "Search by:\n\n (r)ecipe name\n (c)ategory\n (a)uthor\n (s)ervings\n\n (m)ain menu\n";
		while (!valid_response) //wait until valid response given.
		{
			cout << "Enter the letter you want to search: "; // only get one letter
			getline(cin, category_response);
			for (int i = 0 ; i < category_response.size(); i++) //lowercase match type
			{
				category_response[i] = tolower(category_response[i]);
			}
			if (category_response == "r" || category_response == "c" || category_response == "a") // string types
			{
				bool valid_search_type = false;
				while (!valid_search_type)
				{
					valid_search_type = true;
					cout << "\nHow would you like to search?  \n\n\
					(e)xact match\n\
					(p)artial match\nType in the letter: ";
					getline(cin, match_type_response);
					for (int i = 0 ; i < match_type_response.size(); i++) //lowercase match type
					{
						match_type_response[i] = tolower(match_type_response[i]);
					}
					if (match_type_response == "e" || match_type_response == "p")
					{
						cout << "\nAnd what would you like to search for? \n";
						getline(cin, search_response); // save string user wants to search
						search_response = lower_str(search_response); //check lowercase version

						//call search; loop through entire array
						for (int i = 0; i < database.get_size(); i++)
						{
							if (category_response == "r") //Recipe
							{
								if (match_type_response == "e") // recipe exact match
								{
									//compare lowercased version on record to search response, for comparison
									if (lower_str(database.get_database()[i].get_name()) == search_response)
									{
										cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
										searches_found++;
									}
								}
								else if (match_type_response == "p") // recipe partial match
								{
									//check if substring exists in lowercased record
									if (lower_str(database.get_database()[i].get_name()).find(search_response)
									 != string::npos)
									{
										cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
										searches_found++;
									}
								}
							}
							else if (category_response == "c") // category
							{
								if (match_type_response == "e") // category exact match
								{
									if (lower_str(database.get_database()[i].get_category()) == search_response)
									{
										cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
										searches_found++;
									}
								}
								else if (match_type_response == "p") // category partial match
								{
									if (lower_str(database.get_database()[i].get_category()).find(search_response)
										!= string::npos)
									{
										cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
										searches_found++;
									}
								}
							}	
							else if (category_response == "a") // author
							{
								if (match_type_response == "e") // author exact match
								{
									if (lower_str(database.get_database()[i].get_author()) == search_response)
									{
										cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
										searches_found++;
									}
								}
								else if (match_type_response == "p") // author partial match
								{
									if (lower_str(database.get_database()[i].get_author()).find(search_response)
									 != string::npos)
									{
										cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
										searches_found++;
									}
								}
							}	
						} // for loop, increments through entire database, printing out exact/partial matches
						valid_response = true; // find_recipe() runs once, return to main menu.
						//check if any searches found
						if (searches_found == 0) // no matches found in database.
						{
							cout << "No matches found.\n";
						} //end main loop, return to main menu
					}
					else // exact/partial match type.
					{
						cout << "Sorry, I don't understand your response of search type. Please re-enter.\n";
						valid_response = false;
						valid_search_type = false; //re-ask search type
					}
				}

				
			} // end of category responses.
			else if (category_response == "s")// serving size, type int.
			{
				bool valid_search_type = false;
				int searches_found = 0;
				while (!valid_search_type)
				{
					valid_search_type = true;
					//int searches_found = 0;
					cout << "\nHow would you like to search?  \n\n\
					(e)xact match\n\
					(r)ange of numbers\nType in the letter: ";
					getline(cin, match_type_response);
					match_type_response = format_string(match_type_response); //lowercase str, remove whitespace
					if (match_type_response == "e") //exact match
					{
						cout << "\nAnd what would you like to search for? \n";
						getline(cin, search_response); // save string user wants to search
						for (int i = 0; i < database.get_size(); i++)
						{
							if (to_string(database.get_database()[i].get_servings()) == search_response) //check string version
							{
								cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
								searches_found = searches_found+1;
							}
						}
						valid_search_type = true;
					}
					else if (match_type_response == "r") //range of numbers to search
					{
						string user_serving_response;
						string min_number1; //initialize
						int min_number;
						string max_number1; 
						int max_number;
						bool valid_number = false;
						while(!valid_number)
						{
							valid_number = true;
							cout << "What is the minimum number? \n";
							getline(cin, min_number1);
							min_number1 = format_string(min_number1); //lowercase str, remove whitespace

							if (!is_integer(min_number1) || min_number1 == "") //invalid input, not int
							{
								valid_number = false;
							}
							else //valid, type int
							{
								min_number = stoi(min_number1);
							}
						
							cout << "What is the maximum number? \n";
							getline(cin, max_number1); // read in number, store as string
							max_number1 = format_string(max_number1);
							if (!is_integer(max_number1)|| max_number1 == "") //invalid, not int
							{
								valid_number = false;
							}
							else //valid input, convert string to int
							{
								max_number = stoi(max_number1); // convert to int
							}
							
							if (!valid_number)
							{
								cout << "Error occured in your entry. Please re-enter max/min numbers.\n";
							}
							else
							{
								if (min_number > max_number || min_number == max_number)
								{
								valid_number = false;
								cout << "Min can't be larger than max and cannot equal. please re-enter.\n";
								}
							}
						}
						
						// loop through database, increment from min to max number to list;
						int range_increment = min_number;
						for (int i = 0; i < max_number-min_number+1; i++) //loop through each # in range
						{
							for (int i = 0; i < database.get_size(); i++)
							{
								if (database.get_database()[i].get_servings() == range_increment) //check int version
								{
									cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
									searches_found = searches_found + 1;
									
								}
							}
							range_increment++; //increase number from min to max to print out
						} // end of printing range of numbers, low to high
						valid_search_type = true;	
						
					} // end of serving_size range of numbers
					else
					{
						cout << "Invalid search type. Please re-enter.\n";
						valid_search_type = false;
					}
					
				}
				
				// if no matches in database, print so, incremented by searches_found
				if (searches_found == 0)
				{
					cout << "No matches found in database.\n";
				}
				valid_response = true;
			} // end of serving size

			else if (category_response == "m")
			{
				valid_response = true;
			} // return find_recipe(), take back to main menu
			else
			{
				cout << "Sorry, I don't understand your response of category type. Please re-enter.\n";
				valid_response = false;
			}
		}	
		//string holder;
		cout << "Returning to main menu. \n";
	} // end find_recipe

	void delete_recipe(Database& database) // used find_recipe() as base
	{
		string category_response;
		string match_type_response;
		string search_response;

		bool valid_response = false; 
		int searches_found = 0;

		int delete_positions[database.get_size()]; // initialize array, holds positions of records to delete.
		(void) delete_positions;
		cout << "Delete recipies:\n\n";
		cout << "Search by:\n\n (r)ecipe name\n (c)ategory\n (a)uthor\n (s)ervings\n\n (m)ain menu\n";
		while (!valid_response)
		{
			valid_response = true;
			int arr_pos = 0;
			cout << "Enter the letter of category you want to delete: "; // only get one letter
			getline(cin, category_response);
			category_response = format_string(category_response); //lowercase
			if (category_response == "r" || category_response == "c" || category_response == "a") // string types
			{
				bool valid_search_response = false;
				while (!valid_search_response)
				{
					valid_response = true;
					valid_search_response = true;
					cout << "\nHow would you like to search to delete?  \n\n\
					(e)xact match\n\
					(p)artial match\nType in the letter: ";
					getline(cin, match_type_response);
					match_type_response = format_string(match_type_response); //lowercase, remove whitespace
					if (match_type_response == "e" || match_type_response == "p")
					{
						cout << "\nAnd what would you like to search for? \n";
						getline(cin, search_response); // save string user wants to search
						search_response = lower_str(search_response);
						//call search; loop through entire array
						for (int i = 0; i < database.get_size(); i++)
						{
							if (category_response == "r") //Recipe
							{
								if (match_type_response == "e") // recipe exact match
								{
									if (lower_str(database.get_database()[i].get_name()) == search_response)
									{
										cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
										searches_found = searches_found+1;
										delete_positions[arr_pos] = i; // add position to list of records to delete.
										arr_pos++;
									}
								}
								else if (match_type_response == "p") // recipe partial match
								{
									if (lower_str(database.get_database()[i].get_name()).find(search_response)
									 != string::npos)
									{
										cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
										searches_found = searches_found+1;
										delete_positions[arr_pos] = i; // add position to list of records to delete.
										arr_pos++;
									}
								}
							}
							else if (category_response == "c") // category
							{
								if (match_type_response == "e") // category exact match
								{
									if (lower_str(database.get_database()[i].get_category()) == search_response)
									{
										cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
										searches_found = searches_found+1;
										delete_positions[arr_pos] = i; // add position to list of records to delete.
										arr_pos++;
									}
								}
								else if (match_type_response == "p") // category partial match
								{
									if (lower_str(database.get_database()[i].get_category()).find(search_response)
									 != string::npos)
									{
										cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
										searches_found = searches_found+1;
										delete_positions[arr_pos] = i; // add position to list of records to delete.
										arr_pos++;
									}
								}
							}	
							else if (category_response == "a") // author
							{
								if (match_type_response == "e") // author exact match
								{
									if (lower_str(database.get_database()[i].get_author()) == search_response)
									{
										cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
										searches_found = searches_found+1;
										delete_positions[arr_pos] = i; // add position to list of records to delete.
										arr_pos++;
									}
								}
								else if (match_type_response == "p") // author partial match
								{
									if (lower_str(database.get_database()[i].get_author()).find(search_response)
									 != string::npos)
									{
										cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
										searches_found = searches_found+1;
										delete_positions[arr_pos] = i; // add position to list of records to delete.
										arr_pos++;
									}
								}
							}	

						} // for loop, increments through entire database, printing out exact/partial matches
						valid_response = true; // find_recipe() runs once, return to main menu.
						//check if any searches found
						if (searches_found == 0) // no matches found in database.
						{
							cout << "No matches found.\n";
						} //end main loop, return to main menu
					}
					else // exact/partial match type.
					{
						cout << "Sorry, I don't understand your response of search type. Please re-enter.\n";
						valid_response = false;
						valid_search_response = false;

					}
				}

				//ask user to delete said records
				if (searches_found > 0) // elements were added to array to delete, ask to delete.
				{
					bool delete_confirmation = false;
					string user_confirmation;
					while (!delete_confirmation)
					{
						delete_confirmation = true;
						cout << "Would you like to delete these records? (y/n)";
						getline(cin, user_confirmation);
						user_confirmation = format_string(user_confirmation); //lowercase
						if (user_confirmation == "y") // yes, delete records
						{
							// update database, remove from memory.
							database.delete_records(delete_positions, searches_found);
							cout << "Record deleted successfully.\n";
						}
						else if (user_confirmation == "n") // don't delete records
						{
							cout << "Alright, records not deleted.\n";
						}
						if (!cin) //invalid response
						{
							cout << "Please re-enter a response.\n";
							delete_confirmation = false;
						}
					}	
				}	
			} // end of category responses.
			else if (category_response == "s")// serving size, type int.
			{
				bool valid_search_type = false;
				int searches_found = 0;
				while (!valid_search_type)
				{
					valid_search_type = true;
					cout << "\nHow would you like to search?  \n\n\
					(e)xact match\n\
					(r)ange of numbers\nType in the letter: ";
					getline(cin, match_type_response);
					match_type_response = format_string(match_type_response);
					
					if (match_type_response == "e") //exact match
					{
						cout << "\nAnd what would you like to search for? \n";
						getline(cin, search_response); // save string user wants to search
						match_type_response = format_string(match_type_response);
						for (int i = 0; i < database.get_size(); i++)
						{
							// check string version of record
							if (to_string(database.get_database()[i].get_servings()) == search_response)
							{
								cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
								searches_found = searches_found+1;
								delete_positions[arr_pos] = i; // add position to list of records to delete.
								arr_pos++;
							}
						}
						valid_search_type = true;
					}
					else if (match_type_response == "r") //range of numbers
					{
						string user_serving_response;
						string min_number1; //initialize
						string max_number1; 
						int min_number; //initialize
						int max_number; 
						bool valid_number = false;
						while(!valid_number)
						{
							valid_number = true; //set as true to begining, bad input switch to false
							cout << "What is the minimum number? \n";
							getline(cin, min_number1); // read in #, getline() not used. not getting line of string.
							min_number1 = format_string(min_number1); //lowercase str, remove whitespace

							if (!is_integer(min_number1) || min_number1 == "") //invalid input, not int
							{
								valid_number = false;
								
							}
							else //valid, type int convert to string
							{
								min_number = stoi(min_number1);
							}
							cout << "What is the maximum number? \n";
							getline(cin, max_number1); // read in number, store as string
							max_number1 = format_string(max_number1);

							if (!is_integer(max_number1)|| max_number1 == "") //invalid, not int
							{
								//cout << "Please re-enter maximum number.\n";
								valid_number = false;
							}
							else //valid input, convert string to int
							{
								max_number = stoi(max_number1); // convert to int
							}
							if (!valid_number) // invalid input, re-ask
							{
								cout << "Error occured in your entry. Please re-enter max/min numbers.\n";
							}
							else
							{
								//check if min/max are invalid relatively
								if (min_number > max_number || min_number == max_number) 
								{
								//cout << "Min num. must be smaller than Max num. and can't equal. Please re-enter.\n";
								valid_number = false;
								cout << "Min can't be larger than max and cannot equal. please re-enter.\n";
								}
							}
						}
						// loop through database, increment from min to max number to list;
						int range_increment = min_number;
						for (int i = 0; i < max_number-min_number+1; i++) //loop through each # in range
						{
							for (int i = 0; i < database.get_size(); i++)
							{
								if (database.get_database()[i].get_servings() == range_increment) //check int version
								{
									cout << database.get_database()[i].formatted_record() << "\n"; //print out record;
									searches_found = searches_found+1;
									delete_positions[arr_pos] = i; // add position to list of records to delete.
									arr_pos++;
								}
							}
							range_increment++; //increase number from min to max to print out
						} // end of printing range of numbers, low to high
						
					} // end of serving_size range of numbers
				} //end of serving_size while loop
				
				// serving_size: if no matches in database, print so, incremented by searches_found
				if (searches_found == 0)
				{
					cout << "No matches found in database.\n";
				}
				valid_response = true;

				// serving_size: ask user to delete said records
				if (searches_found > 0) // elements were added to array to delete, ask to delete.
				{
					bool delete_confirmation = false;
					string user_confirmation;
					while (!delete_confirmation)
					{
						delete_confirmation = true;
						cout << "Would you like to delete these records? (y/n)";
						getline(cin, user_confirmation);
						user_confirmation = format_string(user_confirmation); //lowercase
						if (user_confirmation == "y") // yes, delete records
						{
							// update database, remove from memory.
							database.delete_records(delete_positions, searches_found);
							cout << "Record deleted successfully.\n";
						}
						else if (user_confirmation == "n") // don't delete records
						{
							cout << "Alright, records not deleted.\n";
						}
						if (!cin) //invalid response
						{
							cout << "Please re-enter a response.\n";
							delete_confirmation = false;
						}
					}	
				}	
			} // end of serving size
			else if (category_response == "m")
			{
				valid_response = true;
			} // return find_recipe(), take back to main menu
			else
			{
				cout << "Sorry, I don't understand your response of category type. Please re-enter.\n";
				valid_response = false;
			}
		}
		cout << "Returning to main menu. \n";
	}


	void list_recipe(Database& database) //used find_recipe() as a base
	{
		string category_response;
		string order_type_response;
		string search_response;
		bool valid_response = false; 
		
		cout << "List Recipies:\n\n";
		cout << "Fields:\n\n (r)ecipe name\n (c)ategory\n (a)uthor\n (s)ervings\n\n (m)ain menu\n";
		while (!valid_response)
		{
			valid_response = true;
			bool valid_order_response = false; 
			int searches_found = 0;

			cout << "Enter the letter of the field you want to list: "; // only get one letter
			getline(cin, category_response);
			for (int i = 0 ; i < category_response.size(); i++) //lowercase match type
			{
				category_response[i] = tolower(category_response[i]);
			}
			if (category_response == "r" || category_response == "c" || category_response == "a") // string type
			{
				while (!valid_order_response)
				{
					valid_order_response = true;
					cout << "\nWhat order would you like to list?  \n\n\
					(a)lphabetical order\n\
					(r)everse alphabetical order\nType in the letter: ";
					getline(cin, order_type_response);
					order_type_response = format_string(order_type_response); //lowercase, remove whitepsace

					if (category_response == "r") //recipe
					{
						if (order_type_response == "a") // recipe string alphabetical
						{
							sort(database.get_database(), database.get_database()+database.get_size(),
							[](const Recipe& left, const Recipe& right) 
							{
				    			return left.get_name() < right.get_name();
				    		});
						}
						else if(order_type_response == "r")//recipe string reverse alphabetical
						{
							sort(database.get_database(), database.get_database()+database.get_size(),
							[](const Recipe& left, const Recipe& right) 
							{
				    			return left.get_name() > right.get_name();
				    		});
						}
						else
						{
							valid_order_response = false;
						}
					}
					else if (category_response == "c") //category
					{
						if (order_type_response == "a") // category string alphabetical
						{
							sort(database.get_database(), database.get_database()+database.get_size(),
							[](const Recipe& left, const Recipe& right) 
							{
				    			return left.get_category() < right.get_category();
				    		});
						}
						else if(order_type_response == "r")//category string reverse alphabetical
						{
							sort(database.get_database(), database.get_database()+database.get_size(),
							[](const Recipe& left, const Recipe& right) 
							{
				    			return left.get_category() > right.get_category();
				    		});
						}
						else
						{
							valid_order_response = false;
						}
					}
					else if (category_response == "a") //author
					{
						if (order_type_response == "a") // author string alphabetical
						{
							sort(database.get_database(), database.get_database()+database.get_size(),
							[](const Recipe& left, const Recipe& right) 
							{
				    			return left.get_author() < right.get_author();
				    		});
							}
						else if(order_type_response == "r")//author string reverse alphabetical
						{
							sort(database.get_database(), database.get_database()+database.get_size(),
							[](const Recipe& left, const Recipe& right) 
							{
				    			return left.get_author() > right.get_author();
				    		});
						}
						else
						{
							valid_order_response = false;
						}
					}
					else //didn't understand order type
					{
						valid_order_response = false;
					}
					if (!valid_order_response) //invalid response
					{
						cout << "I don't understand. Please re-type your response.\n";
					}
				} // end of string valid_order_response while loop
				//loop through sorted (sorted by chosen string) array, print out each line.
				for (int i = 0; i < database.get_size(); i++)
				{
					cout << database.get_database()[i].formatted_record() << "\n";
					searches_found++;
				}
			} // end of string type
			else if (category_response == "s") //int type, serving size.
			{
				valid_order_response = false;
				while (!valid_order_response)
				{
					valid_order_response = true;
					cout << "\nWhat order would you like to list the serving sizes?  \n\n\
					(i)ncreasing order\n\
					(d)ecreasing order\nType in the letter: ";
					getline(cin, order_type_response);
					for (int i = 0 ; i < order_type_response.size(); i++) //lowercase order type
					{
						order_type_response[i] = tolower(order_type_response[i]);
					}
					if (order_type_response == "i") // int increasing order
					{
						//sort database by increased serving size. loop through from beg. to end of database, checking bool.
						sort(database.get_database(), database.get_database()+database.get_size(),
						[](const Recipe& left, const Recipe& right) 
						{
				    	return left.get_servings() < right.get_servings();
				    	});
					}
					else if(order_type_response == "d") // int decreasing order
					{
						// call sort of database based on decreasing serving size field
						sort(database.get_database(), database.get_database()+database.get_size(),
						[](const Recipe& left, const Recipe& right) 
						{
				    	return left.get_servings() > right.get_servings();
				    	});
					}
					else //didn't understand order type
					{
						cout << "I don't understand. Please re-type your response.\n";
						valid_order_response = false;
					}	
				} //end of serving size

				//all valid responses: loop through sorted array, print out each line.
				for (int i = 0; i < database.get_size(); i++)
				{
					cout << database.get_database()[i].formatted_record() << "\n";
					searches_found++;
				}
			}
			else if (category_response == "m") //return to main menu
			{
			}
			else // didn't understand response to category type, re-ask
			{
				cout << "Sorry, I don't understand your response of category type. Please re-enter.\n";
				valid_response = false;
			}
		} // end of valid category response while loop
		cout << "Returning to main menu.\n";
	} // end of list_recipe()

	//capitalize first letter of each word, returns number of. uses reference, modify s.
	int capitalize_string(string& user_response) 
	{
		int int_count = 0;
		
		// capitalize each word, if entire input is type int, ask for another input.
	    for (int i = 0; i < user_response.length(); i++)
		{
			if (i == 0 || i - 1 == ' ' )
			{
				user_response[i] = toupper(user_response[i]);
			} 
			//check if type int.
			if (isdigit(user_response[i]))
			{
				int_count++;
			}
		}
		return int_count;
	}

	// check if type int, returns true if int, false otherwise
	bool is_integer(string& s)
	{
		for (int i = 0; i < s.size(); i++)
		{
			if (!isdigit(s[i]))
			{
				return false;
			}
		}
		return true;
	}

	~Menu() //destructor
	{
	}
};