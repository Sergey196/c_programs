#include <iostream>
#include <bitset>
#include <thread>
#include <unistd.h>

// Обратите внимание, используя std::bitset, наши options соответствуют порядковым номерам бит, а не их значениям
const int option_1 = 0;
const int option_2 = 1;
const int option_3 = 2;
const int option_4 = 3;
const int option_5 = 4;
const int option_6 = 5;
const int option_7 = 6;
const int option_8 = 7;

int main()
{
    // Помните, что отсчет бит начинается не с 1, а с 0
    std::bitset<8> bits(0x2); // нам нужно 8 бит, начнем с битового шаблона 0000 0010
    //bits.set(option_5); // включаем 4-й бит - его значение изменится на 1 (теперь мы имеем 0001 0010)
   // bits.flip(option_6); // изменяем значения 5-го бита на противоположное (теперь мы имеем 0011 0010)
   // bits.reset(option_6); // выключаем 5-й бит - его значение снова 0 (теперь мы имеем 0001 0010)

    //std::cout << "Bit 4 has value: " << bits.test(option_5) << '\n';
    //std::cout << "Bit 5 has value: " << bits.test(option_6) << '\n';
    //std::cout << "All the bits: " << bits << '\n';

    std::thread([&] {
        bits.flip(option_6);
    }).detach();

    std::thread([&] {
       bits.flip(option_6);
    }).detach();

    sleep(1000);


    return 0;
}
