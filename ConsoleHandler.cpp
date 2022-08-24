/*!
* \file
* \brief
* File containing the definition of functions for parsing arguments from the console
*/
#include <stdio.h>
#include <io.h>
#include <string.h>
#include "ConsoleHandler.h"

//!-------------------------------------------------
//! Function to parse arguments from console
//! \param [in] argc Number of arguments
//! \param [in] argv Arguments (array of strings)
//! 
//! ------------------------------------------------
LaunchAttributes Parse_Console(int argc, const char* argv[]) {
	LaunchAttributes res;

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
				res.test_from_file = true;
				if (i < argc - 1) {
					res.test_file_name = argv[i + 1]; //!! unsafe cast
				}
				break;
			default:
				break;
			}
		}
	}

	return res;
}
