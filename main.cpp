#include <iostream>
#include <cstddef>
std::byte *array = new std::byte[1024];

void push(int &count) {
    int replays = (count+64-1)/64;
    for (int k = 0; k < replays; k++) {
        for (int i = 0; i < 1024; ++i) {
            if (*(array+i)==std::byte{0}) {
                for (int j = i; j < i+64; ++j)
                {
                    if (j==i) *(array+i)=std::byte{2};
                    else *(array+j)=std::byte{1};
                }
                break;
            }
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
    }
}