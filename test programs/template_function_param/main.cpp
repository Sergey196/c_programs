// non-type (function pointer) template parameter
#include <iostream>
void add(int i, int j)
{
   std::cout << "TEST1 = " << i << std::endl; 
   std::cout << "TEST2 = " << j << std::endl; 
}

template<void op(int, int)>
void do_op(int i, int j) { op(i, j); }




int main()
{
   int i = 1;
   int j = 2;
   do_op<&add>(i, j); // still need address-of operator in the function pointer case.
   return 0; 
}
