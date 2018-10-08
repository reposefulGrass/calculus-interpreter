
HEADERS = binaryTree.h fraction.h term.h expression.h
FLAGS = -std=c++11 -Wall -Wextra -Wuninitialized -pedantic-errors -Wconversion
CC = g++

# here lies the driver
driver : driver.cpp $(HEADERS)
	$(CC) driver.cpp -o driver $(FLAGS)

test : test.cpp $(HEADERS)
	$(CC) test.cpp -o test $(FLAGS)

