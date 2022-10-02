#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dbms.h"

const char MAX_CHAR_L[4] = {6, 20, 20, 4}; // added for easier adjustment

/* Auxiliary method that takes the input (the album fields) and then 
 * reformats it as required. Also takes the type of field and the size
 * of the dest array
 */
void row_format(char *dest, char *input, int type, int size_d){
    /* Checks if the length of the string exceeds maximum number of chars
     * for the field type and adjusts the offset if necessary
     */
    int offset;
    
    if (MAX_CHAR_L[type] <= strlen(input))
        offset = 0;
    else 
        offset = MAX_CHAR_L[type] - strlen(input);
    
    /* Adding the input string via for loop with offset specified
     * for strings lower than the max. Also adds the colon and need
     * null terminator at the end
     */
    for (int i = offset; i < size_d; i++){
        if (i < size_d - 2)
            *(dest + i) = *(input + (i - offset));
        /* Adds the semicolon as long as the current field being modified
         * isn't the last string
         */
        else if (i < size_d - 1 && type != 3) 
            *(dest + i) = ':';
        else
            *(dest + i) = '\0'; // null char needs to be added to remove errors
    }
    
}


/* Function used to display the value of a row in a table. Inputs are a table struct
 * pointer and an unsigned int for the row that needs to be displayed
 */
int db_show_row(const struct db_table *db, unsigned int row){
    /* Checking the validity of inputs*/
    if (row >= db->rows_used) 
        return 0;
    else if (db->rows_total == 0 || db->rows_used == 0)
        return 0;
    else if (db->rows_used > db->rows_total)
        return 0;
    
    /* Storing album struct for easier use and creating char arrays for storing
     * strings. Sizes are offset to account for colon and null chars
     */
    struct album *alb = &(db->table[row]);    
    char id[MAX_CHAR_L[0] + 2];
    char title[MAX_CHAR_L[1] + 2];
    char artist[MAX_CHAR_L[2] + 2];
    char year[MAX_CHAR_L[3] + 2];
    char id_cpy[MAX_CHAR_L[0] + 2];  // extra arrays created to convert ints
    char year_cpy[MAX_CHAR_L[3] + 2]; // created solely for aux function
    
    /* Setting defaults chars to spaces */
    memset(id, ' ', sizeof(id));
    memset(title, ' ', sizeof(title));
    memset(artist, ' ', sizeof(artist));
    memset(year, ' ', sizeof(year));
    
    /* Converting ints to strings */
    itoa(alb->id, id_cpy, 10);
    itoa(alb->year, year_cpy, 10);
    
    /* Calling aux function to reformat strings */
    row_format(id, id_cpy, 0, sizeof(id));
    row_format(artist, alb->artist, 1, sizeof(artist));
    row_format(title, alb->title, 2, sizeof(title));
    row_format(year, year_cpy, 3, sizeof(year));
    
    /* Creating output string then printing out */
    char output[MAX_CHAR_L[0] + MAX_CHAR_L[1] + MAX_CHAR_L[2] + MAX_CHAR_L[3]];
    
    /* Copying first string then concatenating the rest */
    strcpy(output, id);
    strcat(output, title);
    strcat(output, artist);
    strcat(output, year);
    
    printf("%s\n", output);
    
    return 1; // success num
}


/* Function for adding another album to an existing table. Inputs are a table struct
 * pointer and a pointer to the album that needs to be added
 */
int db_add_row(struct db_table *db, struct album *a){
    /* Checking the validity */
    if (db == NULL)
        return 0;
    else if (a == NULL)
        return 0;
    else if (db->rows_used > db->rows_total)
        return 0;
    
    /* Allocating memory for new row and then checking if allocated */
    struct album *new_row;
    new_row = (struct album *)malloc(sizeof(struct album));
    
    if (new_row == NULL)
        return 0;
    
    /* Copying the the contents of the struct a into new album */
    memcpy(&(new_row->id), &(a->id), MAX_CHAR_L[0]);
    memcpy(&(new_row->title), &(a->title), MAX_CHAR_L[1]);
    memcpy(&(new_row->artist), &(a->artist), MAX_CHAR_L[2]);
    memcpy(&(new_row->year), &(a->year), MAX_CHAR_L[3]);
    
    /* If there are unused rows, use pointer arithmetic to find the next empty row.
     * If the given table is empty or full, reallocate 5 more row slots and add the
     * new row using pointer arithmetic
     */
    if (db->rows_used < db->rows_total){
        struct album *row = db->table; // creating new pointer to do arithmetic
        
        row = row + db->rows_used; // arithmetic
        *row = *new_row; // copying new_row contents
        db->rows_used++; // incrementing rows_used
    }
    else {
        db->table = (struct album *)realloc(db->table, (db->rows_total + 5)*sizeof(struct album));
        
        if (db->table == NULL)
            return 0;
        
        
        struct album *row = db->table; // creating new pointer to do arithmetic
        
        row = row + db->rows_used; // arithmetic
        *row = *new_row; // copying new_row contents
        db->rows_used++; // incrementing row counts
        db->rows_total = db->rows_total + 5;
    }
    
    free(new_row); // freeing memory after being copied into table
    
    return 1;
}


/* Function for removing a row with a given id. Inputs are a table struct pointer
 * and the id of the row that needs to be removed. If after removal the number of 
 * unused rows reaches 5, the number of rows in the table is reduced by 5 and 
 * rows_used and rows_total is updated accordingly
 */
int db_remove_row(struct db_table *db, unsigned long id){
    /* Checking for validity */
    if (db == NULL)
        return 0;
    else if (db->rows_used > db->rows_total)
        return 0;
    else if (db->rows_total == 0 || db->rows_used == 0)
        return 0;
    
    
    // finding the row number of the given id and storing it for later use
    int row = -1; // setting intial to -1 to indicate if unchanged
    
    for (int i = 0; i < db->rows_used; i++){
        if (db->table[i].id == id){
            row = i;
            break;
        }
    }
    
    // if id is not found, return 0
    if (row == -1)
        return 0;
    
    /* Creating album the size of all albums after the one to be removed, copying them
     * and then overwriting the row to be removed
     */
    struct album db_copy[db->rows_used - row];
    
    for (int i = row + 1; i < db->rows_used; i++)
        db_copy[i - (row + 1)] = db->table[i];
    
    
    for (int i = row; i < db->rows_used - 1; i++)
        db->table[i] = db_copy[i - row];
    
    
    struct album *ptr; // creating an album pointer for realloc
    
    db->rows_used--; // decreasing db->rows_used for checking the number of unused rows following
    
    /* Checking if the number of unused rows after a removal would be greater or equal to 5. 
     * If so, then use realloc to remove 5 unused rows. If not, then realloc with db->rows_used
     * as has already been decreased by 1
     */
    if (db->rows_total - db->rows_used  >= 5){
        ptr = (struct album *)realloc(db->table, (db->rows_total - 5)*(sizeof(struct album)));
        db->rows_total = db->rows_total - 5;
    }
    else {
        ptr = (struct album *)realloc(db->table, (db->rows_used)*(sizeof(struct album)));
    }
    
    
    if (ptr = NULL) // checking if realloc worked
        return 0;
    
    
    return 1;
}
