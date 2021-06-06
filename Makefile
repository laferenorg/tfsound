# MIT License

# Copyright (c) 2021 laferenorg

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Settings
CCOPILER       = g++
CVERSION       = $(shell $(CCOPILER) --version | grep ^$(CCOPILER) | sed 's/^.* //g')

# Flags
COPTIMIZE      = -O2 -g -Ofast -Os -Og
CFLAGS         = -Wall -fPIC -fno-inline -finline-functions \
				 -lSDL2
CINCLUDE       = -I . -D_REENTRANT

# Source
CSOURCES_CPP   := $(shell find $(SOURCEDIR) -name '*.cpp')
CSOURCES_C     := $(shell find $(SOURCEDIR) -name '*.c')

# Output
COUTPUT_SRC    = obj
COUTPUT_BIN    = bin
COUTPUT_BUILD  = build
CFINISH_OUTPUT = tfsound

ifeq "$(CVERSION)" "4.4.3"
    CFLAGS += -Wtype-limits
endif

# Main
all: check_obj compile compile_binary finish

check_obj:
	@if [ ! -d $(COUTPUT_BUILD) ]; then \
		mkdir $(COUTPUT_BUILD); \
	fi
	@if [ ! -d $(COUTPUT_BUILD)/$(COUTPUT_SRC) ]; then \
		mkdir $(COUTPUT_BUILD)/$(COUTPUT_SRC); \
	fi
	@if [ ! -d $(COUTPUT_BUILD)/$(COUTPUT_BIN) ]; then \
		mkdir $(COUTPUT_BUILD)/$(COUTPUT_BIN); \
	fi

compile_binary:
	@$(CCOPILER) *.o $(CFLAGS) $(OPTIMIZE) -o $(COUTPUT_BUILD)/$(COUTPUT_BIN)/$(CFINISH_OUTPUT)

compile:
	@for _source_ in $(CSOURCES_CPP); do \
		printf "\033[0;32mCompile File: [\033[0;33m$$_source_\033[0m\033[0;32m]\033[0m \n"; \
		$(CCOPILER) -c $$_source_ $(CINCLUDE) $(OPTIMIZE); \
	done

	@for _source_ in $(CSOURCES_C); do \
		printf "\033[0;32mCompile File: [\033[0;33m$$_source_\033[0m\033[0;32m]\033[0m \n"; \
		$(CCOPILER) -c $$_source_ $(CINCLUDE) $(OPTIMIZE); \
	done

finish:
	@mv *.o $(COUTPUT_BUILD)/$(COUTPUT_SRC)
