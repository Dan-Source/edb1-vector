#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>  // size_t
#include <iostream> // std::cerr, std::distance
#include <exception>
#include <algorithm>        // std::min
#include <initializer_list> // std::initializer_list
#include <iterator>
#include <stdexcept> //std::out_of_range
#include <string> //std::to_string

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
        data = new T[CAPACITY];
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

    //=== [II] ITERATORS
    iterator begin(void)
    {
        iterator it(&data[0]);
        return it;
    }
    iterator end(void)
    {
        iterator it(&data[SIZE]);
        return it;
    }
    const_iterator cbegin(void) const
    {
        const_iterator it(&data[0]);
        return it;
    }
    const_iterator cend(void) const
    {
        const_iterator it(&data[SIZE]);
        return it;
    }

    //=== [III] Capacity
    /// Return the number of elements in the container.
    size_type size() const
    {
        return SIZE;
    }

    /// Return the internal storage capacity of the array.
    size_type capacity() const
    {
        return CAPACITY;
    }

    /// Returns true if the container contains no elements, and false otherwise.
    bool empty()
    {
        return SIZE == 0;
    }

    //=== [IV] Modifiers
    /// Remove all elements from the container.
    void clear()
    {
        SIZE = 0;
    }

    /// Adds value to the front of the list.
    void push_front(const_reference value) {
        reserve(SIZE + 1);

        for (int i = SIZE; i > 0; i--)
            data[i] = data[i - 1];

        data[0] = value;

        ++SIZE;
    }

    /// Adds value to the end of the list.
    void push_back(const_reference value) {
        reserve(SIZE + 1);
        data[SIZE] = value;
        ++SIZE;
    }

    /// Removes the object at the end of the list.
    void pop_back () {
        --SIZE;
    }

    /// Removes the object at the front of the list.
    void pop_front () {
        for (auto i(0u); i < SIZE - 1; i++)
            data[i] = data[i+1];
        
        --SIZE;
    }
    
    void reserve (size_type new_cap) {
        if (new_cap < capacity()) return;

        CAPACITY = CAPACITY == 0 ? 2 : 2 * CAPACITY;        
        T *newData = new T[CAPACITY];

        for (auto i(0u); i < SIZE; i++)
            newData[i] = data[i];

        data = newData;
    }

    /// Requests the removal of unused capacity.
    void shrink_to_fit () {
        CAPACITY = SIZE;
        T *newData = new T[CAPACITY];

        for (auto i(0u); i < SIZE; i++)
            newData[i] = data[i];

        data = newData;
    }

    void assign(size_type count, const_reference value) {
        reserve(count);

        for (auto i(0u); i < count; i++)
            data[i] = value;

        SIZE = count;
    }

    /*
    iterator insert(iterator, const_reference);
    template <typename InputItr>
    iterator insert(iterator, InputItr, InputItr);
    iterator insert(iterator, const std::initializer_list<value_type> &);
    void reserve(size_type);
    void shrink_to_fit(void);
    void assign(size_type, const_reference);
    void assign(const std::initializer_list<T> &);
    template <typename InputItr>
    void assign(InputItr, InputItr);

    iterator erase(iterator, iterator);
    iterator erase(iterator);*/

    //=== [V] Element access
    ///  Returns the object at the beginning of the list.
    const_reference front() const {
        return data[0];
    }

    /// Returns the object at the beginning of the list.
    reference front () {
        return data[0];
    }
    
    ///  Returns the object at the end of the list.
    const_reference back() const {
        return data[SIZE - 1];
    }

    ///  Returns the object at the end of the list.
    reference back () {
        return data[SIZE - 1];
    }

    /// Returns the object at the index pos in the array, with no bounds-checking.
    reference operator[](size_type pos)
    {
        return data[pos];
    }

    /// Returns the object at the index pos in the array, with no bounds-checking.
    const_reference operator[](size_type pos) const {
        return data[pos];
    }

    /// Returns the object at the index pos in the array, with bounds-checking. 
    const_reference at(size_type pos) const {
        if(pos < 0 || pos >= SIZE) throw std::out_of_range(std::to_string(pos));
        return data[pos];
    }

    /// Returns the object at the index pos in the array, with bounds-checking. 
    reference at(size_type pos) {
        if(pos < 0 || pos >= SIZE) throw std::out_of_range(std::to_string(pos));
        return data[pos];
    }
    /*

    pointer data(void);
    const_reference data(void) const;

    // [VI] Friend functions
    friend std::ostream &operator<<(std::ostream &, const vector<T> &);
    friend void swap(vector<T> &, vector<T> &);
*/
private:
    size_type SIZE;
    size_type CAPACITY;
    T *data;
};
} // namespace sc

#endif