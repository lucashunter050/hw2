#ifndef MDATASTORE_H
#define MDATASTORE_H
#include "datastore.h"
#include "util.h"
#include "product.h"
#include <map>
#include <string>
#include <queue>

class MyDataStore : public DataStore {
public:
    MyDataStore() {}

    // destructor - must deallocate all products and users here when the
    // object is destroyed
    ~MyDataStore() {
        for (Product* prod : products_) {
            delete prod;
        }
        for (std::pair<std::string, User*> toDelete : users_map_) {
            delete toDelete.second;
        }
    }

    void addProduct(Product* p);

    void addUser(User* u);

    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    void addToCart(std::string username, Product* toAdd);

    void viewCart(std::string username);

    void buyCart(std::string username);

    void dump(std::ostream& ofile);

private:
    std::map<std::string, User*> users_map_;
    std::set<Product*> products_;

    // store a mapping between the keywords and the matching products
    std::map<std::string, std::set<Product*>> keywordMapping; 

    // store the user carts
    // used a deque because it supports iterators and I can treat it as FIFO
    std::map<User*, std::deque<Product* >> cart_;
};

#endif