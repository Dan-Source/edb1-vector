/**
 * @file
 * @author Eduardo Sarmento <cealvesarmento@gmail.com> & Victor Vieira <victor@agenciaatwork.com>
 * @version 1.0
 * 
 * @section DESCRIPTION
 * 
 * Iterator used by the vector class.
 */

/**
 * @brief Iterator class
 * @author Eduardo Sarmento & Victor Vieira
 * 
 * A simple iterator class that is used by the main vector class.
 */
template <typename T>
class MyIterator
{
public:
  // Below we have the iterator_traits common interface
  typedef std::ptrdiff_t difference_type;                    //!< Difference type used to calculated distance between iterators.
  typedef T value_type;                                      //!< Value type the iterator points to.
  typedef T *pointer;                                        //!< Pointer to the value type.
  typedef T &reference;                                      //!< Reference to the value type.
  typedef std::bidirectional_iterator_tag iterator_category; //!< Iterator category.

  /// Default constructor that creates an nullptr.
  MyIterator()
  {
    current = nullptr;
  }

  /// Copy assignment operator.
  MyIterator &operator=(const MyIterator &other)
  {
    current = other.current;
    return *this;
  }

  /// Constructs a iterator from a address reference.
  MyIterator(pointer ref)
  {
    current = ref;
  }

  /// Returns a value from the iterator pointer.
  reference operator*() const
  {
    return *current;
  }

  /// Return a pointer to the location in the vector the it points to.
  pointer operator->(void)const
  {
    assert(current != nullptr);
    return current;
  }

  /// Advances iterator to the next location within the vector and returns itself.
  MyIterator &operator++() // ++it;
  {
    current++;
    return *this;
  }

  /// Advances iterator to the next location within the vector and returns itself before the increment.
  MyIterator operator++(int n) // it++;
  {
    MyIterator temp = *this;
    current++;
    return temp;
  }

  /// Backs the iterator to the next location within the vector and returns itself.
  MyIterator &operator--() // --it;
  {
    current--;
    return *this;
  }

  /// Backs the iterator to the next location within the vector and returns itself before that.
  MyIterator operator--(int n) // it--;
  {
    MyIterator temp = *this;
    current--;
    return temp;
  }

  /// Return a iterator pointing to the n-th sucessor in the vector from `it`.
  friend MyIterator operator+(difference_type n, MyIterator it)
  {
    it.current += n;
    return it;
  }

  /// Return a iterator pointing to the n-th sucessor in the vector from `it`.
  friend MyIterator operator+(MyIterator it, difference_type n)
  {
    it.current += n;
    return it;
  }

  /// Return the sum `std::ptrdiff_t` from two iterators.
  friend difference_type operator+(MyIterator it, MyIterator other)
  {
    return it.current + other.current;
  }

  /// Return a iterator pointing to the n-th predecessor in the vector from `it`.
  friend MyIterator operator-(difference_type n, MyIterator it)
  {
    it.current -= n;
    return it;
  }

  /// Return a iterator pointing to the n-th predecessor in the vector from `it`.
  friend MyIterator operator-(MyIterator it, difference_type n)
  {
    it.current -= n;
    return it;
  }

  /// Return the difference `std::ptrdiff_t` from two iterators.
  friend difference_type operator-(MyIterator it, MyIterator other)
  {
    return it.current - other.current;
  }

  /// Returns true if both iterators refer to the same location within the vector, and false otherwise.
  bool operator==(const MyIterator &other) const
  {
    return (current - other.current) == 0;
  }

  /// Returns true if both iterators refer to differents location within the vector, and false otherwise.
  bool operator!=(const MyIterator &other) const
  {
    return (current - other.current) != 0;
  }

private:
  T *current; //<! The pointer to the vector data.
};