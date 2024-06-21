#include <iostream>

class Virtual
{
   public:
      virtual ~Virtual() { std::cout << "TEST Destroy Virtual" << std::endl; } 
      virtual void run() = 0;
};

class A: public Virtual
{
   public:
      ~A() { std::cout << "TEST Destroy A" << std::endl; }  
      void run() override { std::cout << "TEST A" << std::endl; }
};

class B: public Virtual
{
   public:
      ~B() { std::cout << "TEST Destroy B" << std::endl; system("rm -r FILE"); }  
      void run() override { std::cout << "TEST B" << std::endl; }
};

int main()
{
   Virtual *arr[2];  
   arr[0] = new A();
   arr[1] = new B();
   
   arr[0]->run();
   arr[1]->run();
   
   delete arr[0];
   delete arr[1];
}
