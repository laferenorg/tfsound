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
#include <fstream>
#include <ios>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>

#include "../../include/binaryfile/binaryfile.hpp"
#include "../../header/compile/compile.hpp"
#include "../../header/deps/filehelp.hpp"
#include "../../header/deps/struct.hpp"

// settings variable
const std::string WHITESPACE = " \n\r\t\f\v";

void splitFunctionOne(std::string& fillFile, 
								   std::vector<std::string>& allCode,
								   std::string delimiter) {
	size_t pos = 0;
	std::string token;
	while ((pos = fillFile.find(delimiter)) != std::string::npos) {
	    token = fillFile.substr(0, pos);
	    allCode.push_back(token);
	    fillFile.erase(0, pos + delimiter.length());
	}
	allCode.push_back(fillFile);
}

void compile(std::string nameFile) {
	FILESHELP FSH_I(nameFile.c_str());

	std::string fillFile = FSH_I.getFile();
	std::vector<std::string> allCode;

	splitFunctionOne(fillFile, allCode, ",");

	for(int i = 0; i < allCode.size(); i+= 2)
	{
		char *cstr = new char[allCode[i].length() + 1];
		strcpy(cstr, allCode[i].c_str());
	}

	std::vector<compileSound> inCompileSound;
	
	double Temp_S_HZ;
	float Temp_D_DURATION;

	for(int i = 0; i < allCode.size(); i += 2)
	{
		if((Temp_D_DURATION == atof(allCode[i + 1].c_str())) &&
			(Temp_S_HZ == atof(allCode[i].c_str()))) {
			inCompileSound[((int)inCompileSound.size()) - 1].duplicate += 1;
		} else {
			compileSound cpls;
			cpls.S_HZ = atof(allCode[i].c_str());
			cpls.D_DURATION = atof(allCode[i + 1].c_str());

			Temp_S_HZ = atof(allCode[i].c_str());
			Temp_D_DURATION = atof(allCode[i + 1].c_str());

			inCompileSound.push_back(cpls);
		}
	}

	std::binaryfile db = ((std::string)nameFile + ".tf");
	for(int i = 0; i < inCompileSound.size(); i++)
	{
		db.adding_number<double>(inCompileSound[i].D_DURATION);
		db.adding_number<double>(inCompileSound[i].S_HZ);
		db.adding_number<double>(inCompileSound[i].duplicate);
	}
	db.save();
}

void __compile__name__space__::__section__compile__(int& argc, const char* argv[]) {
	for(int i = 0; i < argc; i++) compile(argv[i]);
}