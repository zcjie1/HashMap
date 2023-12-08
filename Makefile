# Version 4
CC = gcc
TARGET = main
CFLAGS = -c

SRCDIR = source
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(SRCDIR)/%.o,$(SRCS))

$(TARGET): $(OBJS) main.o
	$(CC) -o $@ $^

main.o: main.c 
	gcc -c main.c 

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) $(SRCDIR)/*.o main.o


# Version 1
# main: main.c HashFunction.c HashMap.c HashMapIterator.c
# 	gcc main.c HashFunction.c HashMap.c HashMapIterator.c -o main

# Version 2
# CXX = gcc
# TARGET = main
# OBJ = main.o HashFunction.o HashMap.o HashMapIterator.o
# CXXFLAGS = -c -Wall

# $(TARGET): $(OBJ)
# 	$(CXX) -o $(TARGET) $(OBJ)

# main.o: main.c
# 	$(CXX) -c main.c

# HashFunction.o: HashFunction.c
# 	$(CXX) -c HashFunction.c

# HashMap.o: HashMap.c
# 	$(CXX) -c HashMap.c

# HashMapIterator.o: HashMapIterator.c
# 	$(CXX) -c HashMapIterator.c


# Version 3
# CXX = gcc
# TARGET = main
# OBJ = main.o HashFunction.o HashMap.o HashMapIterator.o
# CXXFLAGS = -c

# $(TARGET): $(OBJ)
# 	$(CXX) -o $@ $^

# %.o: %.c
# 	$(CXX) $(CXXFLAGS) $< -o $@

# .PHONY: clean
# clean:
# 	rm -f *.o $(TARGET)


