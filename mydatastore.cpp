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
    users_map_.insert({u->getName(), u});
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

void MyDataStore::addToCart(std::string username, Product* toAdd) {
    cart_.at(users_map_.at(username)).push_back(toAdd);
}

void MyDataStore::viewCart(std::string username) {
    if (users_map_.find(username) == users_map_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    std::deque<Product*>::iterator it = cart_.at(users_map_.at(username)).begin();

    int index = 0;
    while (it != cart_.at(users_map_.at(username)).end()) {
        std::cout << index << ": ";
        std::cout << (*it)->displayString();
        ++index;
        ++it;
    }
    
}

void MyDataStore::buyCart(std::string username) {
    std::deque<Product*>::iterator it = cart_.at(users_map_.at(username)).begin();

    while (it != cart_.at(users_map_.at(username)).end()) {
        if ((*it)->getQty() && (users_map_.at(username)->getBalance())) {
            --(*it);
            users_map_.at(username)->deductAmount((*it)->getPrice());
            std::deque<Product*>::iterator temp = it;
            cart_.at(users_map_.at(username)).erase(temp);
            ++it;
        }
    }
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
    std::map<std::string, User*>::iterator it2 = users_map_.begin();

    while (it2 != users_map_.end())
    {
        ofile << it2->second << std::endl;
    }

    ofile << "</users>\n";
    
}