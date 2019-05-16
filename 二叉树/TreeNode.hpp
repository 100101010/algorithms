//
// Created by 帆桥 on 2019/5/15.
//

#ifndef CLIONCODE_TREENODE_HPP
#define CLIONCODE_TREENODE_HPP

#include <memory>
template <typename T>
class TreeNode{
private:
    std::shared_ptr<TreeNode> leftNode;
    std::shared_ptr<TreeNode> rightNode;
    std::shared_ptr<TreeNode> fatherNode;
    T data;
public:
    TreeNode() {
        leftNode = nullptr;
        rightNode = nullptr;
        fatherNode = nullptr;
    }

    void setLeftNode(std::shared_ptr<TreeNode<T>> leftNode) {
        this->leftNode = leftNode;
    }

    void setRightNode(std::shared_ptr<TreeNode<T>> RightNode) {
        this->rightNode = RightNode;
    }

    const std::shared_ptr<TreeNode<T>> &getFatherNode() {
        return fatherNode;
    }

    T getData() {
        return data;
    }

    const std::shared_ptr<TreeNode> &getLeftNode() const {
        return leftNode;
    }

    const std::shared_ptr<TreeNode> &getRightNode() const {
        return rightNode;
    }

    TreeNode(const std::shared_ptr<TreeNode> &fatherNode) : fatherNode(fatherNode) {}

    TreeNode(const std::shared_ptr<TreeNode> &fatherNode, T data) : fatherNode(fatherNode), data(data) {
        leftNode = nullptr;
        rightNode = nullptr;
    }
};
#endif //CLIONCODE_TREENODE_HPP
