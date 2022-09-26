#include "mydatastore.h"


void MyDataStore::addProduct(Product* p) {
    products_.insert(p);
    this->makeMap();
}

void MyDataStore::addUser(User* u) {
    users_.insert(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    // type 0 is AND
    // type 1 is OR

    // want to search through all products_

    std::vector<Product*> matches;
    std::set<Product*> intermediary;
    if (!type) {
        //intermediary = setIntersection()
        // products must contain all search words
        for (size_t i = 0; i < terms.size(); ++i) {
            keywordMapping.find(terms[i]);
        }
    } else {
        for (size_t i = 0; i < terms.size(); ++i) {
            // brute force method -- change later with maps
            std::set<Product*>::iterator it = products_.begin();
            while (it != products_.end()) {
                std::set<std::string> temp = (*it)->keywords();
                if (temp.find(terms[i]) != products_.end()) {
                    matches.push_back(*it);
                }
            }
        }
    }


    return matches;
}

void MyDataStore::dump(std::ostream& ofile) {

}

void MyDataStore::makeMap() {
    // note: probably does not work b/c there can probably be identical keys to diff products
    keywordMapping.clear();
    std::set<Product*>::iterator it = products_.begin();

    while (it != products_.end()) {
        std::set<std::string> keywordsSet = (*it)->keywords();
        std::set<std::string>::iterator it2 = keywordsSet.begin();
        while (it2 != keywordsSet.end()) {
            std::pair<std::string, Product*> insertPair;
            insertPair.first = *it2;
            insertPair.second = *it;
            keywordMapping.insert(insertPair);
            ++it2;
        }

        ++it;
    
    }

}