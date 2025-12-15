export module arch32:co0;

import <string_view>;
import <map>;
import <utility>;

import arch;
import formatted_register;
import exception;

export namespace MIPS::arch::_32 {
struct Coprocessor0 {

  // OPTIONAL
  // struct Register0 {
  //  Word Index;
  //  Word MVPControl;
  //  Word MVPConf0;
  //  Word MVPConf1;
  //};

  // OPTIONAL
  // struct Register1 {
  //  Word Random;       // unclear if optional in release 6 or deprecated
  //  Word VPEControl;   // optional
  //  Word VPEConf0;     // optional
  //  Word VPEConf1;     // optional
  //  Word YQMask;       // optional
  //  Word VPESchedule;  // optional
  //  Word VPEScheFBack; // optional
  //  Word VPEOpt;       // optional
  //};

  // OPTIONAL
  // struct Register2 {
  //  Word EntryLoO;
  //  Word TCStatus;
  //  Word TCBind;
  //  Word TCRestart;
  //  Word TCHalt;
  //  Word TCContext;
  //  Word TCSchedu1e;
  //  Word TCScheFBack;
  //};

  // OPTIONAL
  // struct Register3 {
  //  Word EntryLo1;
  //  Word TCOpt; // 7
  //};

  // OPTIONAL
  // struct Register4 {
  //  Word Context;
  //  Word ContextConfig;
  //  Word UserLocal;
  //  Word _unnamed;
  //};

  // OPTIONAL
  // struct Register5 {
  //  Word PageMask;
  //  Word PageGrain;
  //  Word SegCt10;
  //  Word SegCtl1;
  //  Word SegCt12;
  //  Word PWBase;
  //  Word PWField;
  //  Word PWSize;
  //};

  // OPTIONAL
  // struct Register6 {
  //  Word Wired;
  //  Word SRSConf1;
  //  Word SRSConf1;
  //  Word SRSConf2;
  //  Word SRSConf3;
  //  Word SRSConf4;
  //  Word PWCtl;
  //};

  struct RegisterBank {
    std::map<int, FReg> registers{};
    std::map<std::string_view, int> nameToSel{};
  };
  struct BanksWrapper {
    std::map<int, RegisterBank> banks{};
    std::map<std::string_view, std::pair<int, int>> nameToIndexSel{};

  } wrapper;

  template <int reg, int sel, FRegName name>
  static void addFReg(BanksWrapper &out, FReg &&freg) {
    auto it = out.banks.find(reg);
    const std::string_view str{name.m, name.SIZE};
    freg.name = str;
    auto &bank = (it != out.banks.end())
                     ? it->second
                     : out.banks.emplace(reg, RegisterBank{}).first->second;
    bank.registers.emplace(sel, std::move(freg));
    bank.nameToSel.emplace(str, sel);
    out.nameToIndexSel.emplace(str, std::pair<int, int>{reg, sel});
  }
  static BanksWrapper initBanks();

  Coprocessor0() : wrapper{initBanks()} {}

  void onReleaseChange();

  // RegisterBank *get(const int i) {
  //   switch (i) {
  //   default: {
  //     return nullptr;
  //   }
  //   }
  // }

  struct Register7 {
    Word HWREna; // required >= 2
                 // 1-7 reserved
  };

  struct Register8 {
    Word BadVAddr;
    Word BadInstr;  // required >= 6
    Word BadInstrP; // required >= 6
  };

  struct Register9 {
    Word Count;
    // 6-7 impl dep
  };

  // OPTIONAL
  // struct Register10 {
  //  Word EntryHi;
  //  Word GuestCt11; // 4
  //  Word GuestCt12; // 5
  //  Word GuestCt13; // 6
  //};

  // OPTIONAL
  // struct Register11 {
  //  Word Compare;
  //  Word GuestCtl0Ext; // 4
  //  // 6-7 impl dep
  //};

