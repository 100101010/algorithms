//
// Created by 帆桥 on 2019/5/15.
//

#ifndef CLIONCODE_TREE_HPP
#define CLIONCODE_TREE_HPP

#include "TreeNode.hpp"
#include <memory>
#include <queue>
#include <stack>
#include <queue>
template <typename T>
class Tree{
private:
    std::shared_ptr<TreeNode<T>> root;
    std::queue<std::shared_ptr<TreeNode<T>>> que; // 存储叶结点
    int NodeNumber = 0;
private:
    // 前序遍历
    void pre_traversal(std::shared_ptr<TreeNode<T>> Node){
        if (Node!= nullptr) {
            std::cout<<Node.get()->getData()<<" ";
            pre_traversal(Node.get()->getLeftNode());
            pre_traversal(Node.get()->getRightNode());
        }
    }

    //中序遍历
    void in_traversal(std::shared_ptr<TreeNode<T>> Node) {
        if (Node!= nullptr) {
            in_traversal(Node.get()->getLeftNode());
            std::cout<<Node.get()->getData()<<" ";
            in_traversal(Node.get()->getRightNode());
        }
    }

    // 后序遍历
    void end_traversal(std::shared_ptr<TreeNode<T>> Node) {
        if (Node!= nullptr) {
            end_traversal(Node.get()->getLeftNode());
            end_traversal(Node.get()->getRightNode());
            std::cout<<Node.get()->getData()<<" ";
        }
    }

    // 计算结点所在的层次
    int calculate(std::shared_ptr<TreeNode<T>> Node) {
        int count = 0;
        std::shared_ptr<TreeNode<T>> temp = Node.get()->getFatherNode();
        while (temp != nullptr){
            temp = temp.get()->getFatherNode();
            ++count;
        }
        return count;
    }

    // 中序非递归遍历
    void inOrderTraversal(std::shared_ptr<TreeNode<T>> Node) {
        std::shared_ptr<TreeNode<T>> temp = Node;
        std::stack<std::shared_ptr<TreeNode<T>>> sta;
        while (temp!= nullptr || !sta.empty()) {
            while(temp!= nullptr) {
                sta.push(temp);
                temp = temp.get()->getLeftNode();
            }
            if (!sta.empty()) {
                temp = sta.top();
                sta.pop();
                std::cout<<temp.get()->getData()<<" ";
                temp = temp.get()->getRightNode();
            }
        }
        std::cout<<std::endl;
    }

    // 前序非递归遍历
    void preOrderTraversal(std::shared_ptr<TreeNode<T>> Node) {
        std::shared_ptr<TreeNode<T>> temp = Node;
        std::stack<std::shared_ptr<TreeNode<T>>> sta;
        while (temp!= nullptr || !sta.empty()) {
            while(temp!= nullptr) {
                sta.push(temp);
                std::cout<<temp.get()->getData()<<" ";
                temp = temp.get()->getLeftNode();
            }
            if (!sta.empty()) {
                temp = sta.top();
                sta.pop();
                temp = temp.get()->getRightNode();
            }
        }
        std::cout<<std::endl;
    }

    // 后序非递归遍历
    void postOrderTraversal(std::shared_ptr<TreeNode<T>> Node) {
        std::shared_ptr<TreeNode<T>> temp = Node, cur, pre = nullptr;
        // cur记录当前访问结点，pre记录前一次访问结点
        std::stack<std::shared_ptr<TreeNode<T>>> sta;
        sta.push(temp);
        while (!sta.empty()) {
            cur = sta.top();
            if ((cur.get()->getLeftNode() == nullptr && cur.get()->getRightNode() == nullptr)
                || (pre!= nullptr && (pre == cur.get()->getLeftNode()|| pre == cur.get()->getRightNode()))) {
                std::cout<<cur.get()->getData()<<" ";
                sta.pop();
                pre = cur;
            }
            else {
                if (cur.get()->getRightNode()!= nullptr)
                    sta.push(cur.get()->getRightNode());
                if (cur.get()->getLeftNode()!= nullptr)
                    sta.push(cur.get()->getLeftNode());
            }
        }
        std::cout<<std::endl;
    }

    // 层次遍历
    void levelOrderTraversal(std::shared_ptr<TreeNode<T>> Node) {
        std::queue<std::shared_ptr<TreeNode<T>>> tempque;
        std::shared_ptr<TreeNode<T>> temp = Node, cur;
        if (temp == nullptr)
            return;
        tempque.push(temp);
        while (!tempque.empty()) {
            cur = tempque.front();
            tempque.pop();
            std::cout<<cur.get()->getData()<<" ";
            if (cur.get()->getLeftNode()!= nullptr)
                tempque.push(cur.get()->getLeftNode());
            if (cur.get()->getRightNode()!= nullptr)
                tempque.push(cur.get()->getRightNode());
        }
        std::cout<<std::endl;
    }

    // 复制树
    void CopyTree(std::shared_ptr<TreeNode<T>> &tempRoot,std::shared_ptr<TreeNode<T>> Node) {
        if (Node == nullptr)
            return;
        else {
            tempRoot = std::make_shared<TreeNode<T>>(Node.get()->getFatherNode(), Node.get()->getData());
            CopyTree(tempRoot.get()->getLeftNode(), Node.get()->getLeftNode());
            CopyTree(tempRoot.get()->getRightNode(), Node.get()->getRightNode());
        }
    }

