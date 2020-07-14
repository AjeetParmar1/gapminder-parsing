/*This project was made by Ajeet Parmar on July 2020. This project takes in information 
from Gapminder (done via R), and stores it in a custom hash function in hash.h. 
country.h is the country class and holds both country information and query information. */
#include <iostream> 
#include <fstream>

#include "country.h"
#include "Hash.h"
using namespace std; 

/*These are the function declarations for my helper functions. True_or_false() handles
different queries given a country. For example, if someone only specified 2 arguments,
True_or_false() qould generate the query so that it can be inserted into the hash table,
filled with the country info, and then retrieved once the user specifies it. 
help_text() and info_text() simply output the help information and general information
repsectively. */
void permute_filters(int pos, std::vector<int> filter, country& c, Hash& table);
void help_text();
void info_text();


int main(){
    // file which holds all the info. 
    string input_file = "gapminder.txt"; 
    ifstream input_object(input_file); 

    /*If the user doesn't have the file with all the information, 
    I run an error message.*/
    if(!input_object.good()){
        cerr << "Error: " << input_file << " not found" << endl; 
        cerr << "For the program to work, you need to include in the directory" << input_file; 
        cerr << " with this file." << endl;
        return 1; 
    }else{
        /* Otherwise, I initialize the hash table with a size of
        11000, collect the country information, store the
        country information in a class then put it in the vector "countries",
        run true_or_false() to generate all possible queries, 
        then put all the countries in the hash table. */

        vector <country> countries; 
        Hash table(11000); 
        cout << "collecting data from gapminder.txt..." << endl;
        string line; 
        /*since the column names appear, misc stores this info 
        so that it will not break the program if it is initialized 
        as a country object.*/
        string misc; 
        input_object >> misc; 
        while(input_object >> line){
        country object(line);
        permute_filters(0, vector <int>(), object, table);
        countries.push_back(object);
        }
         cout << "inputting country info" << endl;
        // this is where I insert each country from the vector "countries". 
       for(uint x = 0; x < countries.size(); ++x){
            table.countryinsert(countries[x]); 
            cout << x << " out of " << countries.size() << " inserted." << endl;
        }
        while(true){
            string command; 
            // This is where I output instructions to the user.
            cout << "data collected" << endl; 
            cout << "Welcome to the gapminder parsing project. This project extracted data from the gapminder data available through R." << endl; 
            cout << "and stored it in a custom hash table. Here are the flags you can use to search the database:" << endl; 
            cout << " -c allows you to search for a specific entry" << endl; 
            cout << "-? pulls up the help menu" << endl;
            cout << "-info pulls up information on this project" << endl;
            cout << "-ex exits the program" << endl;
            cout << "Please enter your commands: " << endl; 
            cin >> command;
            // I erase all spaces from the command to avoid error. 
            command.erase(remove_if(command.begin(), command.end(), ::isspace), command.end());
            //If the command is -c, I allow the user to search the hash table
            if(command == "-c"){
                // allows the user to keep searching until specified. 
                while(true){
                    string name = ""; 
                    int year; 
                    string yearq;
                    string continent = ""; 
                    string region0 = ""; 
                    string region1 = ""; 
                    string region; 
                    cout << "For each query, enter \"NA\" if you don't want to specify that query"; 
                    cout << " or enter \"000\" to break out of searching mode. " << endl;
                    cout << "Please enter the name of the country." << endl; 

                    cin >> name; 
                    // erases all spaces from the country name to avoid error. 
                    name.erase(remove_if(name.begin(), name.end(), ::isspace), name.end());
                    if(name == "NA")
                        name = ""; 
                    else if(name == "000")
                        break; 

                    cout << "Please enter the year" << endl; 
                    cin >> yearq; 
                    // takes the year in and converts it to an int if the user doesn't put NA. 
                    if(yearq == "NA")
                        year = 0; 
                    else if(year == 000)
                        break; 
                    else{
                        try{
                            year = stoi(yearq);
                        }
                        catch(invalid_argument& error){
                            cout << "Error: input cannot be converted into an integer" << endl;
                        }
                    }
                    cout << "Please enter the continent" << endl; 
                    cin >> continent; 
                    // erases spaces from the continent input to avoid error. 
                    continent.erase(remove_if(continent.begin(), continent.end(), ::isspace), continent.end());
                    if(continent == "NA")
                        continent = ""; 
                    else if(continent == "000")
                        break; 
                    // erases the spaces from the region input. 
                    cout << "Please enter the region" << endl; 
                    cin >> region; 
                    region.erase(remove_if(region.begin(), region.end(), ::isspace), region.end());
                    if(region == "NA")
                        region = ""; 
                    else if(region == "000")
                        break; 

                    /* This generates the query regarding the user's indicated input. From here,
                    printquery() searches for the query and prints it.*/
                    country query(name, year, continent, region); 
                    table.printquery(query); 
                }
            }else if(command == "-?"){
                /* If the user needs help, I run help_text() to 
                print the help info to the console. */
                help_text(); 
            }else if(command == "-info"){
                /* info_text() prints the general info about the project to 
                the console.*/
                info_text(); 
            }else if(command == "-ex"){
                /* If the user ends the program, I print a 
                message to the console and return 0. */
                cout << "Thank you for using this project. Have an outstanding day" << endl;
                return 0; 
            }


        }
    }

}
/* As mentioned previously, true_or_false() generates all possible queries given 
a movie. This is done by generating a vector of 4 booleans recursively. If an index 
is false, I don't include it in a generated query. Otherwise, I include it. 
These queries are generated (they share the same class as countries) and then are 
inserted into the table using the function queryinsert(). */
void permute_filters(int pos, std::vector<int> filter, country& c, Hash& table){
	if(pos == 4){
		string name = c.getname(); 
        int year = c.getyear(); 
        string continent = c.getcontinent(); 
        string region = c.getregion(); 

        if(filter[0] == 0)
            name = ""; 
        if(filter[1] == 0)
            year = 0; 
        if(filter[2] == 0)
            continent = ""; 
        if(filter[3] == 0)
            region = ""; 
        
        country query(name, year, continent, region);
        table.queryinsert(query); 
        return; 
	}
    /* This generates 2 new vectors. One with a true
    value for an index and one with a false. 
    These are passed in again via recursive calls
    through the bottom 2 lines. */
	filter.push_back(0);
	std::vector<int> filter_new = filter;
	filter_new.back() = 1;
	permute_filters(pos+1, filter_new, c, table);
	permute_filters(pos+1, filter, c, table);
}

