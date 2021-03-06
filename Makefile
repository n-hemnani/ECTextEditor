CPPFILES = main.cpp\
 ECTextViewImp.cpp\
 Editor.cpp\
 Command.cpp\
 Visible.cpp

HFILES = $(CPPFILES:.cpp=.h)

OFILES= $(CPPFILES:.cpp=.o)

CC = g++
LIBPATH =

CFLAGS = -O3 -std=c++11 -Wall -I.

all: ECTextEditor

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

ECTextEditor:$(OFILES)
	$(CC) -o ECTextEditor $(OFILES)

clean: 
	rm *.o
	rm ECTextEditor