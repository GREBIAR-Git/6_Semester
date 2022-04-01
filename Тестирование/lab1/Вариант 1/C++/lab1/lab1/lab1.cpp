#include <iostream>

int main()
{
    std::cout << "X = ";
    
    int number;
    std::string result;
    
    std::cin >> number;
    
    while (number > 0)
    {
        result += (number % 10) + 48;
        number = number / 10;
    }
    
    for (int i = result.length() - 1; i >= 0; i--)
    {
        std::cout << result[i] << std::endl;
    }

    system("pause");
    return 0;
}
