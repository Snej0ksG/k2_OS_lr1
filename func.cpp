#include "header.h"
std::map<std::byte*, int> container;
std::byte *array = new std::byte[1024];

void push(int &count) {
    int replays = (count + 64 - 1) / 64;
    int free = 0;
    int upfree = 0;
    int fullfree = 0;
    int freenuls = 0;
    std::byte *address;

    for (int i = 0; i < 1024; i++) {
        if (*(array + i) == std::byte{0}) {
            fullfree++;
            free++;
        }
        if (i == 1023 || *(array + i) == std::byte{1}) {
            if (free > upfree) {
                upfree = free;
                free = 0;
            }
        }
    }
    std::cout << "\nчисло свободной памяти: " << fullfree << std::endl;
    std::cout << "число свободной памяти в наибольшем кластере: " << upfree << "\n" << std::endl;
    if (replays > upfree / 64) std::cout << "\nне хватает памяти\n";
    else {
        for (int g = 0; g < 1024; g++) {
            if (*(array + g) == std::byte{0}) {
                freenuls++;
            } else freenuls = 0;
            if (freenuls == count) {
                address = (array + (g - freenuls + 1));
                    std::cout << "адрес выделенного участка: " << (address) << std::endl;
                    container[address]=count;
                    for (int i = 0; i < count; i++) {
                        *(address + i) = std::byte{1};
                    }
                break;
            }
        }
    }
}

void deleter(std::byte *address) {

    int value = container[address];
    for (int i = 0; i < value; i++) *(address + i) = std::byte{0};
    container.erase(address);
    std::cout << "очищение прошло успешно\n";
}

std::byte *deleterprint() {
    int value = 0;
    int count =1;
    std::map<int, std::byte*> delmap;
    for (int i=0; i<1024; i++)
    {
        if (container.find((array+i)) != container.end()) {
            std::cout <<count<<" : "<<(array+i)<< " адрес начала заполнения, количество элементов: " << container[(array+i)] << std::endl;
            delmap[count]=(array+i);
            count++;
        }
    }
    while (true) {
        std::cout << "\nвведите номер блока для очищения: ";
        if (std::cin >> value && value > 0) {
            break;
        } else {
            std::cout << "Ошибка, Попробуйте снова.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cout << "вы выбрали:" << delmap[value]<< std::endl;
    return delmap[value];
}

void print() {
    int count = 0;
    int countempty = 0;
    int countfull = 0;
    int numb=0;
    std::byte *address;
    std::cout << "\nбитовая карта: ";
    for (int i = 0; i < 1024;) {
        if (*(array + i) == std::byte{1}) {
                address = (array + i);
                for (int j = 0; j < 64; j++) {
                    if (*(address+j)==std::byte{1} ) {
                        numb++;
                    }
                    else {
                        break;
                    }
                }
                if (numb == 64) {
                    std::cout << "1";
                    i += 64;
                    numb = 0;
                }
                else {
                    std::cout << "0";
                    i += 64;
                    numb = 0;
                }

        } else {
            std::cout << "0";
            i += 64;
        }
    }
    std::cout << "\n";
    for (int i = 0; i < 1024;) {
        if (*(array + i) == std::byte{1}) {
            address = (array + i);
            for (int j = 0; j < 64; j++) {
                if (*(address+j)==std::byte{1} ) {
                    numb++;
                }
                else {
                    break;
                }
            }
            if (numb == 64) {
                std::cout << count << ": 1 адрес: " << (array + i);
                std::cout << std::endl;
                i += 64;
                count++;
                countfull++;
                numb = 0;
            }
            else {
                std::cout << count << ": 0 адрес: " << (array + i) << std::endl;
                i += 64;
                count++;
                countempty++;
                numb = 0;
            }
        }
        else {
            std::cout << count << ": 0 адрес: " << (array + i) << std::endl;
            i += 64;
            count++;
            countempty++;
        }
    }
    std::cout << "\n";
    for (int i=0; i<1024; i++)
        {
        if (container.find((array+i)) != container.end()) {
            std::cout <<(array+i)<< " адрес начала заполнения, количество элементов: " << container[(array+i)] << std::endl;
        }
        }
    std::cout << "\n количество заполненых участков: " << countfull << "\n количество пустых участков: " << countempty
            << std::endl;
}
