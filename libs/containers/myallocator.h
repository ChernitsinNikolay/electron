#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <bits/allocator.h>

template <typename T>
class MyAllocator
{
public:
    typedef T value_type;
    typedef value_type *pointer;
    //typedef const value_type *const_pointer;
    typedef T &reference;
    typedef std::size_t size_type;

    MyAllocator();

    pointer allocate(size_type _Count);
    void deallocate(pointer _Ptr, size_type);
};

template <typename T>
MyAllocator<T>::MyAllocator()
{ }

template <typename T>
typename MyAllocator<T>::pointer MyAllocator<T>::allocate(size_type _Count)
{
    void *_Ptr = 0;

    if (_Count != 0 && (((size_type)(-1) / sizeof(value_type) < _Count)
        || (_Ptr = ::operator new(_Count * sizeof (value_type))) == 0)) {
        //throw bad_alloc();
    }
    return (pointer)_Ptr;
}

template <typename T>
void MyAllocator<T>::deallocate(pointer _Ptr, size_type)
{
    ::operator delete(_Ptr);
}

#endif // ALLOCATOR_H
