PP = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
C_FLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

bank: bank.o member.o
	$(PP) -o bank bank.o member.o

bank.o: member.h
	$(PP) $(C_FLAGS) -c bank.cpp

member.o: member.h
	$(PP) $(C_FLAGS) -c member.cpp

clean:
	rm -f *.o bank