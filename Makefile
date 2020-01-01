CXX = g++
DEBUG_LEVEL = -ggdb3
EXTRA_CCFLAGS = -Wall --std=c++11
LDLIBS = -lncurses
TERM_EMULATOR = kitty
TERM_RUN_FLAG = -e
MAIN = main
TERMINAL_HELPER_MAIN = terminal_helper_main
CORE_FILE = core.$(MAIN)
MAIN_BINARY = $(MAIN)
CC = $(CXX)
CXXFLAGS = $(DEBUG_LEVEL) $(EXTRA_CCFLAGS)
CCFLAGS = $(CXXFLAGS)
GDBFLAGS = 


all: main $(TERMINAL_HELPER_MAIN)

main: main.o ncurseswrapper.o displaybuffer.o logger.o

clean:
	rm -fv $(TERMINAL_HELPER_MAIN)
	rm -fv vgcore.* # Generated from valgrind
	rm -fv *.o # Object files
	rm -fv $(MAIN_BINARY)
	rm -fv $(CORE_FILE)

coredebug: $(MAIN) coredump
	gdb -c $(CORE_FILE) $(GDBFLAGS) $(MAIN) 
coredump: $(MAIN)
	coredumpctl -o $(CORE_FILE) dump $(MAIN)

run: $(MAIN) $(TERMINAL_HELPER_MAIN)
	# Runs terminal helper program to disable mouse mode if our program exits
	# with nonzero value (e.g. because of segfault)
	# I did this to help with testing without having
	# to constantly call 'reset' and lose terminal buffer, etc
	# I'm sure there was an easier way, but this is what I thought of off the top of my head.
	./$(MAIN) || ./terminal_helper_main mouse-disable

# For testing output without terminal helper disabling mouse output
# Useful if you're not sure if program cleans up after itself properly
run-unclean: $(MAIN)
	./$(MAIN)

guirun: $(MAIN)
	$(TERM_EMULATOR) $(TERM_RUN_FLAG) ./$(MAIN_BINARY)

debug: $(MAIN)
	gdb ./$(MAIN_BINARY) $(GDBFLAGS)

memcheck: $(MAIN)
	valgrind --leak-check=full -v ./$(MAIN_BINARY)
