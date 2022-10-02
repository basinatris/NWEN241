/**
 * abstractdb.cpp
 * C++ source file that should contain implementation for member functions
 * - loadCSV()
 * - saveCSV()
 * 
 * You need to modify this file to implement the above-mentioned member functions
 * as specified in the hand-out (Tasks 4 and 5)
 */ 

#include "abstractdb.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

namespace nwen{
    /* Function for saving the given database pointer contents into the given CSV file 
     * name. Overwrites previous contents of the file when opened. Returns true if 
     * file write successful and false if:
     *  - .csv extension is not found
     *  - File open errors occured
     *  - File errors occured during writing. 
     * Uses pointer inheritance to call the subclass functions on the object that 
     * this function is called on
     */
    bool AbstractDbTable::saveCSV(string filename){
        if (filename.find(".csv") < 0) // checking correct file format
            return false;
        
        // opening and clearing previous contents
        ofstream fs_io(filename, ios::out | ios::trunc); 

        if (!fs_io.is_open()) // checking if filestream open
            return false;

        
        int num = this->rows();     // using inheritance to gain access to subclass functions
        
        for (int i = 0; i < num; i++){  // going through table row by row
            movie *row = this->get(i);  // getting movie struct out of row

            fs_io <<row->id <<"," <<row->title <<"," <<row->year <<"," <<row->director << "\n";
            
            if (!fs_io.good()){ // checking if any errors occured while writing to fs_io
                fs_io.close();  // close and return false if error occured
                
                return false;
            }
        }

        fs_io.close();  // close and return true after successful write

        return true;
    }

    
    /* Function for loading a given CSV file into the database this was called on. Returns
     * true if file successful and false if:
     *  - .csv extension not found
     *  - Filestream fails to open
     *  - .csv file is of the incorrect formatting 
     *  - File reading errors occur
     * Uses pointer inheritance to call the functions of whatever object this is called on.
     * Relies on the set id, title, year, director format to check for formatting issues, 
     * so parts are quite hard coded
     */
    bool AbstractDbTable::loadCSV(string filename){
        if (filename.find(".csv") < 0)  // checking for .csv file extension
            return false;
        
        
        ifstream fs_io(filename, ios::in); // opening for read only

        if (!fs_io.is_open())   // checking if opened
            return false;
        

        string line;    // variable for storing each .csv file line
        
        while(getline(fs_io, line)){    // reading .csv line by line
            if (!fs_io.good())  // check for file reading errors before processing
                return false;
            
            
            stringstream ss(line);      // declaring stringstream for separating line
            vector<string> process;     // using vector to store separated strings
            movie new_row;              // movie struct to add later

            string block;
            
            while(getline(ss, block, ','))     // separates the variables in each line
                process.push_back(block);
            

            if (process.size() != 4){   // checking if .csv matches format (4 variables only)
                fs_io.close();
                return false;
            }
            
            /* Try catch block for checking if the first and third variables (id and year) 
             * can be turned into ints. Uses stoi, which contains exceptions for such parts */
            try{
                int id = stoi(process[0]);
                int year = stoi(process[2]);
                
                /* If no errors occured, check if ints are negative; if not, then throw
                 * throw exception to trigger catch and return false */
                if (id < 0 || year < 0)
                    throw invalid_argument("");
                
                /* If successful, typecast to respective counterparts and save into new_row */
                new_row.id = (unsigned long) id;
                new_row.year = (unsigned short) year;
                
            }
            catch (invalid_argument &e){    // if stoi cannot convert, invalid_argument is thrown
                fs_io.close();
                
                return false;
            }
            
            // using strcpy and c_str to copy strings into new_row variables
            strcpy(new_row.title, process[1].c_str());
            strcpy(new_row.director, process[3].c_str());

            this->add(new_row); // calling add to add movie struct

            
        }
        
        
        fs_io.close();  // if everything is successful
        
        return true;
    }
}



