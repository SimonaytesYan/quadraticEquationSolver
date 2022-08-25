#include <stdio.h>
#include <io.h>
#include <string.h>
#include <assert.h>
#include <windows.h>
#include "InAndOut.h"
#include "ConsoleHandler.h"
/*!
* \file
* \brief
* File containing the definition of functions for parsing arguments from the console
*/

const CmdComand AllComands[] = {{"-h", "--help",		HELP_MODE,			NULL,							\
"The program will take the coefficients of the quadratic equation from cmd and print its roots" },
								{"-i", "--interection",	INTERACTION_MODE,	NULL,							\
"Enter path to file from which unit tests will be taken (work only with -t flag)" },
								{"-t", "--test",		UNIT_TEST_MODE,		NULL,							\
"The program will run tests from custom file if -f argument was used and from default file othervise"},
								{"-f", "--file",		0,					Set_Testing_From_Custom_File,	\
"The program will print all console flags with their description"}};

//!-------------------------------------------------
//! Function to parse arguments from console
//! \param [in] argc Number of arguments
//! \param [in] argv Arguments (array of strings)
//! 
//! ------------------------------------------------
LaunchAttributes Parse_Console(int argc, const char* argv[]) {

	LaunchAttributes res = {};

	for(int i = 0; i < argc; i++) 
	{
		bool coincidence = false;
		for (int j = 0; j < TOTAL_NUMBER_OF_COMMAND; j++) 
		{
			if (strcmp(argv[i], AllComands[j].short_name) == 0 || strcmp(argv[i], AllComands[j].long_name) == 0) {
				coincidence = true;
				if (AllComands[j].calling_function != NULL) {
					AllComands[j].calling_function(&res, argc, argv, i);
				}
				else {
					res.mode = AllComands[j].program_mode;
				}
				break;
			}
		}
		assert(coincidence && "Some comand flag not recognized");
	}

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	return res;
}

void Print_All_Cmd_Flags() 
{
	for (int i = 0; i < TOTAL_NUMBER_OF_COMMAND; i++) {
		printf("%s or %s\n", AllComands[i].short_name, AllComands[i].long_name);
		printf("%s\n", AllComands[i].description);
	}

}

void Set_Testing_From_Custom_File(LaunchAttributes* Launch_attrib, int argc, const char* argv[], int index)
{
	Launch_attrib->test_from_custom_file = true;
	if (index < argc - 1) {
		Launch_attrib->test_file_name = argv[index + 1];
	}
	
}