//
// Created by 帆桥 on 2019/4/15.
//

#ifndef CLIONCODE_LINKEDLIST_H
#define CLIONCODE_LINKEDLIST_H
#include <memory>
template <typename T>
struct Node{
    T _data;
    std::shared_ptr<Node<T>> _next;

    Node(std::shared_ptr<Node<T>> next = nullptr):
            _next(next){}
    Node(T data, std::shared_ptr<Node<T>> next = nullptr):
            _data(data), _next(next){}
};

template <typename T>
class LinkedList{
private:
    std::shared_ptr<Node<T>> head;
    unsigned count;

public:
    LinkedList(){
        head = std::make_shared<Node<T>>(nullptr);
        count = 0;
    }

    void pop() {
        auto delNode = head.get()->_next;
        head.get()->_next = delNode.get()->_next;
        --count;
    }

    T top() {
        auto frontNode = head.get()->_next;
        return frontNode.get()->_data;
    }

    unsigned int size() const {
        return count;
    }

    void push(T data) {
        auto newNode = std::make_shared<Node<T>>(data, nullptr);
        auto temp = head;
        newNode.get()->_next = temp.get()->_next;
        head.get()->_next = newNode;
        ++count;
    }
};
#endif //CLIONCODE_LINKEDLIST_H
