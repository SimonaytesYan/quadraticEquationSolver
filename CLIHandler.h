#ifndef CONSOLE_HANDLER
#define CONSOLE_HANDLER


const int TOTAL_NUMBER_OF_COMMAND = 4;

enum PROGRAM_EXECUTION_MODE {
	HELP_MODE = 2,
	UNIT_TEST_MODE = 1,
	INTERACTION_MODE = 0,
};

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

//!-------------------------------------------------
//! Structure to store information about different console line flags
//! 
//! ------------------------------------------------
struct CmdComand 
{
	const char* short_name;		//!<Short name of flag
	const char* long_name;		//!<Long name of flag
	const int program_mode;		//!<Mode of operation of the program what will be set when this flag is met
	void (*calling_function)(LaunchAttributes* LC, int argc, const char* argv[], int index);   //!<Function that will be called when this flag is met

	const char* description;   //!<Description of this flag
};

void Print_All_Cmd_Flags();

LaunchAttributes Parse_Console(int argc, const char* argv[]);

#endif //CONSOLE_HANDLER