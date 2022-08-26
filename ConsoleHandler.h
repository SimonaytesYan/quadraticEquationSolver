#ifndef CONSOLE_HANDLER
#define CONSOLE_HANDLER

const int HELP_MODE = 2;
const int UNIT_TEST_MODE = 1;
const int INTERACTION_MODE = 0;
const int TOTAL_NUMBER_OF_COMMAND = 4;

//!-------------------------------------------------
//! Structure to store information about launch conditions from the console
//! 
//! ------------------------------------------------
struct LaunchAttributes
{
	int mode = 0;								//!<Program operating mode
	const char* test_file_name = nullptr;		//!<File path from which unit tests will be read
	bool test_from_custom_file = false;			//!<True if should take unit tests from custom file and false otherwise
};

void Set_Testing_From_Custom_File(LaunchAttributes* LC, int argc, const char* argv[], int index);

struct CmdComand 
{
	const char* short_name;
	const char* long_name;
	const int program_mode;
	void (*calling_function)(LaunchAttributes* LC, int argc, const char* argv[], int index);
	const char* description;

};

void Print_All_Cmd_Flags();

LaunchAttributes Parse_Console(int argc, const char* argv[]);

#endif //CONSOLE_HANDLER