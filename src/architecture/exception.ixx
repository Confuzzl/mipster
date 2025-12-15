export module exception;

export import <exception>;
export import <format>;

export namespace MIPS::arch {
enum struct Exception {
  RESET,                  // unimplemented
  SOFT_RESET,             // unimplemented
  NON_MASKABLE_INTERRUPT, // unimplemented
  MACHINE_CHECK,          // unimplemented
  ADDRESS_ERROR,          //
  TLB_REFILL,             // unimplemented
  EXECUTE_INHIBIT,        // unimplemented
  READ_INHIBIT,           // unimplemented
  TLB_INVALID,            // unimplemented
  TLB_MODIFIED,           // unimplemented
  CACHE_ERROR,            // unimplemented
  BUS_ERROR,              // unimplemented
  INTEGER_OVERFLOW,       //
  TRAP,                   //
  SYSTEM_CALL,            //
  BREAKPOINT,             // unimplemented
  RESERVED_INSTRUCTION,   //
  COPROCESSOR_UNUSABLE,   // unimplemented
  FLOATING_POINT,         //
  COPROCESSOR_2,          // unimplemented
  WATCH,                  // unimplemented
  INTERRUPT,              // unimplemented
};
enum struct ExceptionType {
  ASYNC_RESET,
  ASYNC_DEBUG,
  ASYNC,
  SYNC_DEBUG,
  SYNC,
};
void exception(const Exception exception) {}

enum struct BadBehavior {
  UNPREDICTABLE,
  UNDEFINED,
  UNSTABLE,
};
void badBehavior(const BadBehavior behavior) {
  switch (behavior) {
  case BadBehavior::UNPREDICTABLE: {
  }
  case BadBehavior::UNDEFINED: {
  }
  case BadBehavior::UNSTABLE: {
  }
  }
}

void registerFieldBadAccess() {}
} // namespace MIPS::arch