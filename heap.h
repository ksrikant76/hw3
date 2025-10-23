#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  int m_;
  PComparator comp_;
  std::vector<T> data_;

  size_t parent(size_t i) const { return (i - 1) / static_cast<size_t>(m_); }
  size_t child (size_t i, size_t k) const { return static_cast<size_t>(m_)*i + k; }
  void bubbleUp(size_t i);
  void bubbleDown(size_t i);
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
  : m_(m < 2 ? 2 : m), comp_(c), data_() {}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap() = default;

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
  return data_.empty();
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const {
  return data_.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item) {
  data_.push_back(item);
  bubbleUp(data_.size() - 1);
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap::top on empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data_.front();
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap::pop on empty heap");
  }

  //if size = 1, no need to bubble down
  if (data_.size() == 1) {
    data_.pop_back();
    return;
  }

  //else, swap last element to top of heap and bubble down
  std::swap(data_.front(), data_.back());
  data_.pop_back();
  bubbleDown(0);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::bubbleUp(size_t i) {
  //keep swapping upwards as long as comp with parent is true
  while (i > 0) {
    size_t p = parent(i);
    if (comp_(data_[i], data_[p])) {
      std::swap(data_[i], data_[p]);
      i = p;
    }
    else {
      break;
    }
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::bubbleDown(size_t i) {
  while (true) {
    size_t first = child(i, 1);
    //if child doesn't exist, finish
    if (first >= data_.size()) break;

    //find the child to be swapped
    size_t last = std::min(first + static_cast<size_t>(m_), data_.size());
    size_t best = first;
    for (size_t j = first + 1; j < last; ++j) {
      if (comp_(data_[j], data_[best])) best = j;
    }

    //swap if needed, else break
    if (comp_(data_[best], data_[i])) {
      std::swap(data_[i], data_[best]);
      i = best;
    }
    else {
      break;
    }
  }
}

#endif

