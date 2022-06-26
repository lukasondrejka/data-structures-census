#pragma once

#include "printable.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <windows.h>
#include <cstdlib>

#pragma execution_character_set( "utf-8" )

using std::cout;
using std::cin;
using std::endl;


inline void initCLI()
{
	SetConsoleOutputCP(65001);
}