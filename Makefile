CPPFILES = main.cpp\
 ECTextViewImp.cpp\
 Editor.cpp\

HFILES = $(CPPFILES:.cpp=.h)

OFILES= $(CPPFILES:.cpp=.o)

CC = g++
LIBPATH =

CFLAGS = -O3 -std=c++11 -Wall -I.

all: TextEditor

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

ECTextEditor:$(OFILES)
	$(CC) -o TextEditor $(OFILES)

clean: 
	rm *.o
	rm TextEditor