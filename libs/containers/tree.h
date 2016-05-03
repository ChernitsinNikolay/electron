#ifndef TREE_H
#define TREE_H

#include <vector>

template <typename T>
class Tree
{
public:
    Tree();
    Tree(const Tree<T> &tree);

    virtual ~Tree();

    inline void addChildren(const Tree<T> &tree);
    inline void setValue(const T &value);

    inline std::size_t childrenSize() const { return m_childrens.size(); }
    Tree<T> *operator[](std::size_t idx) const { return m_childrens[idx]; }
    inline T &value() const { return *m_value; }

private:
    std::vector<Tree<T>*> m_childrens;
    T *m_value;
};


/*************************************************************
 ***********************REFERENCE*****************************
 *************************************************************/
template <typename T>
Tree<T>::Tree() : m_value(0) { }

template <typename T>
Tree<T>::Tree(const Tree<T> &tree) :
    m_value(0)
{
    setValue(*tree.m_value);
    for(typename std::vector<Tree<T>*>::const_iterator iter = tree.m_childrens.begin(); iter != tree.m_childrens.end(); iter++)
        addChildren(Tree<T>(**iter));
}

template <typename T>
Tree<T>::~Tree()
{
    delete m_value;
    for(typename std::vector<Tree<T>*>::iterator iter = m_childrens.begin(); iter != m_childrens.end(); iter++)
        delete *iter;
    m_childrens.clear();
}

template <typename T>
void Tree<T>::addChildren(const Tree<T> &tree)
{
    m_childrens.push_back(new Tree<T>(tree));
}

template <typename T>
void Tree<T>::setValue(const T &value)
{
    delete m_value;
    m_value = new T(value);
}

#endif // TREE_H
