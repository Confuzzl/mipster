module formatted_register;

import arch;
import exception;
import util;

namespace MIPS::arch {
Word FReg::operator[](const std::string_view name) const {
  const auto &field = fields[name];
  return util::getBits(value, field.start, field.end);
}

Word FReg::read() const {
  for (const auto &field : fields) {
    if (field.access ==
        Field::Accessibility::W0) // invalid read access should be implemented
                                  // in instruction impl
      throw std::logic_error{
          std::format("Coprocessor 1 (FPU) register {} field {} was read "
                      "with an accessibility of W0",
                      name, field.name)};
  }
  return value;
}
void FReg::write(const Word x) {
  for (const auto &field : fields) {
    const auto mask = util::bitMask(field.start, field.end);
    switch (field.access) {
    case Field::Accessibility::RW: {
      value &= ~mask;      // 0 out field bits
      value |= (x & mask); // write new bits
      break;
    }
    case Field::Accessibility::R: {
      // accepts hardware writes
      // all software writes are ignored
      break;
    }
    case Field::Accessibility::R0: {
      // all writes are ignored
      break;
    }
    case Field::Accessibility::Z: {
      if (getRelease() < 6) {
        // non zero writes are undefined
        if (util::getBits(x, field.start, field.end) != 0) {
          badBehavior(BadBehavior::UNDEFINED);
        }
      } else {
        // all writes are ignored
      }
      break;
    }
    case Field::Accessibility::RW0: {
      break;
    }
    case Field::Accessibility::W0: {
      break;
    }
    }
  }
}
} // namespace MIPS::arch