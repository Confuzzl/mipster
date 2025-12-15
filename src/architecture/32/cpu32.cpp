module arch32:cpu;

namespace MIPS::arch::_32 {
CPU::GeneralPurposeRegisters CPU::initGPRs() {
  GeneralPurposeRegisters out{};
  static constexpr std::string_view DEFAULT_NAMES[32] = {
      "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2",
      "t3",   "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5",
      "s6",   "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra",
  };
  for (auto i = 0; i < 31; i++) {
    out.nameToIndex.emplace(DEFAULT_NAMES[i], i);
  }
  return out;
}
CPU::SpecialRegisters CPU::initSpecials() {
  SpecialRegisters out{};
  if (getRelease() < 6) {
    out.registers.emplace("HI", Word{});
    out.registers.emplace("LO", Word{});
  }
  out.registers.emplace("PC", Word{});
  return out;
}
void CPU::onReleaseChange() { special = initSpecials(); }
} // namespace MIPS::arch::_32