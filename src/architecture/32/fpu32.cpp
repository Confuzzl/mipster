module arch32:fpu;

import arch;
import exception;
import formatted_register;

namespace MIPS::arch::_32 {
FReg *BaseFPU::FCRWrapper::get(const int i) {
  switch (i) {
  case 1:
  case 4:
    if (getRelease() == 5)
      return nullptr;
    break;
  case 25:
    throw std::logic_error{"FPU[25] (FCCR) not implemented!"};
  case 26:
    throw std::logic_error{"FPU[26] (FEXR) not implemented!"};
  case 28:
    throw std::logic_error{"FPU[28] (FENR) not implemented!"};
  }
  auto it = registers.find(i);
  if (it == registers.end())
    return nullptr;
  return &(it->second);
}

BaseFPU::FCRWrapper BaseFPU::initFCR() {
  using F = FReg::Field;
  using enum F::Accessibility;
  FCRWrapper out{};
  addFReg<0, "FIR">( // 1.Fig.6.11 1.Tab.6.5
      out, {{
               F{"0", 30, 31, R},
               F{"FREP", 29, R},
               F{"UFRP", 28, (getRelease() < 6) ? R : R0}, // typo on doc?
               F{"Impl", 24, 27, R},
               F{"Has2008", 23, R},
               F{"F64", 22, R},
               F{"L", 21, R},
               F{"W", 20, R},
               F{"3D", 19, R},
               F{"PS", 18, R},
               F{"D", 17, R},
               F{"S", 16, R},
               F{"ProcessorID", 8, 15, R},
               F{"Revision", 7, 0, R},
           }});
  addFReg<1, "UFR">( // 1.Fig.6.12 1.Tab.6.6
      out, {{
               F{"0", 1, 31, Z},
               F{"FR", 0, (getRelease() == 5) ? RW0 : R0},
           }});
  addFReg<4, "UNFR">( // 1.Fig.6.13 1.Tab.6.7
      out, {{
               F{"0", 1, 31, Z},
               F{"NFR", 0, (getRelease() == 5) ? W0 : R0},
           }});
  addFReg<31, "FCSR">( // 1.Fig.6.14 1.Tab.6.8
      out, {{
               F{"FCC", 25, 31, (getRelease() < 6) ? RW : R0},
               F{"FS", 24, RW},
               F{"FCC0", 23, (getRelease() < 6) ? RW0 : R0},
               F{"Impl", 21, 22, RW},
               F{"0", 20, R},
               F{"ABS2008", 19, R},
               F{"NAN2008", 18, R},
               F{"Cause", 12, 17, RW},
               F{"Enables", 7, 11, RW},
               F{"Flags", 2, 6, RW},
               F{"RM", 0, 2, RW},
           }});
  // addFReg<25, "FCRR">();
  // addFReg<26, "FEXR">();
  // addFReg<28, "FENR">();
  return out;
}

void BaseFPU::onReleaseChange() { FCR = initFCR(); }
} // namespace MIPS::arch::_32