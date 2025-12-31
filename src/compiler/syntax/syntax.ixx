export module syntax;

import <istream>;
import <vector>;
import <string>;

export namespace MIPS::compiler::syntax {
using CharStream = std::basic_istream<char>;

struct Token {
  std::string val;
  unsigned int line = 0, col = 0;
  bool ignore = false;
};

struct TokenStream {
  std::vector<Token> list{};
  std::size_t current = 0;

  template <typename T>
  TokenStream &operator<<(T &&token)
    requires std::same_as<Token, std::decay_t<T>>
  {
    list.emplace_back(std::forward<T>(token));
    return *this;
  }
  TokenStream &operator>>(Token &token) {
    while ((token = list.at(current++)).ignore) {
    }
    return *this;
  }
  Token &get() { return list.at(current++); }

  auto save() { return current; }
  void rewind(const std::size_t saved) { current = saved; }

  operator bool() const { return current < list.size(); }
};
} // namespace MIPS::compiler::syntax