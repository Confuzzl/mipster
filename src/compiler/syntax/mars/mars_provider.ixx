export module syntax_providers:mars;

import <string>;
import <string_view>;
import <variant>;
import <vector>;
import <memory>;
import <optional>;
import <set>;
import <map>;

import syntax;
import arch;
import util;

export namespace MIPS::compiler::syntax::MARS {
struct SegmentType {
  enum Enum {
    TEXT = 0,
    DATA = 1,
    KERNEL = 2,
    KTEXT = KERNEL | TEXT,
    KDATA = KERNEL | DATA,
  };
};

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
struct Coprocessor0Register {
  int index, select;
};
using Register = std::variant<GeneralPurposeRegister, FloatingPointRegister,
                              Coprocessor0Register>;

struct Label {
  std::string name;
  SegmentType::Enum segment;
  arch::Word offset;
};

struct AddressConstant {
  arch::Word address;
};
struct AddressBaseOffset { // 0($t0)
  arch::Word offset;
  GeneralPurposeRegister base;
};
struct AddressBaseLabel { // label($t0)
  Label label;
  GeneralPurposeRegister base;
};
struct AddressLabelOffset { // label + 0
  Label label;
  arch::Word offset;
};
struct AddressLabelBaseOffset { // label + 0($t0)
  Label label;
  arch::Word offset;
  GeneralPurposeRegister base;
};
using Address =
    std::variant<AddressConstant, AddressBaseOffset, AddressBaseLabel,
                 AddressLabelOffset, AddressLabelBaseOffset>;
using ConstexprAddress =
    std::variant<AddressConstant,
                 AddressLabelOffset>; // for jump instructions

using Argument = std::variant<Literal, Register, ConstexprAddress, Address>;

// struct InstructionStatement {
//   std::string name;
//   std::vector<Argument> args;
// };
struct InstructionBase {
  std::string name;
};
enum struct InstructionSyntaxType {
  GGG,
  GGI,
  GA,
  C16,
  C26,
  FFF,
  FF,
};
struct InstGGG : InstructionBase {
  GeneralPurposeRegister rs, rt, rd;
};
struct InstGGI : InstructionBase {
  GeneralPurposeRegister rs, rt;
  arch::Word immed; // 16 wide
};
struct InstGA : InstructionBase {
  GeneralPurposeRegister rt;
  GeneralPurposeRegister base;
  arch::Word offset; // 16 wide
};
// struct InstC16 : InstructionBase {};
struct InstC26 : InstructionBase {
  union {
    arch::Word offset;      // 26 wide
    arch::Word instr_index; // 26 wide
  };
};
struct InstFFF : InstructionBase {
  FloatingPointRegister ft, fs, fd;
};
struct InstFF : InstructionBase {
  FloatingPointRegister fs, fd;
};
using Instruction = std::variant<InstGGG, InstGGI, InstGA,
                                 /*InstC16, */ InstC26, InstFFF, InstFF>;

struct Directive {
  std::string name;
};

struct Comment {
  unsigned int line, col;
  std::string content;
};

struct BaseDataSegment {
  std::vector<arch::Word> data;
};
struct BaseTextSegment {};
struct DataSegment : BaseDataSegment {};
struct TextSegment : BaseTextSegment {};
struct KDataSegment : BaseDataSegment {};
struct KTextSegment : BaseTextSegment {};

struct Program {
  std::set<Comment> comments;

  std::set<std::string> labels;

  DataSegment data{};
  TextSegment text{};

  KDataSegment kdata{};
  KTextSegment ktext{};
};

struct Provider {
  struct TokenizeError {
    std::string msg;
  };
  util::Result<TokenStream, TokenizeError> tokenize(CharStream &stream);

  struct ParseError {
    std::string msg;
  };
  util::Result<Program, ParseError> parse(TokenStream &stream);

  Provider();

private:
  struct Flags {
    // char specialPunctuation[3] = {'.', '\'', '\"'};

    struct Label {
      bool startWithNumber = false;

      // mars crashes if there is punct
      bool allowNonSpecialPunctuationInName = false;
    } label;

    enum struct CommaBehavior {
      AS_WHITESPACE,
      AS_INSTRUCTION_DELIMITER,
    } commaBehavior = CommaBehavior::AS_INSTRUCTION_DELIMITER;

    enum struct NonSpecialPunctuationBehavior {
      AS_NORMAL_CHARACTER,
      AS_DELIMITER,
    } nonSpecialPunctuationBehavior =
        NonSpecialPunctuationBehavior::AS_NORMAL_CHARACTER;
  } flags;

  arch::Word currentSegmentOffsets[4]{0};
  SegmentType::Enum currentSegment = SegmentType::TEXT;
  arch::Word &currentOffset() { return currentSegmentOffsets[currentSegment]; }

  enum struct State {
    INDETERMINATE,
    INTEGER,
    CHAR,
    STRING,
    COMMENT,
  } state = State::INDETERMINATE;
  std::string buffer{};

  template <typename T> struct ParseResult {
    std::optional<T> result = std::nullopt;
    bool endOfStream = false;

    operator bool() const { return result.has_value(); }
  };

  std::set<Label> labelMap{};

  using DirectiveImplementationFunction =
      ParseResult<Directive> (*)(Provider *, TokenStream &);
  std::map<std::string_view, DirectiveImplementationFunction>
      directiveImplementationMap{};

  // using InstructionImplementationFunction =
  //     ParseResult<Instruction> (*)(CharStream &);
  // std::map<std::string_view, InstructionImplementationFunction>
  //     specialInstructionSyntaxImplementationMap{};
  // std::map<std::string_view, InstructionSyntaxType> instructionToSyntax{};
  // std::map<InstructionSyntaxType, InstructionImplementationFunction>
  //     instructionSyntaxImplementationMap{};

  ParseResult<Comment> parseComment(TokenStream &stream);

  ParseResult<Label> parseLabel(TokenStream &stream);

  ParseResult<Instruction> parseInstruction(TokenStream &stream);

  ParseResult<Directive> parseDirective(TokenStream &stream);
  // ParseResult<Directive> parseDirectiveAlign(TokenStream &stream);
  // ParseResult<Directive> parseDirectiveAscii(TokenStream &stream);
  // ParseResult<Directive> parseDirectiveAsciiz(TokenStream &stream);
  // ParseResult<Directive> parseDirectiveByte(TokenStream &stream);
  // ParseResult<Directive> parseDirectiveDouble(TokenStream &stream);
  // ParseResult<Directive> parseDirectiveFloat(TokenStream &stream);
  // ParseResult<Directive> parseDirectiveHalf(TokenStream &stream);
  // ParseResult<Directive> parseDirectiveSpace(TokenStream &stream);
  // ParseResult<Directive> parseDirectiveWord(TokenStream &stream);

  ParseResult<GeneralPurposeRegister> parseGPR(TokenStream &stream);
  ParseResult<FloatingPointRegister> parseFPR(TokenStream &stream);

  ParseResult<Int> parseInteger(TokenStream &stream);
  ParseResult<Float> parseFloat(TokenStream &stream);
  ParseResult<Double> parseDouble(TokenStream &stream);
  ParseResult<Char> parseChar(TokenStream &stream);
  ParseResult<String> parseString(TokenStream &stream);

  ParseResult<Address> parseAddress(TokenStream &stream);
  ParseResult<ConstexprAddress> parseConstexprAddress(TokenStream &stream);
};
} // namespace MIPS::compiler::syntax::MARS
