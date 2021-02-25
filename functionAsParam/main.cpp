#include <iostream>
#include <cstdarg>
#include <functional>

using namespace std::placeholders;

class A
{
   public:
      static void simple_printf(const char* fmt...) // C-style "const char* fmt, ..." is also valid
      {
          va_list args;
          va_start(args, fmt);
       
          while (*fmt != '\0') {
              if (*fmt == 'd') {
                  int i = va_arg(args, int);
                  std::cout << i << '\n';
              } else if (*fmt == 'c') {
                  // note automatic conversion to integral type
                  int c = va_arg(args, int);
                  std::cout << static_cast<char>(c) << '\n';
              } else if (*fmt == 'f') {
                  double d = va_arg(args, double);
                  std::cout << d << '\n';
              }
              ++fmt;
          }
       
          va_end(args);
      }
};
class B
{
   public:
      template <typename FuncType> 
      void funcForFunc(FuncType func)  
      {
          for (int ctr = 0 ; ctr < 5 ; ctr++) 
          {
             func("dcff", 3, 'a', 1.999, 42.5);
          }
      }
};

int main ()
{  
    B beee;
    beee.funcForFunc([&](const char* fmt...) 
    {
       va_list args;
       va_start(args, fmt);
       
       while (*fmt != '\0') {
           if (*fmt == 'd') {
               int i = va_arg(args, int);
               std::cout << i << '\n';
           } else if (*fmt == 'c') {
               // note automatic conversion to integral type
               int c = va_arg(args, int);
               std::cout << static_cast<char>(c) << '\n';
           } else if (*fmt == 'f') {
               double d = va_arg(args, double);
               std::cout << d << '\n';
           }
           ++fmt;
       }
    });
    
    beee.funcForFunc(&A::simple_printf); 
    
   return 0;
}; 
