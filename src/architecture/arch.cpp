module arch;

import computer32;

namespace MIPS::arch {
int RELEASE = 6;
int getRelease() { return RELEASE; }
void setRelease(const int r) {
  RELEASE = r;
  _32::computer.onReleaseChange();
}
} // namespace MIPS::arch
