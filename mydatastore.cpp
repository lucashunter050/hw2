#include "mydatastore.h"


void MyDataStore::addProduct(Product* p) {
    products_.insert(p);

    // add the product to the corresponding set in keywordMapping
    for (std::string itr1: p->keywords()) {
        if (keywordMapping.find(itr1) != keywordMapping.end()) {
            keywordMapping.find(itr1)->second.insert(p);
        } else {
            std::set<Product*> addSet2;
            addSet2.insert(p);
            keywordMapping.insert({itr1, addSet2});
        }
    }
}

void MyDataStore::addUser(User* u) {
    // add to mapping of usernames to user products
    users_map_.insert({u->getName(), u});

    // initialize a deque for the new user's cart
    std::deque<Product*> addDeque;
    cart_.insert({u, addDeque});
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    // type 0 is AND
    // type 1 is OR

    std::vector<Product*> matches;
    std::set<Product*> intermediary;

    if (type) {
        // perform an OR search
        for (size_t i = 0; i < terms.size(); ++i) {
            if (keywordMapping.find(terms[i]) != keywordMapping.end()) {
                intermediary = setUnion(intermediary, keywordMapping.at(terms[i]));
            }
        }
    } else {
        // perform an AND search
        for (size_t i = 0; i < terms.size(); ++i) {
            if (keywordMapping.find(terms[i]) != keywordMapping.end()) {
                /* if this is the first keyword, we need to initialize the intermediary
                set, otherwise we keep finding taking intersection of more and more sets*/
                if (intermediary.empty()) {
                    intermediary = keywordMapping.at(terms[i]);
                } else {
                    intermediary = setIntersection(intermediary, keywordMapping.at(terms[i]));
                }
            }
        }
    }

    // push the intermediary set to the matches vector
    for (Product* itr1: intermediary) {
        matches.push_back(itr1);
    }

    return matches;
}

void MyDataStore::addToCart(std::string username, Product* toAdd) {
    if (users_map_.find(username) == users_map_.end()) {
        std::cout << "Invalid request" << std::endl;
        return;
    }
    // pushes the product to the deque mapped to each user
    cart_.at(users_map_.at(username)).push_back(toAdd);
}

void MyDataStore::viewCart(std::string username) {
    if (users_map_.find(username) == users_map_.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    std::deque<Product*>::iterator it = cart_.at(users_map_.at(username)).begin();

    int index = 0;

    // loops through the cart deque and displays the items in the cart
    while (it != cart_.at(users_map_.at(username)).end()) {
        std::cout << index << ": ";
        std::cout << (*it)->displayString();
        std::cout << std::endl;
        ++index;
        ++it;
    }
    
}

void MyDataStore::buyCart(std::string username) {
    // approach to avoid modifying container: iterate over the deque 
    // and add the elements not purchased to a new deque then set original 
    // deque equal to that

    if (users_map_.find(username) == users_map_.end()) {
        std::cout << "Invalid request" << std::endl;
        return;
    }

    std::deque<Product*> temp;
    for (Product* toBuy: cart_.at(users_map_.at(username))) {
        if (!toBuy->getQty()) {
            temp.push_back(toBuy);
        } else if (users_map_.at(username)->getBalance() < toBuy->getPrice()) {
            temp.push_back(toBuy);
        } else {
            users_map_.at(username)->deductAmount(toBuy->getPrice());
            toBuy->subtractQty(1);
        }
    }

    cart_.at(users_map_.at(username)) = temp;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>\n";
    for (Product* outputProduct: products_) {
        outputProduct->dump(ofile);
    }
    ofile << "</products>\n";
    ofile << "<users>\n";
    for (std::pair<std::string, User*> outputUser: users_map_) {
        outputUser.second->dump(ofile);
    }
    ofile << "</users>\n";
}