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
    std::set<std::string> clothingKeywords;
    std::string currWord;

    // adds the name keywords
    for (unsigned long i = 0; i < name_.size(); ++i) {
        if ((ispunct(name_[i]) && (currWord.size() > 1)) || 
            (isspace(name_[i]) && (currWord.size() > 1))) {
            clothingKeywords.insert(currWord);
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
        clothingKeywords.insert(currWord);
        currWord = "";
    }

    // adds the brand keywords
    for (unsigned long i = 0; i < brand_.size(); ++i) {
        if ((ispunct(brand_[i]) && (currWord.size() > 1)) || 
            (isspace(brand_[i]) && (currWord.size() > 1))) {
            clothingKeywords.insert(currWord);
            currWord = "";
        }  
        else if (ispunct(brand_[i]) || isspace(brand_[i])) {
            currWord = "";
        }
        else {
            currWord += tolower(brand_[i]);
        }
    }

    // check if there's any leftover string that needs to be added
    if (currWord.size() > 1) {
        clothingKeywords.insert(currWord);
        currWord = "";
    }

    return clothingKeywords;

}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
    bool isAMatch = false;

    return isAMatch;
}

std::string Clothing::displayString() const
{
    std::string outputString;

    int priceDecimalPointIndex = 0;
    string priceStr = to_string(price_);

    for (int i = 0; i < priceStr.size(); ++i) {
        if (priceStr[i] == '.') {
            priceDecimalPointIndex = i;
            break;
        } 
    }


    outputString += name_;
    outputString += '\n';
    outputString += "Size: ";
    outputString += size_;
    outputString += " Brand: ";
    outputString += brand_;
    outputString += '\n';
    outputString += priceStr.substr(0, priceDecimalPointIndex);
    outputString += priceStr.substr(priceDecimalPointIndex, 3);
    outputString += ' ';
    outputString += to_string(qty_);
    outputString += " left.";

    return outputString;
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;

    os << size_ << "\n" << brand_ << endl;
}