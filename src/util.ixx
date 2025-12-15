export module util;

import arch;

export namespace MIPS::util {
using namespace arch;
unsigned int bitMask(const int from, const int to) {
  const auto size = to - from + 1;
  return ((1 << size) - 1) << from;
}
Word getBits(const Word word, const int from, const int to) {
  const auto size = to - from + 1;
  const Word mask = (1 << size) - 1;
  const Word shift = word >> from;
  return shift & mask;
}
} // namespace MIPS::util