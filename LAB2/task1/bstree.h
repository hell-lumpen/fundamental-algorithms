//
// Created by Maxim on 14.11.2021.
//

//
// implementation of a class binary search tree inherited from template class Associate Container
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

#ifndef TASK1_BSTREE_H
#define TASK1_BSTREE_H

#include <iostream>
#include <utility>
#include <stack>

template <class T1, class T2>
class BinaryTree : public AssociateContainer<T1, T2> {

protected:

    class Node : public AssociateContainer<T1, T2> :: Node {
    public:
        T1 m_key;
        T2 m_value;
        Node* p_left;
        Node* p_right;
        explicit Node(Node* left = nullptr, Node* right = nullptr) {
            p_left = left;
            p_right = right;
        }
        virtual ~Node() = default;
    };

    Node* root;

    const Comparator<T1> *comparator;

    Node* _find(const T1 &key) const {
        Node* current_node = root;
        while (current_node != nullptr) {
            if (comparator->compare(current_node->m_key, key) == 0) { // нашли нужный ключ
                return current_node;
            }
            if (comparator->compare(current_node->m_key, key) == 1) { // текущий больше переданого
                current_node = current_node->p_left;
            }
            if (comparator->compare(current_node->m_key, key) == -1) { // текущий меньше переданого
                current_node = current_node->p_right;
            }
        }
        throw TreeException("ERROR: m_key not found (it may have been previously deleted)");
    }

    Node* _insert(const T1 &key, const T2 &value) {
        auto current_node = &root;
        while (*current_node != nullptr) {

            if (comparator->compare((*current_node)->m_key, key) == 0) {
                throw TreeException("ERROR: Such an element already exists. You can't add it");
            }

            if (comparator->compare((*current_node)->m_key, key) == 1) {
                current_node = &((*current_node)->p_left);
                continue;
            }

            if (comparator->compare((*current_node)->m_key, key) == -1) {
                current_node = &((*current_node)->p_right);
                continue;
            }
        }

        *current_node = new Node;
        (*current_node)->m_key = key;
        (*current_node)->m_value = value;
        return (*current_node);
    }

    Node* _remove(const T1 &key) {
        auto current_node = root;
        auto parent_node = (Node*) nullptr;
        while (current_node != nullptr) {
            if (comparator->compare(current_node->m_key, key) == 0) {
                break;
            }
            if (comparator->compare(current_node->m_key, key) == 1) {
                parent_node = current_node;
                current_node = current_node->p_left;
                continue;
            }
            if (comparator->compare(current_node->m_key, key) == -1) {
                parent_node = current_node;
                current_node = current_node->p_right;
                continue;
            }
        }

        if (current_node == nullptr) {
            throw TreeException("ERROR: m_key not found (it may have been previously deleted)");
        }

        Node* node_before_removed;

        if (current_node->p_left == nullptr && current_node->p_right == nullptr) {
            // элемент - лист
            if (parent_node == nullptr)
                root = nullptr;
            else {
                if (parent_node->p_left == current_node) {
                    parent_node->p_left = nullptr;
                }
                if (parent_node->p_right == current_node) {
                    parent_node->p_right = nullptr;
                }
            }
            node_before_removed = parent_node;

            delete current_node;
        }

        else if (current_node->p_left == nullptr || current_node->p_right == nullptr) {
            // удаляемый элемент с одним потомком
            if (parent_node == nullptr) {
                if (current_node->p_left == nullptr) {
                    root = root->p_right;
                }
                else {
                    root = root->p_left;
                }
            }
            else {
                if (current_node->p_left == nullptr) {
                    if (parent_node->p_left == current_node) {
                        parent_node->p_left = current_node->p_right;
                    }
                    else {
                        parent_node->p_right = current_node->p_right;
                    }
                }
                else {
                    if (parent_node->p_left == current_node) {
                        parent_node->p_left = current_node->p_left;
                    }
                    else {
                        parent_node->p_right = current_node->p_left;
                    }
                }
            }
            node_before_removed = parent_node;

            delete current_node;
        }

        else {  //когда удаляемый элемент имеет 2 потомка
            auto next_node = current_node->p_right;
            while (next_node->p_left != nullptr) {
                next_node = next_node->p_left;
            }

            T1 tmp = next_node->m_key;
            current_node->m_value = next_node->m_value;
            remove(next_node->m_key); // удаляем лист, потому что он переместился на место удаляемого
            current_node->m_key = tmp;
            node_before_removed = current_node;
        }
        return node_before_removed;
    }

    virtual void _balance(Node* node) {}

    virtual void hook_insert() {};

    virtual void hook_remove() {};

    virtual void hook_find() {};

    void _prefix_traverse(void (*function) (T1, T2, int), Node* pp_node, int depth) {
        if (pp_node == nullptr) {
            return;
        }
        function(pp_node->m_key, pp_node->m_value, depth);
        _prefix_traverse(function, pp_node->p_left, depth + 1);
        _prefix_traverse(function, pp_node->p_right, depth + 1);
    }

    void _infix_traverse(void (*function) (T1, T2, int), Node* pp_node, int depth) {
        if (pp_node == nullptr) {
            return;
        }
        _infix_traverse(function, pp_node->p_left, depth + 1);
        function(pp_node->m_key, pp_node->m_value, depth);
        _infix_traverse(function, pp_node->p_right, depth + 1);
    }

    void _postfix_traverse(void (*function) (T1, T2, int), Node* pp_node, int depth) {
        if (pp_node == nullptr) {
            return;
        }
        _postfix_traverse(function, pp_node->p_left, depth + 1);
        _postfix_traverse(function, pp_node->p_right, depth + 1);
        function(pp_node->m_key, pp_node->m_value, depth);
    }

    void _clear(Node* subTree) {
        if (subTree == nullptr) {
            return;
        }
        if (subTree->p_left != nullptr) {
            _clear(subTree->p_left);
        }
        if (subTree->p_right != nullptr) {
            _clear(subTree->p_right);
        }
        delete subTree;
    }

    static void _print_tree(T1 key, T2 value, int depth) {
        std::cout << "KEY: " << key << " VALUE: " << value << " DEPTH: " << depth << std::endl;
    }

public:

    explicit BinaryTree(const Comparator <int>* _comparator) {
        comparator = _comparator;
        root = nullptr;
    }

    virtual ~BinaryTree() {
        _clear(root);
    }

    void insert(const T1 &key, const T2 &value) {
        auto pNode = _insert(key, value);
        hook_insert();
        _balance(pNode);
    }

    void remove(const T1 &key) {
        auto node = _remove(key);
        _balance(node);
        hook_remove();
    }

    Node* find(const T1 &key) override {
        auto node = _find(key);
        hook_find();
        return node;
    }

    void prefix_traverse(void (*function) (T1, T2, int) = _print_tree) {
        _prefix_traverse(function, root, 0);
    }

    void postfix_traverse(void (*function) (T1, T2, int) = _print_tree) {
        _postfix_traverse(function, root, 0);
    }

    void infix_traverse(void (*function) (T1, T2, int) = _print_tree) {
        _infix_traverse(function, root, 0);
    }

};


#endif //TASK1_BSTREE_H
