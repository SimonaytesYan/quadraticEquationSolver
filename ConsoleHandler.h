
const int UNIT_TEST_MODE = 1;
const int INTERACTION_MODE = 0;
struct ConsoleLine
{
	int mode = 0;
	char* test_file_name = NULL;
	bool test_from_file = false;
};

ConsoleLine Parse_Console(int argc, const char* argv[]);

