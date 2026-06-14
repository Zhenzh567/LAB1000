#include "WareHouse.h"
#include <fstream>
#include <algorithm>
#include <iostream>

Warehouse::Warehouse() {}

void Warehouse::addCell(const StorageCell& cell)
{
    cells.push_back(cell);
}

bool Warehouse::removeCell(int cellNumber)
{
    for (auto it = cells.begin(); it != cells.end(); ++it)
    {
        if (it->getNumber() == cellNumber)
        {
            if (it->getList_of_tovars().empty())
            {
                cells.erase(it);
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

StorageCell* Warehouse::findCell(int cellNumber)
{
    for (auto& cell : cells)
    {
        if (cell.getNumber() == cellNumber)
        {
            return &cell;
        }
    }
    return nullptr;
}

bool Warehouse::addProductToCell(int cellNumber, const Product& product)
{
    StorageCell* cell = findCell(cellNumber);
    if (cell != nullptr)
    {
        cell->addTovar(product);
        return true;
    }
    return false;
}

bool Warehouse::removeProductFromCell(int cellNumber, int productId)
{
    StorageCell* cell = findCell(cellNumber);
    if (cell != nullptr)
    {
        cell->deleteTovar(productId);
        return true;
    }
    return false;
}

bool Warehouse::transferProduct(int productId, int fromCellNumber, int toCellNumber)
{
    StorageCell* fromCell = findCell(fromCellNumber);
    StorageCell* toCell = findCell(toCellNumber);

    if (fromCell == nullptr || toCell == nullptr)
    {
        return false;
    }

    std::vector<Product> products = fromCell->getList_of_tovars();
    const Product* foundProduct = nullptr;

    for (const auto& product : products)
    {
        if (product.getId() == productId)
        {
            foundProduct = &product;
            break;
        }
    }

    if (foundProduct != nullptr)
    {
        toCell->addTovar(*foundProduct);
        fromCell->deleteTovar(productId);
        return true;
    }

    return false;
}

Product* Warehouse::findProductById(int productId)
{
    for (auto& cell : cells)
    {
        std::vector<Product> products = cell.getList_of_tovars();
        for (auto& product : products)
        {
            if (product.getId() == productId)
            {
                return &product;
            }
        }
    }
    return nullptr;
}

std::vector<std::pair<Product*, int>> Warehouse::findProductsByName(const std::string& name)
{
    std::vector<std::pair<Product*, int>> result;
    for (auto& cell : cells)
    {
        std::vector<Product> products = cell.getList_of_tovars();
        for (auto& product : products)
        {
            if (product.getName() == name)
            {
                result.push_back({&product, cell.getNumber()});
            }
        }
    }
    return result;
}

double Warehouse::getTotalValue() const
{
    double total = 0.0;
    for (const auto& cell : cells)
    {
        std::vector<Product> products = cell.getList_of_tovars();
        for (const auto& product : products)
        {
            total += product.total();
        }
    }
    return total;
}

std::vector<Product> Warehouse::sortAllProductsByPrice() const
{
    std::vector<Product> allProducts;
    for (const auto& cell : cells)
    {
        std::vector<Product> products = cell.getList_of_tovars();
        for (const auto& product : products)
        {
            allProducts.push_back(product);
        }
    }
    std::sort(allProducts.begin(), allProducts.end(),
              [](const Product& a, const Product& b)
              {
                  return a.getPrice() < b.getPrice();
              });
    return allProducts;
}

std::vector<int> Warehouse::getEmptyCells() const
{
    std::vector<int> emptyCells;
    for (const auto& cell : cells)
    {
        if (cell.getList_of_tovars().empty())
        {
            emptyCells.push_back(cell.getNumber());
        }
    }
    return emptyCells;
}

std::vector<int> Warehouse::getFullCells() const
{
    std::vector<int> fullCells;
    for (const auto& cell : cells)
    {
        if (cell.getList_of_tovars().size() >= cell.getMax_size())
        {
            fullCells.push_back(cell.getNumber());
        }
    }
    return fullCells;
}

void Warehouse::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        return;
    }

    for (const auto& cell : cells)
    {
        file << "CELL " << cell.getNumber() << " " << cell.getMax_size() << std::endl;
        std::vector<Product> products = cell.getList_of_tovars();
        for (const auto& product : products)
        {
            file << "PRODUCT " << product.getId() << " "
                 << product.getName() << " "
                 << product.getPrice() << " "
                 << product.getQuantity() << std::endl;
        }
    }
    file.close();
}

void Warehouse::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return;
    }

    cells.clear();
    std::string type;
    while (file >> type)
    {
        if (type == "CELL")
        {
            int number;
            double maxSize;
            file >> number >> maxSize;
            std::vector<Product> products;
            StorageCell cell(number, maxSize, products);
            cells.push_back(cell);
        }
        else if (type == "PRODUCT")
        {
            if (cells.empty())
            {
                continue;
            }
            int id;
            std::string name;
            double price;
            double quantity;
            file >> id >> name >> price >> quantity;
            Product product(id, name, price, quantity);
            cells.back().addTovar(product);
        }
    }
    file.close();
}
