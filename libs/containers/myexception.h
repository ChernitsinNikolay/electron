#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <exception>

class AllocException : public std::exception
{
public:
    AllocException() { }
    virtual ~AllocException() { }
    virtual const char* what() const throw() { return "Allocation failed: AllocException\n"; }
};

class OutOfRangeException : public std::exception
{
public:
    OutOfRangeException() { }
    virtual ~OutOfRangeException() { }
    virtual const char* what() const throw() { return "Out of range: OutOfRangeException\n"; }
};

#endif // MYEXCEPTION_H
