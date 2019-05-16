#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>  // size_t
#include <iostream> // std::cerr, std::distance
#include <exception>
#include <algorithm>        // std::min
#include <initializer_list> // std::initializer_list
#include <iterator>

#include "./MyIterator.h"

namespace sc
{
template <typename T>
class vector
{
public:
    using size_type = unsigned long;
    using value_type = T;                       //!< The value type.
    using pointer = value_type *;               //!< Pointer to a value stored in the container.
    using reference = value_type &;             //!< Reference to a value stored in the container.
    using const_reference = const value_type &; //!< Const reference to a value stored in the container.
    using iterator = MyIterator<T>;             // See Code 3
    using const_iterator = MyIterator<const T>; // See Code 3

    //=== [I] SPECIAL MEMBERS
    /// Default constructor that creates an empty list.
    vector()
    {
        SIZE = 0;
        CAPACITY = 0;
        data = new T[0];
    }

    /// Constructs the list with count default-inserted instances of T
    explicit vector(size_type count)
    {
        SIZE = 0;
        CAPACITY = count;
        data = new T[CAPACITY];
    }

    /// Constructs the list with the contents of the range [first, last).
    template <typename InputIt>
    vector(InputIt first, InputIt last)
    {
        SIZE = std::distance(first, last);
        CAPACITY = 2 * SIZE;
        data = new T[CAPACITY];

        for (auto i(0u); i < SIZE; i++)
            data[i] = *first++;
    }

    /// Copy constructor. Constructs the list with the deep copy of the contents of other.
    vector(const vector &other)
    {
        SIZE = other.size();
        CAPACITY = 2 * SIZE;
        data = new T[CAPACITY];

        for (auto i(0u); i < SIZE; i++)
            data[i] = other.data[i];
    }

    /// Constructs the list with the contents of the initializer list init.
    vector(std::initializer_list<T> ilist)
    {
        SIZE = ilist.size();
        CAPACITY = SIZE;
        data = new T[SIZE];

        for (auto i(0u); i < SIZE; i++)
            data[i] = *(ilist.begin() + i);
    }

    /// Destructs the list.
    ~vector()
    {
    }

    /// Copy assignment operator.
    vector &operator=(const vector &other)
    {
        SIZE = other.size();
        CAPACITY = other.capacity();
        data = new T[CAPACITY];

        for (auto i(0u); i < SIZE; i++)
            data[i] = other.data[i];

        return *this;
    }

    /// Replaces the contents with those identified by initializer list ilist.
    vector &operator=(std::initializer_list<T> ilist)
    {
    }

    /// Return the number of elements in the container.
    size_type size() const
    {
        return SIZE;
    }

    /// Return size of allocated storage capacity.
    size_type capacity() const
    {
        return CAPACITY;
    }

    /// Remove all elements from the container.
    void clear()
    {
        SIZE = 0;
    }

    /// Returns true if the container contains no elements, and false otherwise.
    bool empty()
    {
        return SIZE == 0;
    }

    T &operator[](size_type pos)
    {
        return data[pos];
    }

    //=== [II] ITERATORS
    iterator begin(void);
    iterator end(void);
    const_iterator cbegin(void) const;
    const_iterator cend(void) const;

private:
    size_type SIZE;
    size_type CAPACITY;
    T *data;
};
} // namespace sc

#endif