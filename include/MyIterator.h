template <typename T>
class MyIterator
{
public:
  // Below we have the iterator_traits common interface
  /// Difference type used to calculated distance between iterators.
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;                                      //!< Value type the iterator points to.
  typedef T *pointer;                                        //!< Pointer to the value type.
  typedef T &reference;                                      //!< Reference to the value type.
  typedef std::bidirectional_iterator_tag iterator_category; //!< Iterator category.

  MyIterator() {}

  MyIterator &operator=(const MyIterator &other)
  {
    current = other.current;
    return *this;
  }

  MyIterator(pointer ref)
  {
    current = ref;
  }

  reference operator*() const
  {
    return *current;
  }

  pointer operator->(void)const
  {
    assert(current != nullptr);
    return current;
  }

  MyIterator &operator++() // ++it;
  {
    current++;
    return *this;
  }

  MyIterator operator++(int n) // it++;
  {
    MyIterator temp = *this;
    current++;
    return temp;
  }

  MyIterator &operator--() // --it;
  {
    current--;
    return *this;
  }

  MyIterator operator--(int n) // it--;
  {
    MyIterator temp = this;
    current--;
    return temp;
  }

  friend MyIterator operator+(difference_type diff, MyIterator it)
  {
    it.current += diff;
    return it;
  }

  friend MyIterator operator+(MyIterator it, difference_type diff)
  {
    it.current += diff;
    return it;
  }

  friend MyIterator operator+(MyIterator it, MyIterator other)
  {
    it.current += other.current;
    return it;
  }

  friend MyIterator operator-(difference_type diff, MyIterator it)
  {
    it.current -= diff;
    return it;
  }

  friend MyIterator operator-(MyIterator it, MyIterator other)
  {
    it.current -= other.current;
    return it;
  }

  friend MyIterator operator-(MyIterator it, difference_type diff)
  {
    return it;
  }

  bool operator==(const MyIterator &other) const
  {
    if (*current == *(other.current))
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool operator!=(const MyIterator &other) const
  {
    if (*current != *(other.current))
    {
      return true;
    }
    else
    {
      return false;
    }
  }

private:
  T *current;
};