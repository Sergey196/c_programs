#include <iostream>
#include <unordered_map>

int main()
{
   std::string text = "Huffman coding is a data compression algorithm."; 
   std::unordered_map<char, int> freq;
   for (char ch: text) {
      freq[ch]++;
   }
   
   for (auto& it: freq) {
       std::cout << "TEST key = " << it.first << " val = " << it.second << std::endl;
   }
   
   return 0; 
}
