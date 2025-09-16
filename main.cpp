#include "header.h"

int main() {
    while (true) {
        std::string a;
        int count = 0;
        std::cout << "\nМеню выбора"
                << "\n1-заполнить память n-количеством элементов"
                << "\n2-вывести битовую карту и информацию о занятых блоках"
                << "\n3-очистить блок"
                << "\nвведите пункт меню: ";
        std::cin >> a;

        if (a == "1") {
            while (true) {
                std::cout << "\nвведите количество элементов: ";
                if (std::cin >> count) {
                    push(count);
                    break;
                } else {
                    std::cout << "Ошибка, Попробуйте снова.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        } else if (a == "2") {
            print();
        } else if (a == "3") {
            deleter(deleterprint());
        } else std::cout << "повторите попытку\n";
    }
}
