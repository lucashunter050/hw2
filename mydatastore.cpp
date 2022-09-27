#include "mydatastore.h"


void MyDataStore::addProduct(Product* p) {
    products_.insert(p);
    // this->makeMap();

    std::set<std::string>::iterator it1 = p->keywords().begin();
    std::set<Product*> addSet;
    while (it1 != p->keywords().end()) {
        // see if key is already in list, if it is, just add the new 
        // product to the existing set for the key
        if (keywordMapping.find(*it1) != keywordMapping.end()) {
            keywordMapping.find(*it1)->second.insert(p);
        } else {
            addSet.insert(p);
            keywordMapping.insert({*it1, addSet});
        }
        addSet.clear();
        ++it1;
    }
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

    if (type) {
        // perform an OR search
        for (size_t i = 0; i < terms.size(); ++i) {
            // replace with set union function at some point
            if (keywordMapping.find(terms[i]) != keywordMapping.end()) {
                intermediary = setUnion(intermediary, keywordMapping.at(terms[i]));
            }
        }
    } else {
        // perform an AND search
        for (size_t i = 0; i < terms.size(); ++i) {
            if (keywordMapping.find(terms[i]) != keywordMapping.end()) {
                if (intermediary.empty()) {
                    intermediary = keywordMapping.at(terms[i]);
                } else {
                    intermediary = setIntersection(intermediary, keywordMapping.at(terms[i]));
                }
            }
        }
    }

    std::set<Product*>::iterator it1 = intermediary.begin();
    while (it1 != intermediary.end()) {
        matches.push_back(*it1);
        ++it1;
    }

    return matches;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>\n";
    std::set<Product*>::iterator it = products_.begin();

    while (it != products_.end())
    {
        ofile << *it << std::endl;
    }
    
    ofile << "</products>\n";

    ofile << "<users>\n";
    std::set<User*>::iterator it2 = users_.begin();

    while (it2 != users_.end())
    {
        ofile << *it2 << std::endl;
    }

    ofile << "</users>\n";
    
}

/*
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

}*/