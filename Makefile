  
TARGET = genericht
STD_LIBS = -lm
CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Wformat -Ofast -ggdb3
CFLAGS_MAC = -std=c11 -pedantic -Wall -Wextra -Wformat -Ofast -ggdb3 -mmacosx-version-min=10.0
LFLAGS = -pedantic -Wall -Wextra 
CFLAGS_STRICT = -std=c11 -Wall -pedantic -ggdb3 -Ofast -ggdb3 -mmacosx-version-min=10.0 \
-pedantic-errors -Wextra -Waggregate-return -Wcast-align \
-Wcast-qual -Wconversion \
-Wdisabled-optimization \
-Werror -Wfloat-equal -Wformat=2 \
-Wformat-nonliteral -Wformat-security  \
-Wformat-y2k \
-Wimplicit  -Wimport  -Winit-self  -Winline \
-Winvalid-pch   \
-Wlong-long \
-Wmissing-field-initializers -Wmissing-format-attribute   \
-Wmissing-include-dirs -Wmissing-noreturn \
-Wpacked  -Wpadded -Wpointer-arith \
-Wredundant-decls \
-Wshadow -Wstack-protector \
-Wstrict-aliasing=2 -Wswitch-default \
-Wswitch-enum \
-Wunreachable-code -Wunused \
-Wunused-parameter \
-Wvariadic-macros \
-Wwrite-strings

.PHONY: clean all default $(TARGET)

default: $(TARGET)
all: default

BASE_FILES = $(wildcard *.c)
SRC_FILES = $(wildcard src/*.c)

SRC_H_FILES = $(wildcard inc/*.h)


OBJECTS = $(patsubst %.c, %.o, $(BASE_FILES) $(SRC_FILES))
HEADERS = $(BASE_H_FILES) $(SRC_H_FILES)

# Compile
%.o: %.c $(HEADERS)
	@echo Compiling: $< ...
	$(CC) $(CFLAGS_MAC) -c $< -o $@

#.PRECIOUS: $(TARGET) $(OBJECTS)

#Link
$(TARGET): $(OBJECTS)
	@echo Linking files: $(OBJECTS) ...
	$(CC) $(OBJECTS) $(STD_LIBS) -o $@
	@echo Deleting .o files ...
	-rm -f $(OBJECTS)
	@echo Done

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)