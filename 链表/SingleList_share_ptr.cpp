#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <set>
#include <map>
#include <cstring>
#include <numeric>
#include <cmath>
#include <memory>
using namespace std;
template <typename __T>
class Node{
public:
    __T _data;
    shared_ptr<Node<__T>> _next;

public:
    // Node() = default;
    Node(__T data = 0, shared_ptr<Node<__T>> n = nullptr)
        :_data(data), _next(n){}
};

template <typename __T>
class SingleList{
private:
    shared_ptr<Node<__T>> phead;
    int count;

public:
    using pointer = shared_ptr<Node<__T>>;
public:
    SingleList():phead(make_shared<Node<__T>>()),count(0){}
    ~SingleList() = default;
    SingleList(const initializer_list<__T>& p);

    shared_ptr<Node<__T>> insert(int index, __T data);
    const int size() const { return count;}
    void push_back(const __T& data);
    shared_ptr<Node<__T>> getHead() const {return phead;}
};

template <typename __T>
void SingleList<__T>::push_back(const __T& data)
{
    pointer temp = phead;
    while(nullptr!=temp.get()->_next){

        temp = temp.get()->_next;
    }
    auto NewNode = make_shared<Node<__T>>(data);
    temp.get()->_next = NewNode;
    count++;
}

template <typename __T>
SingleList<__T>::SingleList(const initializer_list<__T>& p)
{
    count = 0;
    phead = make_shared<Node<__T>>();
    for(auto i:p)
        push_back(i);
}
int main()
{
    SingleList<int> slist = {1, 2, 3, 4, 5};
    cout << slist.size() << endl;
    SingleList<int>::pointer temp = slist.getHead();
    temp = temp.get()->_next;
    while(temp.get()->_next!=nullptr){
        cout << temp.get()->_data <<" ";
        temp = temp.get()->_next;
    }
    cout << temp.get()->_data<<endl;
    return 0;
}
