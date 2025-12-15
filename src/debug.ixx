export module debug;

import <iostream>;
import <format>;
import <string_view>;

export void println(const std::string_view str = "") {
  std::cout << str << "\n";
}

export template <typename... Args>
void println(std::format_string<Args...> str, Args &&...args) {
  println(std::format(str, std::forward<Args>(args)...));
}

export template <typename T> void println(const T &s) { println("{}", s); }