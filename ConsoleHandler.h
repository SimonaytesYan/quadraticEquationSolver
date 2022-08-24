
const int UNIT_TEST_MODE = 1;
const int INTERACTION_MODE = 0;

//!-------------------------------------------------
//! Structure to store information about launch conditions from the console
//! 
//! ------------------------------------------------
struct LaunchAttributes
{
	int mode = 0;					//!<Program operating mode
	const char* test_file_name = nullptr;	//!<File path from which unit tests will be read
	bool test_from_file = false;	//!<True if should take unit tests from custom file and false otherwise
};

LaunchAttributes Parse_Console(int argc, const char* argv[]);

