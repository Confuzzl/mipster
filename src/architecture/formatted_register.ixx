export module formatted_register;

import arch;
import <memory>;
import <map>;
import <string_view>;

export namespace MIPS::arch {
template <std::size_t N> struct FRegName {
  static constexpr auto SIZE = N;
  char m[N];
  constexpr FRegName(const char (&s)[N]) { std::copy_n(s, N, m); }
};
struct FReg {
  Word value = 0;

  std::string_view name;

  struct Field {
    std::string_view name;
    enum struct Accessibility : unsigned int { RW, R, R0, Z, RW0, W0 };
    Accessibility access : 4;
    unsigned int start : 6;
    unsigned int end : 6;

    Field(const std::string_view name, const unsigned int start,
          const unsigned int end, const Accessibility access)
        : name{name}, start{start}, end{end}, access{access} {}
    Field(const std::string_view name, const unsigned int bit,
          const Accessibility access)
        : Field(name, bit, bit, access) {}
  };
  struct FieldList {
    std::map<std::string_view, int> namedMap;
    std::unique_ptr<Field[]> arr;
    int _size;

    template <typename... Fields>
    FieldList(Fields &&...fields)
        : arr{new Field[]{fields...}}, _size{sizeof...(fields)} {
      for (auto i = 0; i < _size; i++)
        namedMap.emplace(arr[i].name, i);
    }
    FieldList(const FieldList &) = delete;
    FieldList(FieldList &&that) : arr{std::move(that.arr)}, _size{that._size} {}
    FieldList &operator=(const FieldList &) = delete;
    FieldList &operator=(FieldList &that) {
      arr = std::move(that.arr);
      _size = that._size;
      return *this;
    }

    const int size() const { return _size; }

    Field &operator[](const int i) { return arr[i]; }
    const Field &operator[](const int i) const { return arr[i]; }
    Field &operator[](const std::string_view name) {
      return arr[namedMap.at(name)];
    }
    const Field &operator[](const std::string_view name) const {
      return arr[namedMap.at(name)];
    }

    Field *begin() const { return arr.get(); }
    Field *end() const { return begin() + _size; }
  } fields;

  // FReg(const std::string_view name, FieldList &&fields)
  //     : name{name}, fields{std::move(fields)} {}
  FReg(FieldList &&fields) : fields{std::move(fields)} {}

  Word operator[](const std::string_view name) const;

  Word read() const;
  void write(const Word x);
};
} // namespace MIPS::arch
