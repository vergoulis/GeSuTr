/* 
 * This is just a toy example to showcase the use of GeSuTr library. 
 *
 * Copyright (C) 2019 Thanasis Vergoulis
 *
 * This file is part of GeSuTr. 
 *
 * GeSuTr is a free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GeSuTr is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Contact email: vergoulis@athenarc.gr
 */
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "ST.h"
using namespace std;


int main(int argc, char* argv[])
{
	string* strs = new string[2];
	strs[0] = "banana$";
	strs[1] = "moana$";

	ST* my_tree;
	my_tree = new ST(strs,2);

	return 0;
}