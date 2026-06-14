#ifndef PRODUCT_a_INCLUDED
#define PRODUCT_a_INCLUDED

#include "Product.h"
#include <vector>
#include <string>

class StorageCell
{
private:
    int number;
    double max_size;
    std::vector<Product> list_of_tovars;

public:
    StorageCell(int p_number, double p_max_size, std::vector<Product> p_list_of_tovars);
    int getNumber() const;
    double getMax_size() const;
    std::vector<Product> getList_of_tovars() const; 
    void addTovar(const Product& product);
    void deleteTovar(int productId);
    std::string findTovar(int id2);
};

#endif
