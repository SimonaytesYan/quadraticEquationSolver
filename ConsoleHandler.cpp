#include <stdio.h>
#include <io.h>
#include <string.h>
#include <windows.h>
#include "InAndOut.h"
#include "ConsoleHandler.h"
/*!
* \file
* \brief
* File containing the definition of functions for parsing arguments from the console
*/

//!-------------------------------------------------
//! Function to parse arguments from console
//! \param [in] argc Number of arguments
//! \param [in] argv Arguments (array of strings)
//! 
//! ------------------------------------------------
LaunchAttributes Parse_Console(int argc, const char* argv[]) {
	LaunchAttributes res; //unitinialized

#if 0
	struct Command commands [] = {{"-h", "--help", HELP_MODE}, {...}, ...};		//Mode и указатель на функцию
	foreach in commands:
		if (strcmp (argv [i], cur_command.short) || long ())
			mode = cur_command.mode;
#endif
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for(int i = 0; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (strlen(argv[i]) == 1)
				continue;
			switch (argv[i][1])
			{
			case 't':
				res.mode = UNIT_TEST_MODE;
				break;
			case 's':
				res.mode = INTERACTION_MODE;
				break;
			case 'f':
				res.test_from_custom_file = true;
				if (i < argc - 1) {
					res.test_file_name = argv[i + 1];
				}
				break;	//! -h
			default:
				SetConsoleTextAttribute(hConsole, YELLOW);
				printf("Param %s not found", argv[i]); //!!!! Bit' po golove
				SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);

			}
		}
	}

	return res;
}
