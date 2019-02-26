
// 双向循环链表

#include <iostream>
#include <memory>
using namespace std;
template <typename __T>
struct Node
{
public:
    __T _value;
    Node<__T>* pre_ptr;
    Node<__T>* next_ptr;

    Node() = default;
    Node(__T value, Node<__T>* prePtr, Node<__T>* nexPtr)
        :_value(value), pre_ptr(prePtr), next_ptr(nexPtr){}

};
template <typename __T>
class doubleCircleList{
private:
    Node<__T>* phead;
    int count;

public:
    using pointer = Node<__T>*;

    doubleCircleList();
    ~doubleCircleList() = default;

public:
    Node<__T>* insert(int index, __T value);
    Node<__T>* insert_front(__T value);
    Node<__T>* insert_last(__T value);

    Node<__T>* del(int index);
    Node<__T>* del_front();
    Node<__T>* del_last();

    bool isEmpty() const {return count == 0;};
    int size() const {return count;};

    __T get_node_value(int index);
    __T get_front_value();
    __T get_last_value();
    Node<__T>* getHead();

private:
    Node<__T>* getNode(int index);
};

template <typename __T>
doubleCircleList<__T>::doubleCircleList()
{
    phead = new Node<__T>(0, nullptr, nullptr);
    phead->pre_ptr = phead;
    phead->next_ptr = phead;
    count = 0;
}

template <typename __T>
Node<__T>* doubleCircleList<__T>::getHead()
{
    return phead;
}

template <typename __T>
Node<__T>* doubleCircleList<__T>::getNode(int index)
{
    if(index >= count || index < 0)
        return nullptr;
    if(index <= count/2){
        Node<__T>* temp = phead->next_ptr;
        while(index--)
            temp = temp->next_ptr;
        return temp;
    }
    index = count - index - 1;
    Node<__T>* temp  = phead->pre_ptr;
    while(index--)
        temp = temp->pre_ptr;
    return temp;
}

template <typename __T>
Node<__T>* doubleCircleList<__T>::insert_last(__T value)
{
    Node<__T>* NewNode = new Node<__T>(value, phead->pre_ptr, phead);
    phead->pre_ptr->next_ptr = NewNode;
    phead->pre_ptr = NewNode;
    count++;
    return NewNode;
}

template <typename __T>
Node<__T>* doubleCircleList<__T>::insert_front(__T value)
{
    Node<__T>* NewNode = new Node<__T>(value, phead, phead->next_ptr);
    phead->next_ptr->pre_ptr = NewNode;
    phead->next_ptr = NewNode;
    count++;
    return NewNode;
}

template <typename __T>
Node<__T>* doubleCircleList<__T>::insert(int index, __T value)
{
    if(index == 0)
        return insert_front(value);
    else{
        Node<__T>* temp = getNode(index);
        if(temp == nullptr)
            return nullptr;
        Node<__T>* NewNode = new Node<__T>(value, temp->pre_ptr, temp);
        temp->pre_ptr->next_ptr = NewNode;
        temp->pre_ptr = NewNode;
        count++;
        cout << "sb" << endl;
        return NewNode;
    }
}

template <typename __T>
Node<__T>* doubleCircleList<__T>::del_front()
{
    if(count == 0)
        return nullptr;
    Node<__T>* temp = phead->next_ptr;
    phead->next_ptr = temp->next_ptr;
    temp->next_ptr->pre_ptr = phead;
    delete temp;
    count--;
    return phead->next_ptr;
}

template <typename __T>
Node<__T>* doubleCircleList<__T>::del_last()
{
    if(count == 0)
        return nullptr;
    Node<__T>* temp = phead->pre_ptr;
    temp->pre_ptr->next_ptr = phead;
    phead->pre_ptr = temp->pre_ptr;
    delete temp;
    count--;
    return phead->pre_ptr;
}

template <typename __T>
Node<__T>* doubleCircleList<__T>::del(int index)
{
    if(index == 0)
        return del_front();
    else if(index == count - 1)
        return del_last();
    else if(index >= count)
        return nullptr;
    Node<__T>* temp = getNode(index);
    temp->pre_ptr->next_ptr = temp->next_ptr;
    temp->next_ptr->pre_ptr = temp->pre_ptr;

    Node<__T>* ptemp = temp->pre_ptr;
    delete temp;
    count--;
    return ptemp;
}

template <typename __T>
__T doubleCircleList<__T>::get_front_value()
{
    return phead->next_ptr->_value;
}

template <typename __T>
__T doubleCircleList<__T>::get_last_value()
{
    return phead->pre_ptr->_value;
}

template <typename __T>
__T doubleCircleList<__T>::get_node_value(int index)
{
    Node<__T>* temp = getNode(index);
    if(temp==nullptr)
        throw runtime_error("index下标错误!");
    else
        return temp->_value;
}
int main()
{
    doubleCircleList<int> dlink;
    for(int i = 0; i <= 10; i++){
        dlink.insert(0, i);
    }
    cout << dlink.size() << endl;
    doubleCircleList<int>::pointer ptr = dlink.getHead();
    ptr = ptr->next_ptr;
    while(ptr!=dlink.getHead()){
        cout << ptr->_value << " ";
        ptr = ptr->next_ptr;
    }
    return 0;
}