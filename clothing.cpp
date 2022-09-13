#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty,
    const std::string brand, const std::string size) :
    Product("clothing", name, price, qty)
{
    brand_ = brand;
    size_  = size;
} 

Clothing::~Clothing()
{
}

std::string Clothing::getBrand() const
{
    return brand_;
}

std::string Clothing::getSize() const
{
    return size_;
}

std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> keywords;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms)
{
    bool isAMatch = false;

    return isAMatch;
}

std::string Clothing::displayString()
{
    std::string outputString;

    return outputString;
}

void Clothing::dump(std::ostream& os)
{
    // dynamically cast the clothing object to the base class product and call dump
    const Product* dummyProduct;
    dummyProduct = dynamic_cast<const Product*>(this);
    dummyProduct->dump();

    os << size_ << "\n" << brand_ << endl;
}