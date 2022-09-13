#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Book : public Product {
public:
    Book(const std::string category, const std::string name, double price,
    int qty, const std::string isbn, const std::string author);
    ~Book();

    virtual std::set<std::string> keywords() const = 0;

    virtual bool isMatch(std::vector<std::string>& searchTerms) const;

    virtual std::string displayString() const = 0;

    virtual void dump(std::ostream& os) const;

    // new accessors and mutators
    std::string getISBN() const;
    std::string getAuthor() const;

private:
    std::string isbn_;
    std::string author_;
};
#endif