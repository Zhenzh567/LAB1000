#ifndef WAREHOUSE_H_INCLUDED
#define WAREHOUSE_H_INCLUDED

#include "StotageCell.h"
#include <vector>
#include <string>

class Warehouse
{
private:
    std::vector<StorageCell> cells;

public:
    Warehouse();

    void addCell(const StorageCell& cell);
    bool removeCell(int cellNumber);
    StorageCell* findCell(int cellNumber);

    bool addProductToCell(int cellNumber, const Product& product);
    bool removeProductFromCell(int cellNumber, int productId);
    bool transferProduct(int productId, int fromCellNumber, int toCellNumber);

    Product* findProductById(int productId);
    std::vector<std::pair<Product*, int>> findProductsByName(const std::string& name);

    double getTotalValue() const;
    std::vector<Product> sortAllProductsByPrice() const;

    std::vector<int> getEmptyCells() const;
    std::vector<int> getFullCells() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif
