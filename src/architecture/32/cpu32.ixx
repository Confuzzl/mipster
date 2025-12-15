export module arch32:cpu;

import arch;
import <map>;
import <string_view>;

export namespace MIPS::arch::_32 {
struct CPU {
  struct GeneralPurposeRegisters {
    // I DONT CARE ABOUT ANONYMOUS STRUCTS OR UNION UB!!!!!!!!!!
    /*union {
      struct {
        Word zero;
        Word at;
        Word v0, v1;
        Word a0, a1, a2, a3;
        Word t0, t1, t2, t3, t4, t5, t6, t7;
        Word s0, s1, s2, s3, s4, s5, s6, s7;
        Word t8, t9;
        Word k0, k1;
        Word gp;
        Word sp;
        Word fp;
        Word ra;
      };
    };*/
    Word registers[32]{};
    std::map<std::string_view, int> nameToIndex{};

    Word &operator[](const int i) { return registers[i]; }
    const Word &operator[](const int i) const { return registers[i]; }
    Word &operator[](const std::string_view name) {
      return registers[nameToIndex.at(name)];
    }
    const Word &operator[](const std::string_view name) const {
      return registers[nameToIndex.at(name)];
    }

  } registers;
  struct SpecialRegisters {
    std::map<std::string_view, Word> registers{};
  } special;

  static GeneralPurposeRegisters initGPRs();
  static SpecialRegisters initSpecials();

  CPU() : registers{initGPRs()}, special{initSpecials()} {}

  void onReleaseChange();
};
} // namespace MIPS::arch::_32