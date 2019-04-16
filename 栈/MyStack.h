//
// Created by 帆桥 on 2019/4/15.
//

#ifndef CLIONCODE_MYSTACK_H
#define CLIONCODE_MYSTACK_H

#include "LinkedList.h"
template <typename T>
class Stack{
private:
    LinkedList<T> link;

public:
    Stack() = default;
    void push(T data) {
        link.push(data);
    }

    bool isEmpty() {
        return (link.size() == 0);
    }

    unsigned int size() {
        return link.size();
    }

    void pop() {
        if (size() == 0)
            throw std::runtime_error("size is 0, can not pop");
        else
            link.pop();
    }

    T top() {
        if (size() == 0)
            throw std::runtime_error("size is 0, can not pop");
        else
            return link.top();
    }
};
#endif //CLIONCODE_MYSTACK_H
