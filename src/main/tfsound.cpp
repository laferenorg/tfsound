// MIT License

// Copyright (c) 2021 laferenorg

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>
#include <string>

#include "../../header/compile/compile.hpp"
#include "../../header/play/play.hpp"

int main(int argc, const char* argv[]) {
	// init
	const char* argv_copy[argc - 1];
	for(int i = 1; i < argc; i++) argv_copy[i - 2] = argv[i];
	int length_argv_copy = argc - 2;

	// check argc
	switch(argc) {
		case 1: {
			printf("Giving Parmeter (--play, --compile) <filepath>\n");
			/* End Of Program And Clean */
			{
				(void)argc;
				(void)argv;
			}
			return 0;
		}
		break;
		case 2: {
			printf("Giving Parmeter <filepath>\n");
			/* End Of Program And Clean */
			{
				(void)argc;
				(void)argv;
			}
			return 0;
		}
		break;
	}

	// Check
	std::string argv_cheking = argv[1];
	if(argv_cheking == "--play")
	{
		__play__namespace__::__section__play__(
			length_argv_copy, argv_copy);
	}
	else if(argv_cheking == "--compile")
	{
		__compile__name__space__::__section__compile__(
			length_argv_copy, argv_copy);
	}
	else
	{
		std::cout << "Undefined Parameter 1 : " << argv[1] << std::endl;
	}

	{
		(void)argc;
		(void)argv;
	}
	return 0;
}