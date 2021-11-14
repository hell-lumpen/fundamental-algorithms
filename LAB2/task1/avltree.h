//
// Created by Maxim on 14.11.2021.
//

//
// implementation of a class balanced AVL tree inherited from template class Binary Tree
// available operation:
// insert node
// delete node
// find node
//
// tree traversal options:
// prefix
// postfix
// infix
//

#ifndef TASK1_AVLTREE_H
#define TASK1_AVLTREE_H

template <class T1, class T2>
class AVLTree : public BinaryTree<T1, T2> {
private:
    class Node : public BinaryTree<T1, T2>::Node {
    public:
        int height;
        explicit Node() : BinaryTree<T1, T2>::Node() {
            height = 0;
        }
        int getBalance() const {
            int h_left, h_right;
            if (static_cast<typename AVLTree<T1, T2>::Node *>(this->p_right) == nullptr)
                h_right = 0;

            if (static_cast<typename AVLTree<T1, T2>::Node *>(this->p_left) == nullptr)
                h_left = 0;

            if (static_cast<typename AVLTree<T1, T2>::Node *>(this->p_right))
                h_right = static_cast<typename AVLTree<T1, T2>::Node *>(this->p_right)->height + 1;

            if (static_cast<typename AVLTree<T1, T2>::Node *>(this->p_left))
                h_left = static_cast<typename AVLTree<T1, T2>::Node *>(this->p_left)->height + 1;

            return h_left - h_right;
        }
        virtual ~Node() = default;
    };

    void _small_right(Node* node, Node* parent_node) {
        enum {left, right} side;

        if (parent_node != nullptr && parent_node->p_left == node)
            side = left;
        else
            side = right;

        auto temp = static_cast<typename AVLTree<T1, T2>::Node*> (node->p_left);
        node->p_left = static_cast<typename AVLTree<T1, T2>::Node*> (temp->p_right);
        temp->p_right= static_cast<typename AVLTree<T1, T2>::Node*> (node);
        temp->height += 1;
        static_cast<typename AVLTree<T1, T2>::Node*> (temp->p_right)->height -= 1;

        if (parent_node == nullptr)
            this->root = temp;
        else if (side == left)
            parent_node->p_left = temp;
        else
            parent_node->p_right = temp;
    }

    void _small_left(Node* node, Node* parent_node) {
        enum {left, right} side;

        if (parent_node != nullptr && parent_node->p_left == node)
            side = left;
        else
            side = right;

        auto temp = static_cast<typename AVLTree<T1, T2>::Node*> (node->p_right);
        node->p_right = static_cast<typename AVLTree<T1, T2>::Node*> (temp->p_left);
        temp->p_left = static_cast<typename AVLTree<T1, T2>::Node*> (node);
        temp->height += 1;
        static_cast<typename AVLTree<T1, T2>::Node*> (temp->p_left)->height -= 1;

        if (parent_node == nullptr)
            this->root = temp;
        else if (side == left)
            parent_node->p_left = temp;
        else
            parent_node->p_right = temp;
    }

    void _balance(typename BinaryTree<T1, T2>::Node* node) override {

        auto pNode = static_cast<typename AVLTree<T1, T2>::Node*>(node);
        auto current_node = static_cast<typename AVLTree<T1, T2>::Node*>(this->root);
        std::stack<Node*> stack;
        int height = 0;

        if(!current_node)
            throw TreeException("ERROR: m_key not found (it may have been previously deleted)");

        while (current_node != nullptr) {
            if (this->comparator->compare(current_node->m_key, pNode->m_key) == 0) {
                stack.push(current_node);
                break;
            }
            if (this->comparator->compare(current_node->m_key, pNode->m_key) == 1) {
                stack.push(current_node);
                current_node = static_cast<typename AVLTree<T1, T2>::Node*>(current_node->p_left);
            }
            if (this->comparator->compare(current_node->m_key, pNode->m_key) == -1) {
                stack.push(current_node);
                current_node = static_cast<typename AVLTree<T1, T2>::Node*>(current_node->p_right);
            }
        }

        int balance_factor;
        Node* tmp1;

        while (!stack.empty()) {
            tmp1 = stack.top();
            stack.pop();

            tmp1->height = height++;

            balance_factor = tmp1->getBalance();

            //std::cout << "key:" << tmp1->m_key << " (height left:" << h_left << " height right:" << h_right
            //        << ") height:" << tmp1->height << " factor:" << balance_factor << std::endl;

            if (balance_factor != -1 && balance_factor != 0 && balance_factor != 1)
                break;
        }

        AVLTree<T1, T2>::Node* parent = nullptr;
        if (!stack.empty())
            parent = stack.top();

        if (balance_factor == 2) {
            if (static_cast<typename AVLTree<T1, T2>::Node*>(tmp1->p_left)->getBalance() == -1) {
                _small_left(static_cast<typename AVLTree<T1, T2>::Node *>(tmp1->p_left), tmp1);
            }
            _small_right(tmp1, parent);

        } else if (balance_factor == -2) {
            if (static_cast<typename AVLTree<T1, T2>::Node*>(tmp1->p_right)->getBalance() == 1) {
                _small_right(static_cast<typename AVLTree<T1, T2>::Node *>(tmp1->p_right), tmp1);
            }
            _small_left(tmp1, parent);
        }
//        while (!stack_tmp.empty()) {
//            stack_tmp.top()->height = stack_tmp.top()->updateHeight();
//            std::cout << "******\n" << stack_tmp.top()->m_key << " " << stack_tmp.top()->height << std::endl;
//            stack_tmp.pop();
//        }

    }

public:
    explicit AVLTree(const Comparator <T1>* _comparator) : BinaryTree<T1, T2>(_comparator){}
    ~AVLTree() = default;

};

#endif //TASK1_AVLTREE_H
