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

#include <string>

#include "../../header/deps/filehelp.hpp"

namespace _TEMP_ {
	// make variable for file management
	std::fstream frmXFile;
};

// fill variable name file
FILESHELP::FILESHELP(const char* nameFile) :
	namefile(nameFile) {}

// function for openFile in this script
void S_openFile(std::fstream& frmXFile, std::string& nameFile) {
	frmXFile.open(nameFile, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
	if(!frmXFile.is_open()) {
		frmXFile.close();
		frmXFile.open(nameFile, std::ios::trunc | std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
	}
}

// function for close file in this script
void S_closeFile(std::fstream& frmXFile) {
	frmXFile.close();
}

// function for open file
void FILESHELP::F_openFile() {
	// openfile
	S_openFile(_TEMP_::frmXFile, namefile);
}

// function for close file
void FILESHELP::F_closeFile() {
	// close file
	S_closeFile(_TEMP_::frmXFile);
}

// return fstream variable in this function
std::fstream& FILESHELP::getVarFile() {
	return _TEMP_::frmXFile;
}

bool FILESHELP::itsExist() {
	_TEMP_::frmXFile.open(namefile, std::ios::in | std::ios::out | std::ios::binary);
	if(!_TEMP_::frmXFile.is_open()) {
		_TEMP_::frmXFile.close();
		return 0;
	}
	_TEMP_::frmXFile.close();
	return 1;
}

std::string FILESHELP::getFile() {
	std::fstream inputFile;
	std::string _BUFFER_;

	inputFile.open(namefile, std::ios::in);
	if(!inputFile.is_open())
	{
		return "";
	}

	int indexes = 0;
	while(!inputFile.eof())
	{
		std::string _TEMP_;
		getline(inputFile, _TEMP_);

		if(indexes == 0) {
			_BUFFER_ += _TEMP_;
			indexes += 1;
		} else {
			_BUFFER_ += " " + _TEMP_;
		}
	}
	inputFile.close();

	return _BUFFER_;
}