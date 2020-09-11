MYSQL_CONCPP_DIR = /usr/local/mysql-connector-c++-8.0
CPPFLAGS = -I $(MYSQL_CONCPP_DIR)/include -L $(MYSQL_CONCPP_DIR)/lib64
LDLIBS = -lmysqlcppconn8
CXX = clang++ -stdlib=libc++
CXXFLAGS = -std=c++11
#app : app.cc


#PP = g++
#CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
#DEBUGGING_FLAGS = -g -O0
#C_FLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

bank: bank.o member.o
	$(CXX) -o bank bank.o member.o $(CPPFLAGS) $(LDLIBS)

bank.o: member.h
	$(CXX) $(CXXFLAGS) -c bank.cpp

member.o: member.h
	$(CXX) $(CXXFLAGS) -c member.cpp

clean:
	rm -f *.o bank