// this is the help text for a user. 
void help_text(){
    cout << "Using the command -c, you can search this database for a specific entry."; 
    cout << "The database allows you to specify by 4 criteria:" << endl;
    cout << "- Country name" << endl; 
    cout << "- data year" << endl; 
    cout << "- continent" << endl; 
    cout << "-region of continent" << endl << endl; 

    cout << "Here is a list of the different continents available with the regions under them: " << endl << endl; 
    cout << "Africa" << endl; 
    cout << "-Northern Africa" << endl; 
    cout << "-Middle Africa" << endl; 
    cout << "-Western Africa" << endl;
    cout << "-Southern Africa" << endl;
    cout << "-Eastern Africa" << endl << endl;

    cout << "Americas" << endl;
    cout << "-Caribbean" << endl;
    cout << "-South America" << endl; 
    cout << "-Central America" << endl;
    cout << "-Northern America" << endl << endl;

    cout << "Asia" << endl; 
    cout << "-Western Asia" << endl;
    cout << "-Southern Asia" << endl;
    cout << "-South-Eastern Asia" << endl;
    cout << "-Eastern Asia" << endl;
    cout << "-Central Asia" << endl << endl;


    cout << "Europe" << endl; 
    cout << "-Northern Europe" << endl;
    cout << "-Southern Europe" << endl;
    cout << "-Western Europe" << endl; 
    cout << "-Eastern Europe" << endl << endl; 

    cout << "Oceania" << endl;
    cout << "-Australia and New Zealand" << endl;
    cout << "-Melanesia" << endl;
    cout << "-Polynesia" << endl; 
    cout << "-Micronesia" << endl << endl << endl;



}
// this contains info about the program to the user. 
void info_text(){
    cout << "The gapminder parsing project was made by Ajeet Parmar to store the information in" << endl; 
    cout << "A C++ data structure. This was done using a hash table due to its quick access time " << endl; 
    cout << "This project is open-source and forwards ths mission of Gapminder: to demonstrate that" << endl; 
    cout << "the so called \"third world\" dogma is essentially far from the truth in today\'s world" << endl << endl;
    cout << "Mr. Parmar also embarked on this project to demonstrate the importance of a world view;" << endl; 
    cout << "he believed that many people do not appreciate the resurgence of developing countries " << endl; 
    cout << "and that they are often characterized my negative stereotypes such as being places of famine," << endl;
    cout << "war, and corruption despite their recent economic success." << endl;



    cout << "Technical notes: " << endl;
    cout << "The years available vary by 10\'s, ranging from 1960 to 2010" << endl << endl; 

    cout << "Certain overseas territories are not included with their host country. For example: " << endl; 
    cout << "Puerto Rico is a separate entry from the USA and French Pacific territories are not included with France" << endl<< endl;
    cout << "Information is stored via current borders. For example, the ex-Soviet countries are marked off " << endl; 
    cout << "by their current borders. " << endl << endl;
    cout << "Note: there are some parts of information which aren't available; these are marked off by \"-1\"." << endl << endl; 
    cout << "Certain countries and territories are not included as a part of the gapminder project."; 
    cout << "This includes, but is not limited to: " << endl; 
    cout << "The Democratic Republic of Korea (DPRK) " << endl; 
    cout << "Myanmar (Burma)" << endl; 
    cout << "Taiwan" << endl; 
    cout << "Kosovo" << endl; 
    cout << "South Ossetia" << endl; 
    cout << "Abkhazia" << endl;
    cout << "Northern Cyprus" << endl;
    cout << "Transnistria" << endl; 
    cout << "These omissions are not meant to be political. These are simply due to a lack of data." << endl; 

}