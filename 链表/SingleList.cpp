#include <iostream>
using namespace std;

template <typename __T>
class Node
{
public:
    __T _value;
    Node* _next;
public:
    Node() = default;
    Node(__T&& value, Node* next)
        :_value(value), _next(next){}
};

template <typename __T>
class SingleLink
{
public:
    using pointer = Node<__T>*;
    SingleLink();
    ~SingleLink();

    const int size() const;
    bool isEmpty() const;

    Node<__T>* insert(int index, __T&& t);  //在指定位置进行插入
    // Node<__T>* insertHead(__T t);
    // Node<__T>* insertTail(__T t);
    
    Node<__T>* del(int index);

    __T get(int index);

    Node<__T>* getHead();

private:
    int count;
    Node<__T>* phead;

    Node<__T>* getNode(int index) const;
};

// 默认构造函数
template <typename __T>
SingleLink<__T>::SingleLink()
:count(0), phead(nullptr)
{
    phead = new Node<__T>();
    phead->_next = nullptr;
}

//返回指定索引的前一个结点，若链表为空，返回头结点
template <typename __T>
Node<__T>* SingleLink<__T>::getNode(int index) const
{
    if(index>count||index<0)
        return nullptr;
    int temp = 0;
    Node<__T>* preNode = phead;
    while(temp<index){
        ++temp;
        preNode = preNode->_next;
    }
    return preNode;
}

//析构函数
template <typename __T>
SingleLink<__T>::~SingleLink()
{
    Node<__T>* tempNode = phead->_next;
    while(nullptr!=tempNode){
        Node<__T>* temp = tempNode;
        tempNode = tempNode->_next;
        delete temp;
    }
}

//返回链表的大小
template <typename __T>
const int SingleLink<__T>::size() const
{
    return count;
}

//判断链表是否为空
template <typename __T>
bool SingleLink<__T>::isEmpty() const
{
    return count==0;
}

//获取指定结点的数据
template <typename __T>
__T SingleLink<__T>::get(int index)
{
    if(index>count||index<0)
        throw runtime_error("index参数指定错误");
    Node<__T>* tempNode = getNode(index);
    return tempNode->_value;
}

//获取头结点
template <typename __T>
Node<__T>* SingleLink<__T>::getHead()
{
    return phead->_next;
}

//在指定位置插入新节点
template <typename __T>
Node<__T>* SingleLink<__T>::insert(int index, __T&& t)
{
    Node<__T>* preNode = getNode(index);
    if(preNode){
        Node<__T>* newNode = new Node<__T>(std::forward<__T>(t), preNode->_next);
        preNode->_next = newNode;
        ++count;
        return newNode;
    }
    return nullptr;
}

//删除链表指定位置元素
template <typename __T>
Node<__T>* SingleLink<__T>::del(int index)
{
    if(isEmpty()||index>count||index<0)
        return nullptr;
    Node<__T>* preNode = getNode(index);
    Node<__T>* delNode = preNode->_next;
    preNode->_next = delNode->_next;
    --count;
    delete delNode;
    return preNode->_next;
}
int main()
{
    SingleLink<int> lis;
    for(int i = 0; i<10;i++){
        lis.insert(i, std::move(i));
    }
    // SingleLink<int>::pointer ptr = lis.getHead();
    Node<int>* ptr = lis.getHead();
    while(nullptr!=ptr){
        cout << ptr->_value << " ";
        ptr = ptr->_next;
    }
    cout << endl;
    cout << lis.get(5) << endl;
    return 0;
}