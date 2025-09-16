#include <iostream>
#include <cstddef>
std::byte *array = new std::byte[1024];

void push(int &count) {
    int replays = (count+64-1)/64;
    int free=0;
    int upfree=0;
    int fullfree=0;
    int freenuls=0;
    std::byte *address;

    for (int i = 0; i < 1024; i++)
    {
        if (*(array+i)==std::byte{0})
        {
                fullfree++;
                free++;
        }
        if (i==1023 || *(array+i)==std::byte {2} ){
                if(free>upfree) {
                    upfree=free;
                    free=0;
                }
        }
    }
    std::cout << fullfree << std::endl;
    std::cout << upfree << std::endl;
    if (replays>upfree/64) std::cout << "не хватает памяти";
    else{
            for (int g = 0; g < 1024; g++) {
                if (*(array+g)==std::byte {0}) {
                    freenuls++;
                }
                else freenuls=0;
                if (freenuls==replays*64) {
                    address = (array+(g-freenuls+1));
                    for (int j = 0; j < replays; j++) {
                        std::cout <<"адрес выделенного участка: "<< (address) << std::endl;
                        for (int i = 0; i < 64; i++) {
                            if (i==0) *(address+i)=std::byte{2};
                            else *(address+i)=std::byte{1};
                        }
                        address = (address+64);
                    }
                    break;
                }
            }
        }


    }
void deleter(std::byte *address)
{
    for (int i = 0; i < 64; i++) *(address+i)=std::byte{0};
}
std::byte* deleterprint() {
    int count = 0;
    int value =0;
    for (int i = 0; i < 1024;) {
        if (*(array+i)==std::byte{2}) {

            std::cout<<count << ": 1 адрес: " << (array+i) << std::endl;
            i+=64;
            count++;

        }
        else {
            std::cout<<count <<": 0" <<std::endl;
            i+=64;
            count++;
        }
    }
    std::cin >> value;
    std::cout << "вы выбрали:"<< (array+(value*64)) << std::endl;
    return (array+(value*64));
}
void print() {
    for (int i = 0; i < 1024;) {

        if (*(array+i)==std::byte{2}) {
            std::cout<<"1";
            i+=64;

        }
        else {
            std::cout<<"0";
            i+=64;
        }
    }
}
int main() {
    while (true) {
        std::string a;
        int count = 0;
        std::cout << "\n";
        std::cin >> a;
        if (a == "1") {
            std::cin >> count;
            push(count);

        }
        if (a == "2") {
            print();
        }
        if (a == "3")
        {
            deleter(deleterprint());
        }
    }
}