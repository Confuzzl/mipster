export module simulator;

// import mips;
import <cstdlib>;
import <cstddef>;
import <vector>;
import <array>;
import <memory>;

import debug;

export namespace MIPS::simulator {
// using namespace architecture;
// struct Execution {
//   struct RegisterDelta {
//     int reg;
//     int diff;
//   };
//   struct MemoryDelta {
//     Word addr;
//     int diff;
//   };
//
//   void execute() {}
// };
//
// struct Computer {
//   CPU _cpu;
//   FPU fpu;
//
//   Computer() {}
//
//   struct Memory {
//     static constexpr auto PAGE_SIZE = 0x1000;
//     using Page = std::unique_ptr<Byte[]>;
//     static constexpr auto CHAPTER_SIZE = 0x1000;
//     using Chapter = std::unique_ptr<Page[]>;
//     static constexpr auto BOOK_SIZE = 0x100;
//     using Book = Chapter[BOOK_SIZE];
//     Book memory = {};
//
//     using InitializerFunc = Page (*)(std::size_t);
//     static constexpr InitializerFunc INITIALIZE_TO_ZERO =
//         [](std::size_t size) { // technically cant take addr of lib func
//           return std::make_unique<Byte[]>(size);
//         };
//     static constexpr InitializerFunc INITIALIZE_UNDEFINED =
//         [](std::size_t size) {
//           return std::make_unique_for_overwrite<Byte[]>(size);
//         };
//     static constexpr auto PAGE_INITIALIZER = INITIALIZE_TO_ZERO;
//
//     Memory() {
//       (memory[0] = std::make_unique<Page[]>(CHAPTER_SIZE))[0] =
//           PAGE_INITIALIZER(PAGE_SIZE);
//
//       println("{}", memory[0][0][0]);
//     }
//
//     static constexpr Word TEXT_START = 0x0000'0000;
//     static constexpr Word TEXT_END = 0x03ff'ffff;
//
//     static constexpr Word DATA_START = 0x0400'0000;
//     static constexpr Word DATA_END = 0x07ff'ffff;
//
//     static constexpr Word STACK_START = 0x7fff'ffff;
//
//     static constexpr Word KERNEL_START = 0x8000'0000;
//
//     std::tuple<int, int, int> indices(const Word addr) const {
//       const auto top = std::div(addr, PAGE_SIZE * CHAPTER_SIZE);
//       const auto chapter = top.quot;
//       const auto bot = std::div(top.rem, CHAPTER_SIZE);
//       const auto page = bot.quot;
//       const auto byte = bot.rem;
//
//       return {chapter, page, byte};
//     }
//
//     void write(const Word addr, const Byte byte) {
//       if (addr >= KERNEL_START || addr <= DATA_END) {
//       } else {
//       }
//     }
//     void read(const Word addr) {}
//
//   } memory;
//
//   // using MemPage = std::array<std::byte, PAGE_SIZE>;
// };
} // namespace MIPS::simulator