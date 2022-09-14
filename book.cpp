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
    return isbn_;
}

std::set<std::string> Book::keywords() const 
{
    std::set<std::string> bookWords;
    bookWords.insert(isbn_);
    bookWords.insert(author_);

    std::string currWord;
    for (unsigned long i = 0; i < name_; ++i) {
        if (static_cast<int>(name_[i]) == 32 && (currWord.size() > 1)) {
            bookWords += currWord;
            currWord = "";
        }  
        else if (static_cast<int>(name_[i]) == 32) {
            currWord = "";
        }
        else {
            currWord += name_[i];
        }
    }

    return bookWords;
}

bool isMatch(std::vector<std::string>& searchTerms) const
{
    bool isAMatch = false;


    return isAMatch;
}