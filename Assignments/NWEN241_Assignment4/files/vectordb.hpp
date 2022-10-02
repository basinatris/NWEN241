/**
 * vectordb.hpp
 * C++ header file that should contain declaration for
 * - VectorDbTable class
 * 
 * You need to modify this file to declare VectorDbTable class 
 * as specified in the hand-out (Task 2)
 */ 

#include "abstractdb.hpp"
#include <vector>

using namespace std;

namespace nwen{
    /* Subclass of AbstractDbTable that uses a vector table of struct movies to store 
     * the table data. Apart from inheriting virtual functions, has one unique function
     * for finding the row of a given id
     */
	class VectorDbTable: public AbstractDbTable {
			vector<movie> db_table;          // vector table   
			int ROW_NUM = 0;                 // var for storing the row number; Stores true array indexes
			int findRowId(unsigned long);    // private function for finding row of given id
			
		public:
			VectorDbTable();
			int rows() const;
            movie* get(int);
            bool add(movie);
            bool update(unsigned long, movie);
            bool remove(unsigned long);
            ~VectorDbTable();

	};
}
