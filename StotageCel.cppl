#include "StotageCell.h"
#include <algorithm>

StorageCell::StorageCell(int p_number, double p_max_size, std::vector<Product> p_list_of_tovars)
{
    number = p_number;
    max_size = p_max_size;
    list_of_tovars = p_list_of_tovars;
}

int StorageCell::getNumber() const
{
    return number;
}

double StorageCell::getMax_size() const
{
    return max_size;
}

std::vector<Product> StorageCell::getList_of_tovars() const
{
    return list_of_tovars;  // возвращает копию
}

void StorageCell::addTovar(const Product& product)
{
    if (list_of_tovars.size() < max_size)
    {
        list_of_tovars.push_back(product);
    }
}

void StorageCell::deleteTovar(int productId)
{
    for (auto it = list_of_tovars.begin(); it != list_of_tovars.end(); ++it)
    {
        if (it->getId() == productId)
        {
            list_of_tovars.erase(it);
            break;
        }
    }
}

std::string StorageCell::findTovar(int id2)
{
    for (const auto& product : list_of_tovars)
    {
        if (product.getId() == id2)
        {
            return product.getName();
        }
    }
    return "Товар не найден";
}
