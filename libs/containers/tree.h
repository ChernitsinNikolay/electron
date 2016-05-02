#ifndef TREE_H
#define TREE_H

#include <vector>

template <class T>
class Tree
{
    //typedef typename std::vector<Tree<T>*> pTypeT;
public:
    explicit Tree();
    explicit Tree(const Tree<T> &tree);

    virtual ~Tree();

    void setParent(Tree<T> *tree)
    { parent = tree; }

    void addChildren(const Tree<T> &tree)
    { Tree<T> *temp = new Tree<T>(tree); temp->setParent(this); m_childrens.push_back(temp); }

    void setValue(const T &value)
    { m_value = new T(value); }

    const Tree<T> *operator[](std::size_t idx) const
    { return m_childrens[idx]; }

    Tree<T> *getParent() const
    { return parent; }

    std::size_t size() const
    { return m_childrens.size(); }

    const T &value() const { return *m_value; }

private:
    Tree<T> *parent;
    std::vector<Tree<T>*> m_childrens;
    T *m_value;
};

template <class T>
Tree<T>::Tree()
{
    m_value = 0;
    parent = 0;
}

template <class T>
Tree<T>::~Tree()
{
    /*for(pTypeT::iterator iter = m_childrens.begin(); iter != m_childrens.end(); iter++)
        delete (*iter);
    delete m_value;*/
}

template <class T>
Tree<T>::Tree(const Tree<T> &tree)
{
    m_value = tree.m_value;
    parent = tree.parent;
    for(std::size_t i = 0; i < tree.m_childrens.size(); i++) {
        Tree<T> *temp = new Tree<T>(*tree.m_childrens[i]);
        temp->setParent(this);
        m_childrens.push_back(temp);
    }
}

#endif // TREE_H
