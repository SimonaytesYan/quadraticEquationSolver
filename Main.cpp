#define _CRT_SECURE_NO_WARNINGS
#include "SolveEq.h"
#include "ConsoleHandler.h"
#include "InAndOut.h"
#include "UnitTest.h"
#include <assert.h>
#include <windows.h>
#include <stdio.h>


/*!
* \file
* \brief 
* Main file from which the execution of the program begins with functions to testing
*/

/*! \mainpage Quadratic Equation Solver 
 *	by SYM 
 *  2022
 *
 * \section intro_sec Console flags
 * 
 * \subsection step1 -s
 * Use -s to run program in interaction mode
 * 
 * \subsection step2 -t
 * Use -t to run Unit tests
 * 
 * \subsection step3 -f
 * Use -f to specify a custom file from which the unit test will be read.
 * File path incroduced after -f flag
 */

int main(int argc, const char* argv[])
{
	//printf("\x1B[32m ERROR \033[0m\n");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);	//Wrapper printf
	Print_Program_Info();

	LaunchAttributes Launch_Attrib = Parse_Console(argc, argv);

	switch (Launch_Attrib.mode)
	{
	case INTERACTION_MODE:
	{
		double a = 0;
		double b = 0;
		double c = 0;

		Get_Coef(&a, &b, &c);

		Solutions* anses = Solve_Quadraric_Eqution(a, b, c);
		Output_Solutions(anses);
		Del_Solutions(anses);
		break;
	}
	case UNIT_TEST_MODE:
        Launch_Tests(Launch_Attrib);
	break;
	case HELP_MODE:
		Print_All_Cmd_Flags();
	break;
	default:
		printf("Wrong operation mode\n");
	}
}