  // struct Register12 {
  //   Word Status;
  //   Word IntCtl;    // required >= 2
  //   Word SRSCt1;    // required >= 2
  //   Word SRSMap;    // required >= 2 and shadow sets (NO SHADOW SETS)
  //   Word View_IPL;  // optional
  //   Word SRSMap2;   // optional
  //   Word GuestCtlO; // optional
  //   Word GTOffset;  // optional
  //};

  struct Register13 {
    Word Cause;
    Word View_RIPL; // 4 optional
    Word NestedExc; // 5 optional
  };

  struct Register14 {
    Word EPC;
    Word NestedEPC; // 2 optional
  };

  struct Register15 {
    Word PRId;
    Word EBase;     // required >= 2
    Word CDMMBase;  // optional
    Word CMGCRBase; // optional
  };

  struct Register16 {
    struct {

    } Config;
    Word Config1;
    Word Config2; // optional
    Word Config3; // optional
    Word Config4; // optional
    Word Config5; // optional
                  // 6-7 impl dep
  };

  // OPTIONAL
  // struct Register17 {
  //  Word LLAddr;
  //};

  // OPTIONAL
  // struct Register18 {
  //  // TODO
  //};

  // OPTIONAL
  // struct Register19 {
  //  // TODO
  //};

  // RESERVED
  struct Register20 {
    Word _unnamed;
  };

  // RESERVED
  struct Register21 {};

  // IMPL DEP
  struct Register22 {};

  // OPTIONAL
  // struct Register23 {
  //  Word Debug;
  //  Word TraceControl;
  //  Word TraceControl2;
  //  Word UserTraceData1;
  //  Word TraceIBPC;
  //  Word TraceDBPC;
  //  Word Debug2;
  //};

  // OPTIONAL
  // struct Register24 {
  //  Word DEPC;
  //  Word TraceContol3;   // 2 misspelled in documentation?
  //  Word UserTraceData2; // 3
  //};

  // RECOMMENDED
  // struct Register25 {
  //  // TODO
  //};

  // OPTIONAL
  // struct Register26 {
  //  Word ErrCtl;
  //};

  // OPTIONAL
  // struct Register27 {
  //  Word CacheErr; // 0-3
  //  // TODO
  //};

  // struct Register28 {
  //   Word TagLo;  // optional / required if cache
  //   Word DataLo; // optional
  //   // TODO
  // };

  // struct Register29 {
  //   Word TagHi;  // optional / required if cache
  //   Word DataHi; // optional
  //   // TODO
  // };

  struct Register30 {
    Word ErrorEPC;
  };

  //// OPTIONAL
  // struct Register31 {
  //   Word DESAVE;
  //   Word KScratch1; // 2
  //   Word KScratch2; // 3
  //   Word KScratch3; // 4
  //   Word KScratch4; // 5
  //   Word KScratch5; // 6
  //   Word KScratch6; // 7
  //   // TODO
  // };

  // enum struct CauseCode {
  //   AdEL = 4,
  //   AdES = 5,
  //   Sys = 8,
  //   Ov = 12,
  //   FPE = 15,
  // };
  // template <CauseCode code> constexpr std::string_view causeDescription();

  // template <> constexpr std::string_view
  // causeDescription<CauseCode::AdEL>()
  // {
  //   return "Address error exception (load or instruction fetch)";
  // }
  // template <> constexpr std::string_view
  // causeDescription<CauseCode::AdES>()
  // {
  //   return "Address error exception (store)";
  // }
  // template <> constexpr std::string_view
  // causeDescription<CauseCode::Sys>() {
  //   return "Syscall exception";
  // }
  // template <> constexpr std::string_view causeDescription<CauseCode::Ov>()
  // {
  //   return "Arithmetic overflow exception";
  // }
  // template <> constexpr std::string_view
  // causeDescription<CauseCode::FPE>() {
  //   return "Floating point exception";
  // }
};
} // namespace MIPS::arch::_32