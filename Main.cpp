#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>	
#include <windows.h>
#include <stdio.h>

#include "SolveEq.h"
#include "ConsoleHandler.h"
#include "InAndOut.h"
#include "UnitTest.h"

/*!
* \file
* \brief 
* Main file from which the execution of the program begins with functions to testing
*/

/*! \mainpage Round Equation Solver 
 *	SYM 
 *  2022
 *
 */

int main(int argc, const char* argv[])
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
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

			Solutions* anses = Solve_Round_Eqution(a, b, c);
			Output_Solutions(anses);
 			Del_Solutions(anses);
			break;
		}

		case UNIT_TEST_MODE:
			Launch_Tests_For_Round_Equation_Solver(Launch_Attrib);
		break;

		case HELP_MODE:
			Print_All_Cmd_Flags();
		break;

		default:
			printf("Wrong operation mode\n");
	}
}
