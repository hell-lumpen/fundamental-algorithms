#include <iostream>
#include "accessory.h"
#include "bstree.h"
#include "avltree.h"

int main() {

    const Comparator_int* comparator = new Comparator_int;

    BinaryTree<int, int> bsTree(comparator);
    bsTree.insert(6, 2);
    bsTree.insert(5, 2);
    bsTree.insert(8, 0);
    bsTree.insert(10, 0);
    bsTree.insert(15, 0);
    bsTree.insert(13, 0);
    bsTree.remove(6);
    std::cout << "find: " << bsTree.find(5)->m_value << std::endl;

    std::cout << "=====BST-infix=====" << std::endl;
    bsTree.infix_traverse();
    std::cout << "=====BST-postfix=====" << std::endl;
    bsTree.postfix_traverse();
    std::cout << "=====BST-prefix=====" << std::endl;
    bsTree.prefix_traverse();
    std::cout << "==========" << std::endl;

    AVLTree<int, int> avlTree(comparator);
    avlTree.insert(6, 2);
    avlTree.insert(5, 2);
    avlTree.insert(8, 0);
    avlTree.insert(10, 0);
    avlTree.insert(15, 0);
    avlTree.insert(13, 0);
    avlTree.remove(6);
    std::cout << "find: " << avlTree.find(5)->m_value << std::endl;

    std::cout << "=====AVL-infix=====" << std::endl;
    avlTree.infix_traverse();
    std::cout << "=====AVL-postfix=====" << std::endl;
    avlTree.postfix_traverse();
    std::cout << "=====AVL-prefix=====" << std::endl;
    avlTree.prefix_traverse();
    std::cout << "==========" << std::endl;

    delete comparator;
    return 0;
}
