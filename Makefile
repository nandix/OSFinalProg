CC = g++

#LIBS = -lpthread

FLAGS = -g -Wall

EXECS = dash

all: $(EXECS)

dash: Source/dash.cpp
	$(CC) $(FLAGS) -o $@ $? $(LIBS)

clean:
	$(RM) $(EXECS)

