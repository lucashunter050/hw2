#include <sstream>
#include <iomanip>
#include "book.h"
#include <ctype.h>

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

    std::string currWord;
    for (unsigned long i = 0; i < name_.size(); ++i) {
        if ((ispunct(name_[i]) && (currWord.size() > 1)) || 
        (isspace(name_[i]) && (currWord.size() > 1))) {
            bookWords.insert(currWord);
            currWord = "";
        }  
        else if (ispunct(name_[i]) || isspace(name_[i])) {
            currWord = "";
        }
        else {
            currWord += tolower(name_[i]);
        }
    }

    // check if there's any leftover string that needs to be added
    if (currWord.size() > 1) {
        bookWords.insert(currWord);
        currWord = "";
    }

    for (unsigned long i = 0; i < author_.size(); ++i) {
        if ((ispunct(author_[i]) && (currWord.size() > 1)) || 
            (isspace(author_[i]) && (currWord.size() > 1))) {
            bookWords.insert(currWord);
            currWord = "";
        }  
        else if (ispunct(author_[i]) || isspace(author_[i])) {
            currWord = "";
        }
        else {
            currWord += tolower(author_[i]);
        }
    }

    // check if there's any leftover string that needs to be added
    if (currWord.size() > 1) {
        bookWords.insert(currWord);
        currWord = "";
    }

    return bookWords;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const
{
    bool isAMatch = false;

    return isAMatch;
}

std::string Book::displayString() const {
    std::string outputString;

    int priceDecimalPointIndex = 0;
    string priceStr = to_string(price_);

    for (size_t i = 0; i < priceStr.size(); ++i) {
        if (priceStr[i] == '.') {
            priceDecimalPointIndex = i;
            break;
        } 
    }

    outputString += name_;
    outputString += '\n';
    outputString += "Author: ";
    outputString += author_;
    outputString += " ISBN: ";
    outputString += isbn_;
    outputString += '\n';
    outputString += priceStr.substr(0, priceDecimalPointIndex);
    outputString += priceStr.substr(priceDecimalPointIndex, 3);
    outputString += ' ';
    outputString += to_string(qty_);
    outputString += " left.";

    return outputString;
}

void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
    os << isbn_ << "\n" << author_ << endl;
}