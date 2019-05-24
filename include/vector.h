/**
 * @file
 * @author Eduardo Sarmento <cealvesarmento@gmail.com> & Victor Vieira <victor@agenciaatwork.com>
 * @version 1.0
 * 
 * @section DESCRIPTION
 * 
 * Implementation of a vector in C++.
 */
#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>  // size_t
#include <iostream> // std::cerr, std::distance
#include <exception>
#include <algorithm>        // std::min
#include <initializer_list> // std::initializer_list
#include <iterator>
#include <stdexcept> //std::out_of_range
#include <string>    //std::to_string

#include "./MyIterator.h"

namespace sc {
    /**
     * @brief Vector data structure
     * @author Eduardo Sarmento & Victor Vieira
     * 
     * A simple class that implements a one-dimensional array with dynamic allocation know as vector.
     */
    template <typename T>
    class vector {
        public:
            using size_type = unsigned long;            //!< The size type.
            using value_type = T;                       //!< The value type.
            using pointer = value_type *;               //!< Pointer to a value stored in the container.
            using reference = value_type &;             //!< Reference to a value stored in the container.
            using const_reference = const value_type &; //!< Const reference to a value stored in the container.
            using iterator = MyIterator<T>;             //!< Iterator that points to a specific element of type T.
            using const_iterator = MyIterator<const T>; //!< Const iterator that points to a specific element of type T.

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
                SIZE = last - first;
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
                delete [] data;
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
                SIZE = ilist.size();
                CAPACITY = SIZE;
                data = new T[CAPACITY];

                for (auto i(0u); i < SIZE; i++)
                    data[i] = *(ilist.begin() + i);

                return *this;
            }

            //=== [II] ITERATORS
            /// Returns an iterator pointing to the first item in the list.
            iterator begin()
            {
                iterator it(&data[0]);
                return it;
            }

            /// Returns an iterator pointing to the end mark in the list, i.e. the position just after the last element of the list.
            iterator end()
            {
                iterator it(&data[SIZE]);
                return it;
            }

            /// Returns a constant iterator pointing to the first item in the list.
            const_iterator cbegin() const
            {
                const_iterator it(&data[0]);
                return it;
            }

            /// Returns a constant iterator pointing to the end mark in the list, i.e. the position just after the last element of the list.
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
            void push_front(const_reference value)
            {
                reserve(SIZE + 1);

                for (int i = SIZE; i > 0; i--)
                    data[i] = data[i - 1];

                data[0] = value;

                ++SIZE;
            }

            /// Adds value to the end of the list.
            void push_back(const_reference value)
            {
                reserve(SIZE + 1);
                data[SIZE] = value;
                ++SIZE;
            }

            /// Removes the object at the end of the list.
            void pop_back()
            {
                --SIZE;
            }

            /// Removes the object at the front of the list.
            void pop_front()
            {
                for (auto i(0u); i < SIZE - 1; i++)
                    data[i] = data[i + 1];

                --SIZE;
            }

            /// Increases the storage capacity of the array to a value that’s is greater or equal to new_cap.
            void reserve(size_type new_cap)
            {
                if (new_cap < capacity())
                    return;

                CAPACITY = CAPACITY == 0 ? 2 : 2 * CAPACITY;
                T *newData = new T[CAPACITY];

                for (auto i(0u); i < SIZE; i++)
                    newData[i] = data[i];

                data = newData;
            }

            /// Requests the removal of unused capacity.
            void shrink_to_fit()
            {
                CAPACITY = SIZE;
                T *newData = new T[CAPACITY];

                for (auto i(0u); i < SIZE; i++)
                    newData[i] = data[i];

                data = newData;
            }

            /// Adds value into the list before the position given by the iterator
            iterator insert(iterator pos, const_reference value)
            {
                std::ptrdiff_t offset = pos - begin();

                if (offset > SIZE)
                    return begin();

                reserve(SIZE + 1);
                SIZE++;

                iterator new_pos = begin() + offset;
                iterator end(&data[SIZE - 1]);

                while (end != new_pos)
                {
                    *end = *(end - 1);
                    end--;
                }

                *end = value;
                return new_pos;
            }

            /// Inserts elements from the range [first; last) before pos
            template <typename InputItr>
            iterator insert(iterator pos, InputItr first, InputItr last)
            {

                std::ptrdiff_t offset = pos - begin();

                if (offset > SIZE)
                    return begin();

                int dist = std::distance(first, last);

                reserve(SIZE + dist);
                SIZE += dist;

                iterator new_pos = begin() + offset;
                iterator old_end = end() - (dist + 1);
                iterator end(&data[SIZE - 1]);

                while (old_end != (new_pos - 1))
                {
                    *end = *old_end;
                    old_end--;
                    end--;
                }

                last--;
                while (last != (first - 1))
                {
                    *end = *last;
                    last--;
                    end--;
                }

                return new_pos;
            }

