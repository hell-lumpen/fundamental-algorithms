//
// Created by Maxim on 14.11.2021.
//

//
// Comparator templated class implementation and
// implementation exception class for binary search tree.
// definition abstract template class associate container
//

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
        if (left > right)
            return 1;
        if (left == right)
            return 0;
        return -1;
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
