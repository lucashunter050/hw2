#ifndef MDATASTORE_H
#define MDATASTORE_H
#include "datastore.h"
#include "util.h"
#include "product.h"
#include <map>
#include <string>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore() {};

    void addProduct(Product* p);

    void addUser(User* u);

    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    void dump(std::ostream& ofile);

    void makeMap();

private:
    std::set<User*> users_;
    std::set<Product*> products_;

    std::map<std::string, Product*> keywordMapping; 
};

#endif