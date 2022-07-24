#include "../../lib/src/main_6502.h"
#include <gtest/gtest.h>

class M6502Test : public testing::Test {
public:
  Mem mem;
  CPU cpu;

  virtual void SetUp() { cpu.Reset(mem); }

  virtual void TearDown() {}
};

TEST_F(M6502Test, LDAImmediateCanLoadAValueIntoTheARegister) {
  // given:
  mem[0xFFFC] = CPU::INS_LDA_IM;
  mem[0xFFFD] = 0x84;

  // when:
  cpu.Execute(2, mem);

  // then:
  EXPECT_EQ(cpu.A, 0x84);
}

TEST_F(M6502Test, LDAZeroPageCanLoadAValueIntoTheARegister) {
  // given:
  mem[0xFFFC] = CPU::INS_LDA_ZP;
  mem[0xFFFD] = 0x42;
  mem[0x0042] = 0x37;

  // when:
  cpu.Execute(3, mem);

  // then:
  EXPECT_EQ(cpu.A, 0x37);
}

TEST_F(M6502Test, LDAZeroPageXCanLoadAValueIntoTheARegisterWhenItWraps) {
  // given:
  cpu.X = 0xFF;

  mem[0xFFFC] = CPU::INS_LDA_ZPX;
  mem[0xFFFD] = 0x80;
  mem[0x007F] = 0x37;

  // when:
  cpu.Execute(4, mem);

  // then:
  EXPECT_EQ(cpu.A, 0x37);
}
