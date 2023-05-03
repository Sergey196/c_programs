#include <inttypes.h>
#include <iostream>

class uint24_t {
   private:
      uint16_t lo16;
      uint8_t hi8;
   public:
      uint24_t operator=(uint32_t const value);
      uint32_t getAddr();
      operator uint32_t();
};

uint24_t uint24_t::operator=(uint32_t const value) {
    lo16 = value & 0xFFFF;
    hi8 = (value >> 16) & 0xFF;
    return *this;
}

uint24_t::operator uint32_t() { return lo16 + hi8; }

uint32_t uint24_t::getAddr() {
    return lo16 + (hi8 << 16);
}

int main()
{
    uint24_t a;
    uint32_t b = 0xFF;
    uint32_t c = 0;
    a = b;
    c = a;
    std::cout << "TEST = " << (int)c << std::endl;
    return 0;
}
