#include <iostream>
#include <string>
#include "Product.h"


Product::Product(int p_id, std::string p_name, double p_price, double  p_quantity)
    {
        id = p_id;
        name = p_name;
        price = p_price;
        quantity = p_quantity;
    }
int Product::getId() const
    {
        return id;
    }
std::string Product::getName() const
    {
        return name;
    }
double Product::getPrice() const
    {
        return price;
    }
double Product::getQuantity() const
    {
        return quantity;
    }
void Product::setPrice(double new_price)
    {
        price = new_price;
    }
void Product::setQuantity(double new_quantity)
    {
        quantity = new_quantity;
    }
double Product::total() const
    {
        return price * quantity;
    }
