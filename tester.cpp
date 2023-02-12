#include <iostream>


int main()
{
    // t_time &time
    int num;
    std::cout << "enter number" << std::endl;
    std::cin >> num;
    srand(time(0));
    while (num)
    {
        std::cout << rand() % 100 << ' ';
        num--;
    }
}