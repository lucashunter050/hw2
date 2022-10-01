## HW 2

 - Name: Lucas Hunter
 - Email: lphunter@usc.edu

### Programming Problem Notes

Steps to compile the project:
 - Navigate to hw2 directory
 - to use the makefile to compile, type "make" and then "./amazon [inputname]" where 
inputname is the name of the formatted database

 - alternatively, to use g++ to compile the project, type "g++ -g -Wall -std=c++11 amazon.cpp db_parser.cpp clothing.cpp book.cpp movie.cpp mydatastore.cpp product_parser.cpp util.cpp product.cpp user.cpp" and then "./a.out [inputname]" where [inputname] is the name of the formatted database

Design decisions you made or other non-trivial choices for your implementation
 - I used maps to store usernames to users, users to a deque of products (their cart), and each keyword to a set of products
 that have that matching keyword

Any additional tests you wrote and what files those exist in
 - I added a few products to database.txt in random order and it seems to work fine