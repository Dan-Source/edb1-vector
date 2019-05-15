#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>  // size_t
#include <iostream> // std::cerr
#include <exception>
#include <algorithm>        // std::min
#include <initializer_list> // std::initializer_list

namespace sc
{
template <typename T>
class Vector
{
public:
  Vector();
  ~Vector();
};
} // namespace sc

#endif