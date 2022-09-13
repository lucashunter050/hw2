#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty,
    const std::string isbn, const std::string author) : 
        Product("book", name, price, qty)
{
    isbn_ = isbn;
    author_ = author;
}

Book::~Book()
{
}

std::string Book::getAuthor() const
{
    return author_;
}

std::string Book::getISBN() const
{
    return author_;
}

