CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

# emulate this terminal line:
# g++ -g amazon.cpp db_parser.cpp clothing.cpp book.cpp movie.cpp mydatastore.cpp product_parser.cpp util.cpp product.cpp user.cpp


OBJS=amazon.o user.o db_parser.o product.o product_parser.o util.o book.o clothing.o movie.o mydatastore.o

amazon: amazon.o user.o db_parser.o product.o product_parser.o util.o book.o clothing.o movie.o mydatastore.o
	g++ -g -Wall -std=c++11 amazon.o user.o db_parser.o product.o product_parser.o util.o book.o clothing.o movie.o mydatastore.o -o amazon

amazon.o: amazon.cpp db_parser.h product_parser.h datastore.h
	g++ -g -c -Wall -std=c++11 amazon.cpp
user.o: user.cpp user.h
	g++ -g -c -Wall -std=c++11 user.cpp
db_parser.o: db_parser.cpp db_parser.h product.h product_parser.h user.h datastore.h
	g++ -g -c -Wall -std=c++11 db_parser.cpp
product.o: product.cpp product.h
	g++ -g -c -Wall -std=c++11 product.cpp
product_parser.o: product_parser.cpp product_parser.h product.h
	g++ -g -c -Wall -std=c++11 product_parser.cpp
util.o: util.cpp util.h
	g++ -g -c -Wall -std=c++11 util.cpp
book.o: book.cpp book.h product.h
	g++ -g -c -Wall -std=c++11 book.cpp
clothing.o: clothing.cpp clothing.h product.h
	g++ -g -c -Wall -std=c++11 clothing.cpp
movie.o: movie.cpp movie.h product.h
	g++ -g -c -Wall -std=c++11 movie.cpp
mydatastore.o: mydatastore.cpp mydatastore.h datastore.h
	g++ -g -c -Wall -std=c++11 mydatastore.cpp


clean:
	rm -f *.o amazon
