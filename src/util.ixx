export module util;

import arch;
import <variant>;
import <utility>;

export namespace MIPS::util {
using namespace arch;
unsigned int bitMask(const int from, const int to) {
  const auto size = to - from + 1;
  return ((1 << size) - 1) << from;
}
Word getBits(const Word word, const int from, const int to) {
  const auto size = to - from + 1;
  const Word mask = (1 << size) - 1;
  const Word shift = word >> from;
  return shift & mask;
}

template <typename T, typename E> struct Result {
  static_assert(!std::is_same_v<T, E>);

  std::variant<T, E> storage;

  template <typename U> Result(U &&val) : storage{std::forward<U>(val)} {}

  bool has_value() const { return std::holds_alternative<T>(storage); }
  operator bool() const { return has_value(); }

  T &value() { return std::get<T>(storage); }
  const T &value() const { return std::get<T>(storage); }

  E &error() { return std::get<E>(storage); }
  const E &error() const { return std::get<E>(storage); }
};
} // namespace MIPS::util