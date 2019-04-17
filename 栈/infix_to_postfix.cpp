#include <iostream>
#include <stack>
#include <map>
#include <functional>
#include <sstream>
using namespace std;
stack<char> op;
stack<int> number;
map<char, int> icp;
map<char, function<int(int, int)>> cal;
map<char, string> ops;

void init() {
    // 初始化各操作符的优先级
    icp['#'] = 0;
    icp['+'] = icp['-'] = 2;
    icp['*'] = icp['/'] = icp['%'] = 3;
    icp['('] = 1;

    // 封装操作符和对应的函数
    cal['+'] = std::plus<int>();
    cal['-'] = std::minus<int>();
    cal['*'] = std::multiplies<int>();
    cal['/'] = std::divides<int>();
    cal['%'] = std::modulus<int>();

    op.push('#');

    ops['+'] = "+";
    ops['-'] = "-";
    ops['*'] = "*";
    ops['/'] = "/";
    ops['%'] = "%";
}
// trim函数去掉中缀表达式多余空格
void trim(string &s) {
     int index = 0;
     if (!s.empty()) {
         while ((index = s.find(' ', index)) != string::npos) {
             s.erase(index,1);
         }
     }
}

void calculate(char oper) {
    int number1 = number.top();number.pop();
    int number2 = number.top();number.pop();
    number.push(cal[oper](number2, number1));
}

int main()
{
    string string1, postfix = "";
    getline(cin, string1);
    trim(string1);
    init();
    int a;
    for (int i = 0; i < string1.length(); ++i) {
        if (isdigit(string1[i])){
            istringstream is(string1.substr(i));
            is>>a;
            i += to_string(a).length() - 1;
            number.push(a);
            postfix.append(to_string(a)+" ");
        }
        else{
            if (string1[i] == '(')
                op.push('(');
            else if (string1[i] == ')'){
                while(op.top()!='('){
                    calculate(op.top());
                    postfix.append(ops[op.top()]+" ");
                    op.pop();
                }
                op.pop();// 将(弹出
            }
            else{
                char topOP = op.top();
                if (icp[topOP] < icp[string1[i]]) // 如果优先级大于栈顶操作符，则把它压栈
                    op.push(string1[i]);
                else{
                    while(icp[string1[i]] <= icp[topOP]) { // 若优先级小于等于栈顶操作符
                        calculate(topOP);
                        postfix.append(ops[topOP]+" ");
                        op.pop();
                        topOP = op.top();
                    }
                    op.push(string1[i]);
                }
            }
        }
    }
    while(op.top() != '#'){
        calculate(op.top());
        postfix.append(ops[op.top()]+" ");
        op.pop();
    }
    cout<<postfix<<endl;
    cout<<"result="<<number.top()<<endl;
    return 0;
}