            /// Inserts elements from the initializer_list `ilist` before `pos`
            iterator insert(iterator pos, const std::initializer_list<value_type> &ilist)
            {
                std::ptrdiff_t offset = pos - begin();

                if (offset > SIZE)
                    return begin();

                int size = ilist.size();

                reserve(SIZE + size);
                SIZE += size;

                iterator new_pos = begin() + offset;
                iterator old_end = end() - (size + 1);
                iterator end(&data[SIZE - 1]);
                while (old_end != (new_pos - 1))
                {
                    *end = *old_end;
                    old_end--;
                    end--;
                }

                auto first = ilist.begin();
                auto last = ilist.end() - 1;
                while (last != (first - 1))
                {
                    *end = *last;
                    last--;
                    end--;
                }
                return new_pos;
            }

            /// Replaces the contents with `count` copies of `value`
            void assign(size_type count, const_reference value)
            {
                SIZE = count;
                if (count > capacity())
                    CAPACITY = count;

                T *newData = new T[CAPACITY];

                for (auto i(0u); i < SIZE; i++)
                    newData[i] = value;

                data = newData;
            }

            /// Replaces the contents of the list with copies of the elements in the `std::initializer_list`
            void assign(const std::initializer_list<T> &ilist)
            {
                int size = ilist.size();
                SIZE = size;
                if (size > capacity())
                    CAPACITY = size;

                T *newData = new T[CAPACITY];

                for (auto i(0u); i < SIZE; i++)
                    data[i] = *(ilist.begin() + i);

                data = newData;
            }

            /// Replaces the contents of the list with copies of the elements in the range [first; last).
            template <typename InputItr>
            void assign(InputItr first, InputItr last)
            {
                int size = last - first;
                SIZE = size;
                if (size > capacity())
                    CAPACITY = size;

                T *newData = new T[CAPACITY];

                iterator it = &newData[0];
                while (first != last)
                {
                    *it = *first;
                    it++;
                    first++;
                }

                data = newData;
            }

            /// Removes elements in the range [first; last) and returns an iterator to the element that follows last before the call.
            iterator erase(iterator first, iterator last)
            {
                iterator past_last = first;
                iterator actual_last = last;
                while (first != actual_last)
                {
                    *first = *last;
                    SIZE--;
                    first++;
                    last++;
                }

                return past_last;
            }

            /// Removes the object at position pos and
            iterator erase(iterator pos)
            {
                iterator past_last = pos;
                while (pos != end())
                {
                    *pos = *(pos + 1);
                    pos++;
                }

                SIZE--;

                return past_last;
            }

            //=== [V] Element access
            ///  Returns the object at the beginning of the list.
            const_reference front() const
            {
                return data[0];
            }

            /// Returns the object at the beginning of the list.
            reference front()
            {
                return data[0];
            }

            ///  Returns the object at the end of the list.
            const_reference back() const
            {
                return data[SIZE - 1];
            }

            ///  Returns the object at the end of the list.
            reference back()
            {
                return data[SIZE - 1];
            }

            /// Returns the object at the index pos in the array, with no bounds-checking.
            reference operator[](size_type pos)
            {
                return data[pos];
            }

            /// Returns the object at the index pos in the array, with no bounds-checking.
            const_reference operator[](size_type pos) const
            {
                return data[pos];
            }

            /// Returns the object at the index pos in the array, with bounds-checking.
            const_reference at(size_type pos) const
            {
                if (pos < 0 || pos >= SIZE)
                    throw std::out_of_range(std::to_string(pos));
                return data[pos];
            }

            /// Returns the object at the index pos in the array, with bounds-checking.
            reference at(size_type pos)
            {
                if (pos < 0 || pos >= SIZE)
                    throw std::out_of_range(std::to_string(pos));
                return data[pos];
            }

            /// Check if contents of both vectors are equal
            bool operator==(const vector &other) const
            {
                if (size() == other.size())
                {
                    for (auto i(0u); i < SIZE; i++)
                        if (data[i] != other.data[i])
                            return false;
                }
                else
                {
                    return false;
                }

                return true;
            }

            /// Check if contents of both vectors are different
            bool operator!=(const vector &other) const
            {
                if (size() != other.size())
                {
                    return true;
                }
                else
                {
                    for (auto i(0u); i < SIZE; i++)
                        if (data[i] != other.data[i])
                            return true;
                }

                return false;
            }

        private:
            size_type SIZE;         //!< Logical size of vector, i.e. the amount of elements stored.
            size_type CAPACITY;     //!< Available amount of elements that can be stored with current allocation.
            T *data;                //!< Array that actually stores the elements of the vector.
    };
}
#endif