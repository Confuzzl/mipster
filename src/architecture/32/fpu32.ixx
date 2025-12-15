export module arch32:fpu;

import arch;
// import computer32;
import util;
import formatted_register;
import <map>;
import <string_view>;
import exception;

import <type_traits>;

export namespace MIPS::arch::_32 {
struct BaseFPU {
  struct FCRWrapper {
    std::map<int, FReg> registers{};
    std::map<std::string_view, int> nameToIndex{};

    FReg *get(const int i);
    FReg *get(const std::string_view name) { return get(nameToIndex.at(name)); }
    template <typename T> FReg &operator[](const T key) {
      if (const auto maybe = get(key))
        return *maybe;
      throw std::logic_error{
          std::format("invalid unchecked access of FCR[{}]", key)};
    }
  } FCR;
  template <int I, FRegName name>
  static void addFReg(FCRWrapper &out, FReg &&freg) {
    const std::string_view str{name.m, name.SIZE};
    freg.name = str;
    out.nameToIndex.emplace(str, I);
    out.registers.emplace(I, std::move(freg));
  }
  static FCRWrapper initFCR();
  BaseFPU() : FCR{initFCR()} {}

  void onReleaseChange();
};
template <typename RegType> struct FPU : BaseFPU {
  RegType registers[32]{};
};
struct FPU32 : FPU<float> {};

struct FPU64 : FPU<double> {
  // template <auto Release> struct RegisterModelByRelease {
  //   enum struct Model { _32, _64 };
  // };
  // template <> struct RegisterModelByRelease<1> {
  //   enum struct Model {};
  // };
  // template <> struct RegisterModelByRelease<6> {
  //   enum struct Model { _64 };
  // };
  // static constexpr auto REGISTER_MODEL =
  //     RegisterModelByRelease<RELEASE>::Model::_64;
};
} // namespace MIPS::arch::_32