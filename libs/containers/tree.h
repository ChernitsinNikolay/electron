#ifndef TREE_H
#define TREE_H

#include <vector>

template <class T>
class Tree
{
public:
    explicit Tree();
    virtual ~Tree();

    void addChildren(const Tree<T> &tree);
    void setValue(const T &value);

    Tree<T> operator[](size_t idx)
    { return *p_childrens[idx]; }

    std::size_t size() const
    { return p_childrens.size(); }

private:
    std::vector<Tree<T>*> p_childrens;
    T *p_value;
};

template <class T>
Tree<T>::Tree()
{
    p_value = 0;
}

template <class T>
Tree<T>::~Tree()
{
    for(std::iterator<Tree<T>*> iter = p_childrens.begin(); iter != p_childrens.end(); iter++)
        delete *iter;
    delete p_value;
}

#endif // TREE_H
