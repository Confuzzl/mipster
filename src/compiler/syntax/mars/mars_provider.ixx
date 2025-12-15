export module syntax_providers:mars;

import <string>;
// import <string_view>;
import <variant>;
import <vector>;
import <memory>;
import <optional>;

import syntax;
import arch;

export namespace MIPS::sim::compiler::syntax::MARS {

template <typename T> struct LiteralTemplate {
  T value;
};
using Int = LiteralTemplate<int>;
using Float = LiteralTemplate<float>;
using Double = LiteralTemplate<double>;
using Char = LiteralTemplate<char>;
using String = LiteralTemplate<std::string>;
using Literal = std::variant<Int, Float, Double, Char, String>;

struct GeneralPurposeRegister {
  int index;
};
struct FloatingPointRegister {
  int index;
};
struct CoprocessorRegister {
  int index, select;
};
using Register = std::variant<GeneralPurposeRegister, FloatingPointRegister,
                              CoprocessorRegister>;

struct Label {
  std::string name;
};

struct AddressConstant {
  arch::Word address;
};
struct AddressRegisterConstantOffset { // 0($t0)
  arch::Word offset;
  int index;
};
struct AddressLabelRegisterOffset { // label($t0)
  Label label;
  int index;
};
struct AddressLabelConstantOffset { // label + 0
  Label label;
  arch::Word offset;
};
struct AddressLabelRegisterConstantOffset { // label + 0($t0)
  Label label;
  arch::Word offset;
  int index;
};
using Address =
    std::variant<AddressConstant, AddressRegisterConstantOffset,
                 AddressLabelRegisterOffset, AddressLabelConstantOffset,
                 AddressLabelRegisterConstantOffset>;
using ConstexprAddress =
    std::variant<AddressConstant,
                 AddressLabelConstantOffset>; // for jump instructions

using Argument = std::variant<Literal, Register, ConstexprAddress, Address>;

struct InstructionStatement {
  std::string name;
  std::vector<Argument> args;
};

struct Directive {};

struct DataSegment {};
struct TextSegment {};

struct Program {};
struct Provider {
  enum struct SegmentType {
    TEXT,
    DATA,
    KTEXT,
    KDATA,
  };

  std::optional<Program> parse(TokenStream &stream) {
    auto segment = SegmentType::TEXT;

    if (stream) {
      // bad parse
    }
    return {};
  }
};
} // namespace MIPS::sim::compiler::syntax::MARS
