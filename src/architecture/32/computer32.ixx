export module computer32;

import <optional>;
import <variant>;

import arch;
import arch32;

export namespace MIPS::arch::_32 {

struct Cache {};

struct MMU {
  struct TLB {};
  struct FixedMapping {};

  std::variant<TLB, FixedMapping> scheme;
};

struct VirtualMemory {
  struct Segment {
    Word start, end;
  };

  static constexpr Segment useg{0x0000'0000, 0x7FFF'FFFF};  // user map
  static constexpr Segment kseg0{0x8000'0000, 0x9FFF'FFFF}; // kernel unmap
  static constexpr Segment kseg1{0xA000'0000, 0xBFFF'FFFF}; // k unmap uncache
  static constexpr Segment ksseg{0xC000'0000, 0xDFFF'FFFF}; // supervisor map
  static constexpr Segment kseg3{0xE000'0000, 0xFFFF'FFFF}; // kernel
};

struct Computer {
  std::optional<Cache> cache;
  MMU mmu;

  CPU cpu;
  std::variant<FPU32, FPU64> fpu = FPU32{};

  Coprocessor0 cp0;

  enum struct OperatingMode {
    DEBUG,      // unimplemented
    KERNEL,     //
    SUPERVISOR, // unimplemented
    USER,       //
  } operatingMode;
  // OperatingMode getOperatingMode() const { }

  void execute(Word addr);
  void onReleaseChange();
} computer;
} // namespace MIPS::arch::_32