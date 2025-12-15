export module arch;

import <cstdint>;

export namespace MIPS::arch {
int getRelease();
void setRelease(const int r);

using Byte = std::uint8_t;
using SByte = std::int8_t;
using Word = std::uint32_t;
using SWord = std::int32_t;

struct Instruction {
  Word repr;

  Word opcode() const { return bitRange(26, 31); }

protected:
  Word bitRange(const int from, const int to) const {
    const auto size = to - from + 1;
    const Word mask = (1 << size) - 1;
    const Word shift = repr >> from;
    return shift & mask;
  }
};
struct RInstruction : Instruction {
  Word rs() const { return bitRange(25, 21); }
  Word rt() const { return bitRange(20, 16); }
  Word rd() const { return bitRange(15, 11); }
  Word shamt() const { return bitRange(10, 6); }
  Word funct() const { return bitRange(5, 0); }
};
struct IInstruction : Instruction {
  Word rs() const { return bitRange(25, 21); }
  Word rt() const { return bitRange(20, 16); }
  Word immed() const { return bitRange(15, 0); }
};
struct JInstruction : Instruction {
  Word addr() const { return bitRange(25, 0); }
};
struct FRInstruction : Instruction {
  Word fmt() const { return bitRange(25, 21); }
  Word rt() const { return bitRange(20, 16); }
  Word rs() const { return bitRange(15, 11); }
  Word fd() const { return bitRange(10, 6); }
  Word funct() const { return bitRange(5, 0); }
};
} // namespace MIPS::arch