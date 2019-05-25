#include "../include/vector.h"

int main(void)
{
  // Range = the entire vector.
  sc::vector<int> vec{1, 2, 3, 4, 5};
  sc::vector<int> vec2(vec.begin(), vec.end());
  std::cout << "[" << vec2.size() << "]"
            << " == 5?" << std::endl;
  std::cout << vec.empty() << std::endl;

  for (auto i{0u}; i < vec.size(); ++i)
    std::cout << "[" << i + 1 << "]"
              << " == " << vec[i] << ";";

  // Range is part of the vector.
  sc::vector<int> vec3(std::next(vec.begin(), 1), std::next(vec.begin(), 3));
  std::cout << "[" << vec3.size() << "] == 2" << std::endl;
  std::cout << vec3.empty() << std::endl;

  for (auto i{0u}; i < vec3.size(); ++i)
    std::cout << "[" << vec[i + 1] << "] == " << vec3[i] << std::endl;

  return 0;
}