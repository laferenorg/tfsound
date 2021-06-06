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
#include <vector>

#include "../../header/deps/sound.hpp"
#include "../../header/deps/filehelp.hpp"
#include "../../header/deps/struct.hpp"
#include "../../include/binaryfile/binaryfile.hpp"
#include "../../header/play/play.hpp"

void __play__namespace__::__section__play__(int& argc, const char* argv[]) {
	std::binaryfile db = "data.tf";
	sound __sound__;
	int index = 1;

	std::cout << "=========| Section: " << index << " |=========" << std::endl;
	for(int i = 0; i < argc; i++) {
		db = argv[i];
		db.init();

		for(int j = 1; j < ((int)db.length() + 1); j += 3) {
			for(int k = 0; k < ((int)db.get_number<double>(j + 2)); k++) {
				std::cout << k + 1 << ". " << db.get_number<double>(j + 1);
				std::cout << " | " << db.get_number<double>(j) << std::endl;
				__sound__.tone(db.get_number<double>(j + 1), db.get_number<double>(j));
			}

			if(j >= ((int)db.length() - 2)) {
				std::cout << "=========| Section: END |=========" << std::endl;
			}
			else {
				index++;
				std::cout << "=========| Section: " << index << " |=========" << std::endl;
			}
		}
	}
}