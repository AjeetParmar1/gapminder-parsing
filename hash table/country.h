#ifndef country_h
#define country_h

#include <iostream> 
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>


using namespace std; 

class country{
    public: 
        /* This constructor handles queries and 
        passes in the name, year, continent, and region 
        of the query with other values set to -1. */
        country(string n, int y, string c, string r){
            name = n; 
            year = y; 
            continent = c; 
            region = r; 
            infant_mortality = -1; 
            life_expectancy = -1; 
            fertility = -1; 
            population = -1; 
            gdp = -1; 
        }
        /* In the hash table, some values are empty 
        country values. So I set a default constructor with 
        no arguments passed in to simulate this.*/
        country(){
            name = ""; 
            year = 0; 
            infant_mortality = -1; 
            life_expectancy = -1; 
            fertility = -1; 
            population = -1; 
            gdp = -1; 
            continent = ""; 
            region = ""; 
        }
        /* This is the construcctor used in the case where country information
        is passed in. I take the line and parse it into its different queries. 
        Then, I set it to the class values.*/
        country(string & line){
            /* Since R's character objects are loaded with parentheses 
            into gapminder.txt, I replace all parentheses with spaces. */
            for(uint x = 0; x < line.size(); ++x){
                if(line[x] == '\"')
                    line[x] = ' ';
            }
            // I remove spaces to make it easier for me to parse. 
            line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

            // I convert the line into a stringstream so I can parse it into a vector. 
            stringstream s; 
            s.str(line);
           string part; 
           vector<string> info;
           // I turn the line into a vector so I can extract values. 
           while(getline(s, part, ',')){
               info.push_back(part);
           }
            /* For the lines below, I take specific indexes of the info vector 
            to assigne them to their values. For numeric objects, I use 
            stoi() or stof() to convert them to their respective type. 
            If a number isn't specified, I put it as "-1" to indicate that it is unavailable.*/
           name = info[0]; 

           year = stoi(info[1]);

            if(info[2] == "NA")
                infant_mortality = -1.0;
            else
                infant_mortality = stof(info[2]);

            if(info[3] == "NA")
                life_expectancy = -1.0;
            else
                life_expectancy = stof(info[3]);

            if(info[4] == "NA")
                fertility = -1.0;
            else
                fertility = stof(info[4]);

            if(info[5] == "NA")
                population = -1;
            else
                population = stoi(info[5]);

            if(info[6] == "NA")
                gdp = -1;
            else
                gdp = stof(info[6]);

           continent = info[7]; 

           region = info[8];

           
        }
        // these functions allow me to output certain values of the object. 
        string getname(){ return name;}
        int getyear(){ return year;}
        float getif(){ return infant_mortality;}
        float getlf(){ return life_expectancy;}
        float getfertility(){ return fertility;}
        int getpopulation(){ return population;}
        float getgdp(){ return gdp;}
        string getcontinent(){ return continent;}
        string getregion(){ return region;}
        
        string get_hash(){
            string returner; 
            returner += name; 
            returner += to_string(year); 
            returner += continent; 
            returner += region; 
            return returner; 
        }

        /* If the result is a query, then this allows us to 
        see whether the argument would satisfy the query. 
        I use this especially if I am inserting a country 
        into the hash table. 
        */
        bool querylist(country& c){
        if(c.name == name|| name == "")
            if(c.year == year || year == 0)
                if(c.region == region || region == "")
                    if(c.continent == continent || continent == "")
                        return true; 
        return false; 
        }

    /* As according to good programming practice, all my member 
    variables are private so I do not unintentionally modify 
    them.*/
    private: 
        string name; 
        int year; 
        float infant_mortality; 
        float life_expectancy; 
        float fertility; 
        int population; 
        float gdp; 
                string continent; 
        string region; 
}; 

/* Overloading "==" allows me to check if 
queries match when I am printing queries.*/
bool operator==(country&a, country&b){
    if(a.getname() == b.getname())
        if(a.getyear() == b.getyear())
            if(a.getregion() == b.getregion())
                if(a.getcontinent() == b.getcontinent())
                    return true; 
    return false; 
}

#endif
