#ifndef hash_h
#define hash_h

#include <iostream> 
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
#include "country.h"
using namespace std; 

uint hash_maker(country & c);

class Hash{
    public:
        /* The hash table is initialized with a 
        table size passed in. This creates the 
        empty pairs of country and a country list
        where I can insert values later.*/
        Hash(int table_size){
                /* This creates empty values for the 
                queries to be inserted later.*/
                for(int x = 0; x < table_size; ++x){
                    pair<country, list<country> > dummy_pair; 
                    hash_table.push_back(dummy_pair);
                }
                // initial values for private variables. 
                queriesfilled = 0;
                size = table_size; 
            }
        
        /* In the event that the table's values have been filled, 
        I resize the table using this function.*/
        void resize_table(int new_size){
                // new table temporarily serves as the resized table. 
                vector <pair<country, list<country> > > new_table; 
                //empty values are initialized. 
                for(int x = 0; x < new_size; ++x){
                    pair<country, list<country> > dummy_pair; 
                    country c;
                    dummy_pair.first = c;
                    new_table.push_back(dummy_pair);
                }
                // the size variable is updated. 
                this->size = new_size;
                // The hash table is assigned to a temporary variable to assign values later. 
                vector <pair<country, list<country> > > dummy_variable = hash_table;
                //the new table becomes the actual hash table. 
                hash_table = new_table;
                //queriesfilled is reinitialized to 0. 
                queriesfilled = 0; 
                // values are reinserted. 
                for(uint x = 0; x < dummy_variable.size(); ++x){
                        insert(dummy_variable[x].first, dummy_variable[x].second);
                        queriesfilled++; 
                }

            }

        /* Once a user specifies a query, I use printquery to 
        print the query's contents to the console.*/
        void printquery(country& query){
                // I find the index of the query
                int index = hash_maker(query) % hash_table.size(); 
                /* If the index doesn't match, I employ linear probing
                to search for the query. Since this is relatively near the 
                previous index and the indexes searched is small relative to the
                number of total indexes, this is ideally still O(1).*/
                if(!(hash_table[index].first == query)){
                    for(uint i = 0; i < hash_table.size(); ++i){
                        uint x = (i +index) % hash_table.size();
                        if(hash_table[x].first == query){
                            // if I find it, I break out of the while loop. 
                            if(hash_table[x].first.getname() == query.getname()){
                                index = x; 
                                break;
                            }
                        }
                    }
                }
                /* if the list is empty, it prints that there
                are no results.*/
                if(hash_table[index].second.size() == 0){
                    cout << "No results for query." << endl;
                }else{
                    /* otherwise, it prints out the
                    elements of the list in the desired format. */
                    cout << "Printing " << hash_table[index].second.size();
                    cout <<" result(s):" << endl;
                    list <country>::iterator i;
                    for(i = hash_table[index].second.begin(); i != hash_table[index].second.end(); ++i){

                        cout << "Country name: " << (*i).getname() << endl; 
                        cout << "Data's year: " << (*i).getyear() << endl; 
                        cout << "Infant mortality: " << (*i).getif() << endl; 
                        cout << "Life expectancy: " << (*i).getlf() << endl; 
                        cout << "Fertility: " << (*i).getfertility() << endl; 
                        cout << "Population: " << (*i).getpopulation() << endl; 
                        cout << "Gross Domestic Product (GDP): " << (*i).getgdp() << endl; 
                        cout << "Continent: " << (*i).getcontinent() << endl; 
                        cout << "Region of continent: " << (*i).getregion() << endl;  
                        cout << endl << endl;
                        

                    }

                }
                
            }
            /*  This insert function handles the special case if I 
            need to insert a query and its contents. 
            */
            void insert(country& query,list<country>& to_insert){
                // I check if I need to resize the table first. 
                float occupancy_compare = (float)queriesfilled/size; 
                if(occupancy_compare > occupancy){
                    resize_table(size*2);
                }

                // I check for an available spot and insert. 
                int index = hash_maker(query) % hash_table.size();
                    for(uint i = 0; i < hash_table.size(); ++i){
                        uint x = (i + index) % hash_table.size();
                        // if the query is already inserted, I return. 
                        if(hash_table[x].first == query)
                            return;
                        else if(hash_table[x].first.getname() == ""){
                            hash_table[x].first = query;
                            hash_table[x].second.clear();
                            list<country>::iterator i; 
                            hash_table[x].second = to_insert; 
                            queriesfilled++; 
                            return;
                        }
                    }
                
            }

            void queryinsert(country query){
                /*If the occupancy is exceeded, I double the 
                size of the hash table.*/
                float occupancy_compare = (float)queriesfilled/size; 
                if(occupancy_compare > occupancy){
                    resize_table(size*2);
                }

                // finds the index to insert. 
                int index = hash_maker(query) % hash_table.size();
                // if the space is unoccupied, it is inserted
                if(hash_table[index].first.getname() == ""){
                    hash_table[index].first = query; 
                    queriesfilled++; 
                    return;
                }
                    for(uint i = 0; i < hash_table.size(); ++i){
                        uint x = (i + index) % hash_table.size();
                        /*if the query's index is already there, 
                        I break the function. */
                        if(hash_table[x].first == query)
                            return;
                        /* If a space is available, I insert at that 
                        point and return.*/
                        if(hash_table[x].first.getname() == ""){
                            hash_table[x].first = query;
                            queriesfilled++; 
                            return;
                        }
                    }
            }

            /* This function inserts a country in all 
            queries which it returns true on 
            querylist(). This is O(n) */
            void countryinsert(country& c){
                int s = hash_table.size(); 
                for(int x = 0; x < s; x++){
                    
                        if(hash_table[x].first.querylist(c)){
                            hash_table[x].second.push_back(c);
                            
                        }
                }
                
            }

    private: 
    float queriesfilled; 
        /* If over 50% of the indexes are filled,
        I resize the table.*/
        float occupancy = 0.5; 
        int size = hash_table.size(); 
        vector <pair<country, list<country> > > hash_table; 
};

/* this finds the hash to insert at for a query. 
The implementation comes from
http://www.partow.net/programming/hashfunctions/ */
uint hash_maker(country& c){
    string key; 
    key = c.get_hash();  
    unsigned int Hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++)
    Hash ^= ((Hash << 5) + key[i] + (Hash >> 2));
    return Hash;
}
#endif