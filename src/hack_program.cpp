#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "const_in_patch.h"
#include "hack_program.h"

static size_t            count_len_file       (FILE* file);
static FILE*             find_program_file    (const char* mode);
static errors_in_patch_t read_file_to_str     (char** ptr_str);
static errors_in_patch_t write_str_to_file    (char** ptr_str);

//--------------------------------------------------------------------------------------------------------

errors_in_patch_t hack_program ()
{
	errors_in_patch_t status = NOT_ERROR;

	char* str_with_file = NULL;

	status = read_file_to_str (&str_with_file);
	if (status) {return status;}

	size_t begin_program_in_com = 0x0100;

	size_t index = 0x0114 - begin_program_in_com;   //ip - begin_program_in_com

	str_with_file[index]     = (char) 0xea;
	str_with_file[index + 1] = (char) 0x32;
	str_with_file[index + 2] = (char) 0x01;
	str_with_file[index + 3] = (char) 0x88;
	str_with_file[index + 4] = (char) 0x52;    // jmp 5288:0132  (to give access)

	index = 0x013a - begin_program_in_com;        //ip - begin_program_in_com

	str_with_file[index]     = (char) 0xea;
	str_with_file[index + 1] = (char) 0x1b;
	str_with_file[index + 2] = (char) 0x01;
	str_with_file[index + 3] = (char) 0x88;
	str_with_file[index + 4] = (char) 0x52;   //jmp 5288:011b   (to return in main program)
	
	printf ("Hacking is complite\n\n");

	status = write_str_to_file (&str_with_file);
	if (status) {return status;}

	return status;
}

//-------------------------------------------------------------------------------------------------------------

static errors_in_patch_t read_file_to_str (char** ptr_str)
{
	FILE* file = find_program_file ("r");
	if (file == NULL) {return NOT_FIND_FILE_FOR_HACKING;}

	size_t len_file = count_len_file (file);

	*ptr_str = (char*) calloc (len_file + 1, sizeof (char));
	if (*ptr_str == NULL)
	{
		printf ("\n\nError in %s:%d\n"
		        "not memory for str\n\n", __FILE__, __LINE__);

		fclose (file);

		return NOT_MEMORY_FOR_STR;
	}

	fread (*ptr_str, sizeof (char), len_file, file);

	fclose (file);

	return NOT_ERROR;
}

static FILE* find_program_file (const char* mode)
{
	assert (mode);

	const char* name_file = "./CRACKME.COM";

	FILE* file = fopen (name_file, mode);																				
	if (file == NULL)																									
	{																													
		printf ("\n\nError in %s:%d\n"																					
				"'find_program_file' not find file, which have name: \"%s\"\n\n", __FILE__, __LINE__, name_file);																								
	}																													
																														
	return file;	
}																									

static size_t count_len_file (FILE* file)      
{ 
    assert (file);

    fseek (file, 0, SEEK_END);
    size_t count_memory = ftell (file);
    fseek (file, 0, SEEK_SET);

    return count_memory;
}

static errors_in_patch_t write_str_to_file (char** ptr_str)
{
	assert (ptr_str);

	FILE* file = find_program_file ("r+");
	if (file == NULL) {return NOT_FIND_FILE_FOR_HACKING;}

	size_t len_file = count_len_file (file);

	fwrite (*ptr_str, sizeof (char), len_file, file);

	fclose (file);
	free (*ptr_str);

	return NOT_ERROR;
}
