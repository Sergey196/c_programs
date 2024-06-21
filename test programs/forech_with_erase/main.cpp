#include <iostream>
#include <vector>
#include <algorithm>
 
int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
 
    for(auto it = v.begin(); it != v.end();)
    {
        // remove odd numbers
        if ((*it == 2) || (*it == 5))
        {
            // `erase()` invalidates the iterator, use returned iterator
            it = v.erase(it);
        }
        // Notice that the iterator is incremented only on the else part (why?)
        else {
            ++it;
        }
    }
 
    for (int const &i: v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
 
    return 0;
} 
