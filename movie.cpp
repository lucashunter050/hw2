#include <sstream>
#include <iomanip>
#include "movie.h"
#include <ctype.h>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty,
    const std::string genre, const std::string rating) :
    Product("movie", name, price, qty)
{
    rating_ = rating;
    genre_ = genre;
} 

Movie::~Movie()
{
}

std::string Movie::getGenre() const
{
    return genre_;
}

std::string Movie::getRating() const
{
    return rating_;
}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> movieWords;

    std::string currWord;

    // make the genre and rating lowercase
    for (unsigned i = 0; i < rating_.size(); ++i) {
        currWord += tolower(rating_[i]);
    }
    movieWords.insert(currWord);
    currWord = "";

    for (unsigned i = 0; i < genre_.size(); ++i) {
        currWord += tolower(genre_[i]);
    }
    movieWords.insert(currWord);
    currWord = "";

    
    for (unsigned i = 0; i < name_.size(); ++i) {
        if ((ispunct(name_[i]) && (currWord.size() > 1)) || 
            (isspace(name_[i]) && (currWord.size() > 1))) {
            movieWords.insert(currWord);
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
        movieWords.insert(currWord);
        currWord = "";
    }
    
    return movieWords;

}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
    bool isAMatch = false;

    return isAMatch;
}

std::string Movie::displayString() const
{
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
    outputString += "Genre: ";
    outputString += genre_;
    outputString += " Rating: ";
    outputString += rating_;
    outputString += '\n';
    outputString += priceStr.substr(0, priceDecimalPointIndex);
    outputString += priceStr.substr(priceDecimalPointIndex, 3);
    outputString += ' ';
    outputString += to_string(qty_);
    outputString += " left.";

    return outputString;
}

void Movie::dump(std::ostream& os) const
{
    os << std::fixed;
    os << std::setprecision(2);
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
    os << genre_ << "\n" << rating_ << endl;
}