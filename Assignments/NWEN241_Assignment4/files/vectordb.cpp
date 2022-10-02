/**
 * vectordb.cpp
 * C++ source file that should contain implementation for member functions
 * - rows()
 * - get()
 * - add()
 * - update()
 * - remove()
 * 
 * You need to modify this file to implement the above-mentioned member functions
 * as specified in the hand-out (Task 3)
 */ 

#include "vectordb.hpp"
#include <vector>


using namespace std;

namespace nwen{
	/* Constructor; defaults already set in hpp */
	VectorDbTable::VectorDbTable(){}

	
	/* Destructor */
	VectorDbTable::~VectorDbTable(){}

	
	/* Returns the ROW_NUM; very simple as number of rows are tracked */
	int VectorDbTable::rows() const{return ROW_NUM; }

	
	/* Private auxlliary function used to find the row of the given id in the
     * vector table; used in add, update, and removed. Returns row index if
     * found and -1 if not
	 */
	int VectorDbTable::findRowId(unsigned long id){
		for (int i = 0; i < ROW_NUM; i++){ 
			if (db_table[i].id == id){   // [] instead of at because no need for error checking
				return i;       // uses int iterator for loop to return row if found
			}
		}
		
		return -1; // default return val if id not found
	}


    /* Returns a pointer to a movie struct located at the requested row. Integer
     * input uses true array indexing so "actual" row is greater by 1. Returns 
     * NULL if row number less than zero or greater than ROW_NUM
     */
	movie* VectorDbTable::get (int row) {
		if (ROW_NUM < row || row < 0){    // checking validity
			return NULL;
		}

        return &db_table[row];  // [] instead of at because no need for error checking
	}
    
    
    /* Appends a copy of the given movie struct into the vector table. Returns true 
     * if row is added; returns false if id of the given row already present. 
     */
	bool VectorDbTable::add(struct movie new_row){
		if (ROW_NUM == 0){ // short cut statement block if table is empty
			db_table.push_back(new_row);
			ROW_NUM++;   // if successful, ROW_NUM is incremented
			
		}
		else {
			int check = findRowId(new_row.id);

			if (check != -1) // checking if id already present in table
				return false;

			/*for (struct movie row : db_table){ // Legacy code
				if (row.id == new_row.id){
					return false;
				}
			}*/
            
			
            db_table.push_back(new_row);
            ROW_NUM++;  
		}
		return true;
	}
    
    
    /* Updates movie at given id by removing it then emplacing the given movie 
     * into the same place. Returns true if row updated and false if there are 
     * no entries, or if the given id is not present within the table. Uses 
     * emplace to insert without overiding entry at the row after erasing
     */
	bool VectorDbTable::update(unsigned long id, struct movie new_movie){
		if (ROW_NUM == 0)     // checking table empty
			return false;
		
		
		int row = findRowId(id);  // auxlliary function called to find row of id

		if (row != -1){   // if id is found
			db_table.erase(db_table.begin() + row);      // erase old
			db_table.emplace(db_table.begin() + row, new_movie);   // emplaces new
            
			return true;
		}
		else {    // if id not found
			return false;
		}
		/* Legacy Code
		bool flag; 
		for (int i = 0; i < ROW_NUM; i++){
			if (db_table[i].id == id){
				flag = false;
				db_table.erase(db_table.begin() + i);
				db_table.emplace(db_table.begin() + i, new_movie);
				break;
			}
		}

		if (flag)
			return false;
		
		return true;
		*/
	}
    
    
    /* Removes table row of the given entry. Returns true if successful and 
     * false if not present in the vector table
     */
	bool VectorDbTable::remove(unsigned long id){
		int row = findRowId(id); // using auxlliary funciton to find row number

		if  (row != -1){  // if id is found
			db_table.erase(db_table.begin() + row);  // erasing
			ROW_NUM--;       // decrementing after erase

			return true;
		}
		else {    // if id not found
			return false;
		}
		/* Legacy code
		bool flag = true;
		for (int i = 0; i < ROW_NUM; i++){
			if (db_table[i].id == id){
				flag = false;

				db_table.erase(db_table.begin() + i);

				ROW_NUM--;
				
				break;
			}
		}
		if (flag)
			return false;
		return true;*/
	}
}

