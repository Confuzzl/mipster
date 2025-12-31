export module executable;

import <vector>;
import arch;
import computer32;

export namespace MIPS::sim::exec {
struct Executable {
  std::vector<arch::Word> instructions{};

  void execute() {
    arch::_32::computer;
    //
  }
};
} // namespace MIPS::sim::exec