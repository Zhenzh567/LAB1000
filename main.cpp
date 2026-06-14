#include <iostream>
#include "WareHouse.h"

int main()
{
    Warehouse warehouse;
    int choice;

    while (true)
    {
        std::cout << "\n========================================" << std::endl;
        std::cout << "        СИСТЕМА УПРАВЛЕНИЯ СКЛАДОМ       " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "1. Добавить ячейку" << std::endl;
        std::cout << "2. Удалить ячейку" << std::endl;
        std::cout << "3. Добавить товар в ячейку" << std::endl;
        std::cout << "4. Удалить товар из ячейки" << std::endl;
        std::cout << "5. Переместить товар между ячейками" << std::endl;
        std::cout << "6. Найти товар по ID" << std::endl;
        std::cout << "7. Найти товары по названию" << std::endl;
        std::cout << "8. Показать все товары (сортировка по цене)" << std::endl;
        std::cout << "9. Показать общую стоимость склада" << std::endl;
        std::cout << "10. Показать пустые ячейки" << std::endl;
        std::cout << "11. Показать заполненные ячейки" << std::endl;
        std::cout << "12. Сохранить склад в файл" << std::endl;
        std::cout << "13. Загрузить склад из файла" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int number, maxSize;
            std::cout << "Номер ячейки: ";
            std::cin >> number;
            std::cout << "Максимальная вместимость: ";
            std::cin >> maxSize;
            StorageCell cell(number, maxSize, {});
            warehouse.addCell(cell);
            std::cout << "Ячейка добавлена." << std::endl;
            break;
        }
        case 2:
        {
            int number;
            std::cout << "Номер ячейки: ";
            std::cin >> number;
            if (warehouse.removeCell(number))
                std::cout << "Ячейка удалена." << std::endl;
            else
                std::cout << "Не удалось удалить (ячейка не пуста или не найдена)." << std::endl;
            break;
        }
        case 3:
        {
            int cellNumber, id, quantity;
            std::string name;
            double price;
            std::cout << "Номер ячейки: ";
            std::cin >> cellNumber;
            std::cout << "ID товара: ";
            std::cin >> id;
            std::cout << "Название: ";
            std::cin >> name;
            std::cout << "Цена: ";
            std::cin >> price;
            std::cout << "Количество: ";
            std::cin >> quantity;
            Product product(id, name, price, quantity);
            if (warehouse.addProductToCell(cellNumber, product))
                std::cout << "Товар добавлен." << std::endl;
            else
                std::cout << "Ячейка не найдена." << std::endl;
            break;
        }
        case 4:
        {
            int cellNumber, productId;
            std::cout << "Номер ячейки: ";
            std::cin >> cellNumber;
            std::cout << "ID товара: ";
            std::cin >> productId;
            if (warehouse.removeProductFromCell(cellNumber, productId))
                std::cout << "Товар удалён." << std::endl;
            else
                std::cout << "Ячейка или товар не найдены." << std::endl;
            break;
        }
        case 5:
        {
            int productId, fromCell, toCell;
            std::cout << "ID товара: ";
            std::cin >> productId;
            std::cout << "Из ячейки: ";
            std::cin >> fromCell;
            std::cout << "В ячейку: ";
            std::cin >> toCell;
            if (warehouse.transferProduct(productId, fromCell, toCell))
                std::cout << "Товар перемещён." << std::endl;
            else
                std::cout << "Ошибка перемещения." << std::endl;
            break;
        }
        case 6:
        {
            int productId;
            std::cout << "ID товара: ";
            std::cin >> productId;
            Product* p = warehouse.findProductById(productId);
            if (p != nullptr)
                std::cout << "Найден: " << p->getName() << ", цена: " << p->getPrice()
                          << ", количество: " << p->getQuantity() << std::endl;
            else
                std::cout << "Товар не найден." << std::endl;
            break;
        }
        case 7:
        {
            std::string name;
            std::cout << "Название товара: ";
            std::cin >> name;
            auto results = warehouse.findProductsByName(name);
            if (results.empty())
            {
                std::cout << "Товары не найдены." << std::endl;
            }
            else
            {
                for (const auto& item : results)
                {
                    std::cout << "Товар: " << item.first->getName()
                              << ", цена: " << item.first->getPrice()
                              << ", количество: " << item.first->getQuantity()
                              << ", ячейка: " << item.second << std::endl;
                }
            }
            break;
        }
        case 8:
        {
            std::vector<Product> sorted = warehouse.sortAllProductsByPrice();
            if (sorted.empty())
            {
                std::cout << "Нет товаров на складе." << std::endl;
            }
            else
            {
                std::cout << "Все товары (по возрастанию цены):" << std::endl;
                for (const auto& p : sorted)
                {
                    std::cout << "  " << p.getName() << ": " << p.getPrice() << " руб." << std::endl;
                }
            }
            break;
        }
        case 9:
        {
            std::cout << "Общая стоимость склада: " << warehouse.getTotalValue() << " руб." << std::endl;
            break;
        }
        case 10:
        {
            std::vector<int> empty = warehouse.getEmptyCells();
            if (empty.empty())
                std::cout << "Пустых ячеек нет." << std::endl;
            else
            {
                std::cout << "Пустые ячейки: ";
                for (int num : empty)
                    std::cout << num << " ";
                std::cout << std::endl;
            }
            break;
        }
        case 11:
        {
            std::vector<int> full = warehouse.getFullCells();
            if (full.empty())
                std::cout << "Заполненных ячеек нет." << std::endl;
            else
            {
                std::cout << "Заполненные ячейки: ";
                for (int num : full)
                    std::cout << num << " ";
                std::cout << std::endl;
            }
            break;
        }
        case 12:
        {
            std::string filename;
            std::cout << "Имя файла: ";
            std::cin >> filename;
            warehouse.saveToFile(filename);
            std::cout << "Сохранено в " << filename << std::endl;
            break;
        }
        case 13:
        {
            std::string filename;
            std::cout << "Имя файла: ";
            std::cin >> filename;
            warehouse.loadFromFile(filename);
            std::cout << "Загружено из " << filename << std::endl;
            break;
        }
        case 0:
            std::cout << "Выход из программы. До свидания!" << std::endl;
            return 0;
        default:
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
        }
    }

    return 0;
}
