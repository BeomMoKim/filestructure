CFLAGS= -Wall -g
OBJS = phonebook.o pbMain.o
all: pbTest
%.o: %.cpp
	g++ -c -o $@ $(CFLAGS) $<
pbTest: $(OBJS)
	g++ -o pbTest $(OBJS)
clean:
	rm pbTest $(OBJS)
