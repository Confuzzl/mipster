module;

#include <algorithm>
#include <cctype>

#define DIRECTIVE_FUNC                                                         \
  [](Provider * self, TokenStream & stream) -> ParseResult<Directive>

module syntax_providers:mars;

// import <exception>;
import <iostream>;

import util;
import exception;
// import <algorithm>;

static void stringLower(std::string &str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return std::tolower(c); });
}

namespace MIPS::compiler::syntax::MARS {

Provider::Provider() {
  directiveImplementationMap = {
      {"align",
       DIRECTIVE_FUNC{
           // TODO
       }},
  };
}

util::Result<TokenStream, Provider::TokenizeError>
Provider::tokenize(CharStream &stream) {
  TokenStream out{};
  char c;
  std::string buffer{};
  unsigned int line = 1, col = 0;

  static constexpr auto pushStream = [](TokenStream &out, std::string &buffer,
                                        const unsigned int line,
                                        const unsigned int col) {
    if (buffer.empty())
      return;

    out << Token{.val = buffer, .line = line, .col = col};
    buffer.clear();
  };
  static constexpr auto pushStreamChar = [](TokenStream &out, const char c,
                                            const unsigned int line,
                                            const unsigned int col,
                                            const bool ignore) {
    out << Token{
        .val = std::string{1, c}, .line = line, .col = col, .ignore = ignore};
  };

  while (stream.get(c)) {
    col++;

    enum struct CharBehavior {
      NORMAL,
      DELIMITER,
      WHITESPACE,
      BAD,
    } behavior;

    if (c == ',') {
      if (flags.commaBehavior == Flags::CommaBehavior::AS_WHITESPACE)
        behavior = CharBehavior::WHITESPACE;
      else if (flags.commaBehavior ==
               Flags::CommaBehavior::AS_INSTRUCTION_DELIMITER)
        behavior = CharBehavior::DELIMITER;
    } else if (std::isspace(c)) {
      behavior = CharBehavior::WHITESPACE;
    } else if (std::ispunct(c)) {
      behavior = CharBehavior::DELIMITER;
    } else if (std::isalnum(c)) {
      behavior = CharBehavior::NORMAL;
    } else {
      behavior = CharBehavior::BAD;
    }

    switch (behavior) {
    case CharBehavior::NORMAL:
      buffer += c;
      break;
    case CharBehavior::DELIMITER:
      pushStream(out, buffer, line, col);
      pushStreamChar(out, c, line, col, false);
      break;
    case CharBehavior::WHITESPACE:
      pushStream(out, buffer, line, col);
      pushStreamChar(out, c, line, col, true);
      if (c == '\n') {
        line++;
        col = 0;
      }
      break;
    case CharBehavior::BAD:
      return TokenizeError{std::format(
          "char '{}' ({}) at line {} col {} of unsupported category", c,
          static_cast<unsigned int>(c), line, col)};
    }
  }
  pushStream(out, buffer, line, col);
  return out;
}

util::Result<Program, Provider::ParseError>
Provider::parse(TokenStream &stream) {
  Program out{};
  while (stream) {
    const auto save = stream.save();

    if (parseComment(stream)) {
      continue;
    }
    stream.rewind(save);

    // if (auto res = parseLabel(stream); res) {
    //   continue;
    // }
    // stream.rewind(save);

    if (auto res = parseDirective(stream); res) {
      continue;
    }
    stream.rewind(save);

    // if (auto res = parseInstruction(stream); res) {
    //   continue;
    // }

    // FAILED
  }
  // else if ()

  //  char c;
  //  while (stream.get(c)) {
  //    if (state == State::COMMENT)
  //      continue;

  //  switch (c) {
  //  case '\n': {
  //    switch (state) {
  //    case State::INDETERMINATE: {
  //    }
  //    case State::INTEGER: {
  //    }
  //    case State::CHAR: { // char wasnt closed
  //    }
  //    case State::STRING: { // string wasnt closed
  //    }
  //    case State::COMMENT: {
  //    }
  //    }
  //    state = State::INDETERMINATE;
  //  }
  //  case '\"': {
  //    if (state != State::STRING) { // start string
  //      state = State::STRING;

  //      buffer.push_back(c);
  //    } else { // end string
  //      state = State::INDETERMINATE;

  //      buffer.clear();
  //    }
  //    // string ^= string;
  //  }
  //  case '#': {
  //    if (state != State::STRING)
  //      state = State::COMMENT;
  //  }
  //  case '.': {
  //    parseDirective();
  //  }
  //  case ':': {
  //  }
  //  default: {
  //    // unrecognized char
  //  }
  //  }
  //  // stream.unget();
  //}
  return out;
}

Provider::ParseResult<Comment> Provider::parseComment(TokenStream &stream) {
  Token hash;
  stream >> hash;
  if (hash.val[0] != '#')
    return ParseResult<Comment>{.result = std::nullopt};
  std::string content{};
  return ParseResult<Comment>{.result = Comment{}};
}

Provider::ParseResult<Label> Provider::parseLabel(TokenStream &stream) {
  Token name, colon;
  stream >> name;
  stream >> colon;
  if (colon.val[0] == ':') {

    return ParseResult<Label>{.result = Label{.name = std::move(name.val),
                                              .segment = currentSegment,
                                              .offset = currentOffset()}};
  } else {
    return ParseResult<Label>{.result = std::nullopt};
  }
}

Provider::ParseResult<Instruction>
Provider::parseInstruction(TokenStream &stream) {
  return {};
}

Provider::ParseResult<Directive> Provider::parseDirective(TokenStream &stream) {
  Token dot;
  stream >> dot;
  if (dot.val[0] != '.') {
    return ParseResult<Directive>{.result = std::nullopt};
  }

  std::string name;
  Token curr;
  while (stream >> curr && !curr.ignore) {
    name += curr.val;
  }
  stringLower(name);

  auto it = directiveImplementationMap.find(name);
  if (it == directiveImplementationMap.end()) {
    return ParseResult<Directive>{.result = std::nullopt};
  }
  DirectiveImplementationFunction func = it->second;
  return func(this, stream);
}

Provider::ParseResult<GeneralPurposeRegister>
Provider::parseGPR(TokenStream &stream) {
  return {};
}
Provider::ParseResult<FloatingPointRegister>
Provider::parseFPR(TokenStream &stream) {
  return {};
}

Provider::ParseResult<Int> Provider::parseInteger(TokenStream &stream) {
  return {};
}
Provider::ParseResult<Float> Provider::parseFloat(TokenStream &stream) {
  return {};
}
Provider::ParseResult<Double> Provider::parseDouble(TokenStream &stream) {
  return {};
}
Provider::ParseResult<Char> Provider::parseChar(TokenStream &stream) {
  return {};
}
Provider::ParseResult<String> Provider::parseString(TokenStream &stream) {
  return {};
}

Provider::ParseResult<Address> Provider::parseAddress(TokenStream &stream) {
  return {};
}
Provider::ParseResult<ConstexprAddress>
Provider::parseConstexprAddress(TokenStream &stream) {
  return {};
}
} // namespace MIPS::compiler::syntax::MARS