    // 计算结点的度
    int calNodeDegree(std::shared_ptr<TreeNode<T>> Node) {
        int degree = 0;
        degree += (Node.get()->getLeftNode() == nullptr?0:1);
        degree += (Node.get()->getRightNode() == nullptr?0:1);
        degree += (Node.get()->getFatherNode() == nullptr?0:1);
        return degree;
    }

    // 寻找父亲结点和左右儿子结点
    using fatherAndbrother = std::tuple<std::shared_ptr<TreeNode<T>>, std::shared_ptr<TreeNode<T>>, std::shared_ptr<TreeNode<T>>>;
    fatherAndbrother findFAB(std::shared_ptr<TreeNode<T>> Node) {
        return std::make_tuple(Node.get()->getFatherNode(), Node.get()->getLeftNode(), Node.get()->getRightNode());
    }

    void showTree(std::shared_ptr<TreeNode<T>> Node) {
        std::queue<std::pair<std::shared_ptr<TreeNode<T>>, int>> tempque;
        std::shared_ptr<TreeNode<T>> temp = Node;
        std::pair<std::shared_ptr<TreeNode<T>>, int> cur;
        if (temp == nullptr)
            return;
        int index = 1; // 记录行数
        tempque.push({temp, 1});
        while (!tempque.empty()) {
            cur = tempque.front();
            tempque.pop();
            if (cur.second != index){
                std::cout<<std::endl;
                ++index;
            }
            std::cout<<cur.first.get()->getData()<<" ";
            if (cur.first.get()->getLeftNode()!= nullptr)
                tempque.push({cur.first.get()->getLeftNode(), cur.second+1});
            if (cur.first.get()->getRightNode()!= nullptr)
                tempque.push({cur.first.get()->getRightNode(), cur.second+1});
        }
        std::cout<<std::endl;
    }

public:
    Tree() {
        root = nullptr;
    }

    Tree(std::initializer_list<T> L) {
        std::vector<T> Tlist(L);
        root = std::make_shared<TreeNode<T>>(nullptr, Tlist[0]);
        que.push(root);
        for (int i = 1; i < Tlist.size()/2; ++i) {
            // 构造左右子节点
            std::shared_ptr<TreeNode<T>> fatherNode = que.front();
            que.pop();
            std::shared_ptr<TreeNode<T>> newLeftNode = std::make_shared<TreeNode<T>>(fatherNode, Tlist[2*i-1]);
            std::shared_ptr<TreeNode<T>> newRightNode = std::make_shared<TreeNode<T>>(fatherNode, Tlist[2*i]);

            // 将左右子节点连接上父亲结点
            fatherNode.get()->setLeftNode(newLeftNode);
            fatherNode.get()->setRightNode(newRightNode);

            // 将新节点加入队列中
            que.push(newLeftNode);
            que.push(newRightNode);
        }
        if (Tlist.size()%2==0){
            std::shared_ptr<TreeNode<T>> fatherNode = que.front();
            std::shared_ptr<TreeNode<T>> newLeftNode = std::make_shared<TreeNode<T>>(fatherNode, Tlist[Tlist.size()-1]);
            fatherNode.get()->setLeftNode(newLeftNode);
            que.push(newLeftNode);
        }
        NodeNumber += Tlist.size();
    }

    /*void test() {
        if (root.get()->getData() == 1) {
            std::cout<<"ss"<<std::endl;
        }
    }*/

    void pre_traversal() {
        std::cout<<"前序遍历:";
        pre_traversal(root);
        std::cout<<std::endl;
    }

    void in_traversal() {
        std::cout<<"中序遍历:";
        in_traversal(root);
        std::cout<<std::endl;
    }

    void end_traversal() {
        std::cout<<"后序遍历:";
        end_traversal(root);
        std::cout<<std::endl;
    }

    // 计算二叉树的高度
    int high() {
        int hight = 1;
        std::shared_ptr<TreeNode<T>> temp = root.get()->getLeftNode();
        while(temp!= nullptr) {
            temp = temp.get()->getLeftNode();
            ++hight;
        }
        return hight;
    }

    int statistic() {
        int leafNumber = que.size();
        std::shared_ptr<TreeNode<T>> temp = que.front();
        if (temp.get()->getLeftNode()!= nullptr)
            --leafNumber;
        std::cout<<"结点数量:"<<NodeNumber<<std::endl;
        std::cout<<"叶节点数量:"<<leafNumber<<std::endl;
    }

    void inOrderTraversal() {
        std::cout<<"中序非递归遍历:";
        inOrderTraversal(root);
    }

    void preOrderTraversal() {
        std::cout<<"前序非递归遍历:";
        pre_traversal(root);
    }

    void postOrderTraversal() {
        std::cout<<"后序非递归遍历:";
        postOrderTraversal(root);
    }

    void levelOrderTraversal() {
        std::cout<<"层次遍历:";
        levelOrderTraversal(root);
    }

    void showTree() {
        showTree(root);
    }

    void operator=(std::shared_ptr<TreeNode<T>> Node){
        CopyTree(root, Node);
    }
};
#endif //CLIONCODE_TREE_HPP
