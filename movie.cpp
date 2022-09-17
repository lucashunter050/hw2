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

    movieWords.insert(rating_);
    movieWords.insert(genre_);

    std::string currWord;
    for (unsigned long i = 0; i < name_.size(); ++i) {
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

    outputString += name_;
    outputString += '\n';
    outputString += "Genre: ";
    outputString += genre_;
    outputString += " Rating: ";
    outputString += rating_;
    outputString += '\n';
    outputString += price_;
    outputString += ' ';
    outputString += qty_;
    outputString += " left.";

    return outputString;
}

void Movie::dump(std::ostream& os) const
{
    // call dump with polymorphism
    const Product* dummyProduct = dynamic_cast<const Product*>(this);
    dummyProduct->dump(os);

    os << genre_ << "\n" << rating_ << endl;
}