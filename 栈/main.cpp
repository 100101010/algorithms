#include <iostream>
#include "MyStack.h"
int main()
{
    Stack<int> sta;
    sta.push(1);
    sta.push(2);
    sta.push(3);
    std::cout << sta.top() << std::endl;
    sta.pop();
    std::cout << sta.size() << std::endl;
    Stack<char> sta1;
    std::string str = "abcde";
    for (int i = 0; i < str.length(); ++i) {
        sta1.push(str[i]);
    }
    for (int j = 0; j < 5; ++j) {
        std::cout << sta1.top();
        sta1.pop();
    }
    std::cout << std::endl;
    std::string str1 = "(((()))";
    Stack<char> sta2;
    for (int k = 0; k < str1.length(); ++k) {
        if (str1[k] == ')' && !sta2.isEmpty())
            sta2.pop();
        if (str1[k] == '(')
            sta2.push('(');
    }
    if (sta2.isEmpty())
        std::cout << "successful" << std::endl;
    else
        std::cout << "fail" << std::endl;
    return 0;
}