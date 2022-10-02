#include <stdio.h>
#include <string.h>
#include "editor.h"

// Generic validity checker
int validity(char type, const void *check, int pos, int end){
    switch (type) {
        case 'i': // index out of bounds checker
            if (end - pos <= 0)
                return -1;
            break;
        case 'n': // null pointer checker
            if (check == NULL)
                return -1;
            break;
        case 's': // size checker
            if (sizeof(check) == 0)
                return -1;
            break;
    }
    return 0; // if check is passed
}


// Task 1 Function 
int editor_insert_char(char editing_buffer[], int editing_buflen, 
    char to_insert, int pos)
{
     
    if (validity('i', editing_buffer, pos, editing_buflen) == -1)
        return 0;
    if (validity('n', editing_buffer, pos, editing_buflen) == -1)
        return 0;
    
    /* Creating a new buffer containing all the chars after the
     * pos
     */
    char buffer[editing_buflen - ( pos + 1 )]; 
    for (int i = pos; i < editing_buflen - 1; i++)
        buffer[(i - pos)] = editing_buffer[i];
    
    /* Inserting char */
    editing_buffer[pos] = to_insert;
    
    /* Readding the chars from the buffer. Excess char is ignore */
    for (int i = 0; i < sizeof(buffer); i++) 
        editing_buffer[(pos + 1 + i )] = buffer[i];
    
    
    if (editing_buffer[pos] != to_insert) 
        return 0;
    
    return 1;
}


// Task 2 Function
int editor_delete_char(char editing_buffer[], int editing_buflen, 
    char to_delete, int offset)
{
    if (validity('i', editing_buffer, offset, editing_buflen) == -1)
        return 0;
    if (validity('n', editing_buffer, offset, editing_buflen) == -1)
        return 0;
    if (validity('s', editing_buffer, offset, editing_buflen) == -1)
        return 0;
    
    int pos = -1; // var to store pos of to_delete
    
    /* Searches for to_delete then saves eveything after it in
     * buffer
     */
    char buffer[editing_buflen - (offset + 1)];
    for (int i = offset; i < editing_buflen; i++) {
        if (editing_buffer[i] == to_delete) {
            pos = i;
            for (int j = pos+1; j < editing_buflen; j++) {
                buffer[j - (pos+1)] = editing_buffer[j];
            }
            break;
        }
    }
    
    /* Check if to_delete found */
    if (pos == -1)
        return 0;
    
    /* Overwriting char array */
    for (int i = 0; i < sizeof(buffer); i++)
        editing_buffer[i + pos] = buffer[i];
    
    /* Adding replacement null char at the end*/
    editing_buffer[editing_buflen - 1] = '\0';
    
    //if (editing_buffer[pos] == to_delete)
    //    return 0;
    
    return 1;
}


// Task 3 Function
int editor_replace_str(char editing_buffer[], int editing_buflen, 
    const char *str, const char *replacement, int offset)
{
    if (validity('i', editing_buffer, offset, editing_buflen) == -1)
        return -1;
    else if (validity('s', &str, offset, editing_buflen == -1)) 
		return -1;
    
    /* Storing a pointer of the str to be replaced */
    char *edit_offset = &editing_buffer[offset];
    char *pos = strstr(edit_offset, str);
    if (pos == NULL) 
        return -1;
    
    /* Creating index vars to be used later*/
    int str_start = pos - editing_buffer;
    int str_l = strlen(str);
    int replace_l = strlen(replacement);
    //printf("Index: %d\n", str_start);
    //printf("Length: %d\n", str_l);
    //printf("R Length: %d\n", replace_l);
    
    /* Creating copy of chars after str */
    int buffer_offset = str_start + str_l;
    char buffer[editing_buflen - buffer_offset];
    for (int i = buffer_offset; i < editing_buflen; i++) {
        buffer[i - buffer_offset] = editing_buffer[i];
    }
    //printf("%s\n", buffer);
    //printf("%d\n", sizeof(buffer));
    
    /* Creating pointer to store last char of replacement */
    char *return_val; 
    /* Replacing str using replacement. Once replacement is 
     * finished, contents from buffer overwrites the previous
     * contents. If buffer is finished before array ends, null
     * char is used as filler
     */
    for (int i = str_start; i < editing_buflen; i++){
        /* Replacing the chars until replacement ends */
		if ((i - str_start) < replace_l){
			editing_buffer[i] = replacement[i - str_start];
            if ((i - str_start) == replace_l - 1)
                return_val = &editing_buffer[i];
        }
        /* Filling in with the rest of the string */
		else if ((i - (str_start + replace_l)) < sizeof(buffer)){
			editing_buffer[i] = buffer[i - (str_start + replace_l)];
            //printf("%c\n", buffer[i - (str_start + replace_l)]);
        }
        else // filler when buffer runs out
            editing_buffer[i] = '\0';
	}
	
	/* Checks to see if replacement occurs. Returns pos if
     * it occured
     */
	if (*return_val == replacement[replace_l - 1])
        return return_val - editing_buffer;
    
    return -1;
}


// Task 4 function
void editor_view(int rows, int cols, char viewing_buffer[rows][cols], 
    const char editing_buffer[], int editing_buflen, int wrap)
{
    
}
