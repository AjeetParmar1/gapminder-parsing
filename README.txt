Project name: gapminder parsing. 

Author: Ajeet Parmar

Project components: 

Hash table for data: 
- main.cpp (handles parsing and taking user inputs)
- country.h (main file to handle holding data for each country)
- hash.h (main file to hold the hash table and its operations)

parsing the data: 
- gapminder.txt (holds the data for the information. If this isn't present, main.cpp 
  will generate an error message.)
- parse.R (in case gapminder.txt is deleted or unintentionally modified, running this
program will generate a new file.)


Research conclusions: 
   - GDP per capita has risen considerably in LEDCs from the 1960s to the 2010s. 

Websites and other sources used: 
- http://www.partow.net/programming/hashfunctions/
- https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
- Dslabs package in R (found using the Harvard online data science course on edx.org)