#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

#include <string>
class Product
{
private:
    int id;
    std::string name;
    double price;
    double quantity;
public:
    Product(int p_id, std::string p_name, double p_price, double  p_quantity);

    int getId() const;

    std::string getName() const;

    double getPrice() const;

    double getQuantity() const;

    void setPrice(double new_price);

    void setQuantity(double new_quantity);

    double total() const;


};


#endif
