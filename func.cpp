#include "header.h"
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
        if (i == 1023 || *(array + i) == std::byte{2}) {
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
            if (freenuls == replays * 64) {
                address = (array + (g - freenuls + 1));
                for (int j = 0; j < replays; j++) {
                    std::cout << "адрес выделенного участка: " << (address) << std::endl;
                    for (int i = 0; i < 64; i++) {
                        if (i == 0) *(address + i) = std::byte{2};
                        else *(address + i) = std::byte{1};
                    }
                    address = (address + 64);
                }
                break;
            }
        }
    }
}

void deleter(std::byte *address) {
    for (int i = 0; i < 64; i++) *(address + i) = std::byte{0};
    std::cout << "очищение прошло успешно\n";
}

std::byte *deleterprint() {
    int count = 0;
    int value = 0;
    std::cout << "\n";
    for (int i = 0; i < 1024;) {
        if (*(array + i) == std::byte{2}) {
            std::cout << count << ": 1 адрес: " << (array + i) << std::endl;
            i += 64;
            count++;
        } else {
            std::cout << count << ": 0 адрес: " << (array + i) << std::endl;
            i += 64;
            count++;
        }
    }
    while (true) {
        std::cout << "\nвведите номер блока для очищения: ";
        if (std::cin >> value && value<16 && value >= 0) {
            break;
        } else {
            std::cout << "Ошибка, Попробуйте снова.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cout << "вы выбрали:" << (array + (value * 64)) << std::endl;
    return (array + (value * 64));
}

void print() {
    std::cout << "\nбитовая карта: ";
    for (int i = 0; i < 1024;) {
        if (*(array + i) == std::byte{2}) {
            std::cout << "1";
            i += 64;
        } else {
            std::cout << "0";
            i += 64;
        }
    }
    std::cout << "\n";
    int count = 0;
    int countempty = 0;
    int countfull = 0;
    for (int i = 0; i < 1024;) {
        if (*(array + i) == std::byte{2}) {
            std::cout << count << ": 1 адрес: " << (array + i) << std::endl;
            i += 64;
            count++;
            countfull++;
        } else {
            std::cout << count << ": 0 адрес: " << (array + i) << std::endl;
            i += 64;
            count++;
            countempty++;
        }
    }
    std::cout << "\n количество заполненых участков: " << countfull << "\n количество пустых участков: " << countempty
            << std::endl;
}
