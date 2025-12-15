export module compiler;

import <string>;
import <iostream>;
import <fstream>;
import <sstream>;

import syntax_providers;

export namespace MIPS::sim::compiler {

/*
(base register) Base address (zero Offset assumed)
expression Absolute address
expression (base register) Based address
relocatable-symbol Relocatable address
relocatable-symbol + expression Relocatable address
relocatable-symbol + expression
(index register) Indexed relocatable address
*/
struct CompilationResult {};
void compile(const std::string &path) {
  std::ifstream fileStream{path};

  std::cout << fileStream.is_open() << "\n";

  std::stringstream buffer{};
  buffer << fileStream.rdbuf();

  // syntax::MARS::Provider provider{};

  // auto result = provider.parse(buffer);
  // if (!result) {
  // }

  std::string tok;
  while (buffer >> tok) {
    std::cout << tok << " ";
  }
  // std::cout << "\n:)\n";
  //  for (std::string line; std::getline(stream, line);) {
  //    // std::cout << line << "\n";
  //    std::istringstream tokenStream{line};

  //  // std::string tok;
  //  // while (tokenStream >> tok) {
  //  // }
  //}
}
} // namespace MIPS::sim::compiler