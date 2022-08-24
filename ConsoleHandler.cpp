#include <stdio.h>
#include <io.h>
#include <string.h>
#include "ConsoleHandler.h"

ConsoleLine Parse_Console(int argc, const char* argv[]) {
	ConsoleLine res;

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
					res.test_file_name = (char*)argv[i];
				}
				break;
			default:
				break;
			}
		}
	}

	return res;
}
