module arch32:co0;

namespace MIPS::arch::_32 {
Coprocessor0::BanksWrapper Coprocessor0::initBanks() {
  using F = FReg::Field;
  using enum F::Accessibility;
  BanksWrapper out{};
  if (getRelease() < 6) { // 3.Fig.9.32
    addFReg<12, 0, "Status">(out, {{
                                      F{"CU", 29, 31, RW},
                                      F{"RW", 28, RW},
                                      F{"0_1", 27, Z},
                                      F{"FR", 26, R},
                                      F{"0_2", 25, Z},
                                      F{"MX", 24, R}, // NOTE module
                                      F{"0_3", 23, Z},
                                      F{"BEV", 22, RW},
                                      F{"0_4", 21, Z},
                                      F{"SR", 20, RW},
                                      F{"NMI", 19, RW},
                                      F{"ASE", 18, Z}, // NOTE ASE
                                      F{"Impl", 16, 17, Z},
                                      F{"IM27", 10, 15, RW},
                                      F{"IM01", 8, 9, RW},
                                      F{"0_5", 5, 7, R},
                                      // F{"KSU", 3, 4, RW}, NOTE supervisor
                                      F{"UM", 4, RW},
                                      F{"R0", 3, R},
                                      F{"ERL", 2, RW},
                                      F{"EXL", 1, RW},
                                      F{"IE", 0, RW},

                                  }});
  } else { // 3.Fig.9.33
    addFReg<12, 0, "Status">(out, {{
                                      F{"CU", 29, 31, RW},
                                      F{"RW", 28, RW},
                                      F{"0_1", 27, Z},
                                      F{"FR", 26, R},
                                      F{"0_2", 25, Z},
                                      F{"MX", 24, R}, // NOTE module
                                      F{"0_3", 23, Z},
                                      F{"BEV", 22, RW},
                                      F{"0_4", 21, Z},
                                      F{"SR", 20, RW},
                                      F{"NMI", 19, RW},
                                      F{"ASE", 18, Z}, // NOTE ASE
                                      F{"Impl", 16, 17, Z},
                                      F{"IM27", 10, 15, RW},
                                      F{"IM01", 8, 9, RW},
                                      F{"0_5", 5, 7, R},
                                      // F{"KSU", 3, 4, RW}, NOTE supervisor
                                      F{"UM", 4, RW},
                                      F{"R0", 3, R},
                                      F{"ERL", 2, RW},
                                      F{"EXL", 1, RW},
                                      F{"IE", 0, RW},

                                  }});
  }
  return out;
}

void Coprocessor0::onReleaseChange() { wrapper = initBanks(); }
} // namespace MIPS::arch::_32