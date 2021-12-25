//
// Created by Maxim on 14.11.2021.
//

//
// Comparator templated class implementation and
// implementation exception class for binary search tree.
// definition abstract template class associate container
//
// Должна быть примерно такая структура, но я не успеваю :(
// ============================================
// template <class T1, class T2>
// class AssociateContainer {
// protected:
//     class Node{
//     public:
//         Node() = default;
//         virtual ~Node() = default;
//     };

//     AssociateContainer() = default;
//     virtual ~AssociateContainer() = default;

//     class Finder {
//     public:
//         Node* invoke(const T1 &key, const T2 &value) {
//             before_find();
//             void find();
//             after_find();
//         }
//     protected:
//         virtual void before_find() {}
//         virtual void find() = 0;
//         virtual void after_find() {}

//     };
//     class Inserter {
//     public:
//         void invoke(const T1 &key, const T2 &value) {
//             before_insert();
//             insert(key, value);
//             after_insert();
//         }
//     protected:
//         virtual void before_insert() {}
//         virtual void insert(const T1 &key, const T2 &value) {}
//         virtual void after_insert() {}
//     };

//     class Remover {
//     public:
//         void invoke(const T1 &key) {
//             before_remove();
//             remove(key);
//             after_remove();
//         }
//     protected:
//         virtual void before_remove() {}
//         virtual void remove(const T1 &key) {}
//         virtual void after_remove() {}
//     };
// };
// ============================================
// template <class T1, class T2>
// class Tree : public AssociateContainer<T1, T2> {
// private:
//     class TNode : AssociateContainer<T1, T2>::Node {};

// protected:
//     class TFinder : AssociateContainer<T1, T2>::Finder {
//     protected:
//         void find() override {
//             // TODO: реализация поиска
//         }
        
//         void after_find() override {
//             // TODO: например поднять ноду наверх как в косом дереве
//         }
//     };
// };
// ============================================

#ifndef TASK1_ACCESSORY_H
#define TASK1_ACCESSORY_H

template <class T>
class Comparator {
public:
    virtual int compare(const T& left, const T& right) const = 0;
    virtual ~Comparator() = default;;
};

class Comparator_int: public Comparator <int> {
public:
    int compare(const int& left, const int& right) const override {
        return left - right;
    }
};

class TreeException: public std::exception
{
private:
    std::string error_;

public:
    explicit TreeException(std::string error): error_{std::move(error)} {}
    const char* what() const noexcept override {
        return error_.c_str();
    }
};

template <class T1, class T2>
class AssociateContainer {
protected:
    class Node{
    public:
        explicit Node() = default;
        virtual ~Node() = default;
    };

    AssociateContainer() = default;
    virtual void insert(const T1 &key, const T2 &value) = 0;
    virtual void remove(const T1 &key) = 0;
    virtual Node* find(const T1 &key) = 0;
    virtual ~AssociateContainer() = default;
};


#endif //TASK1_ACCESSORY_H
