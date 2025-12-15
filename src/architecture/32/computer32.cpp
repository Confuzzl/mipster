module computer32;

import <variant>;

namespace MIPS::arch::_32 {
void Computer::onReleaseChange() {
  cp0.onReleaseChange();
  std::visit(
      [](auto &&fpu) {

      },
      fpu);
  //
}
} // namespace MIPS::arch::_32