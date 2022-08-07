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
  CPU CPUCopy = cpu;
  s32 CyclesUses = cpu.Execute(2, mem);

  // then:
  EXPECT_EQ(cpu.A, 0x84);
  EXPECT_EQ(CyclesUses, 2);
  EXPECT_FALSE(cpu.Z);
  EXPECT_TRUE(cpu.N);
  EXPECT_EQ(cpu.C, CPUCopy.C);
  EXPECT_EQ(cpu.I, CPUCopy.I);
  EXPECT_EQ(cpu.D, CPUCopy.D);
  EXPECT_EQ(cpu.B, CPUCopy.B);
  EXPECT_EQ(cpu.V, CPUCopy.V);
}

TEST_F(M6502Test, LDAZeroPageCanLoadAValueIntoTheARegister) {
  // given:
  mem[0xFFFC] = CPU::INS_LDA_ZP;
  mem[0xFFFD] = 0x42;
  mem[0x0042] = 0x37;

  // when:
  CPU CPUCopy = cpu;
  s32 CyclesUses = cpu.Execute(3, mem);

  // then:
  EXPECT_EQ(cpu.A, 0x37);
  EXPECT_EQ(CyclesUses, 3);
  EXPECT_FALSE(cpu.Z);
  EXPECT_FALSE(cpu.N);
  EXPECT_EQ(cpu.C, CPUCopy.C);
  EXPECT_EQ(cpu.I, CPUCopy.I);
  EXPECT_EQ(cpu.D, CPUCopy.D);
  EXPECT_EQ(cpu.B, CPUCopy.B);
  EXPECT_EQ(cpu.V, CPUCopy.V);
}

TEST_F(M6502Test, LDAZeroPageXCanLoadAValueIntoTheARegister) {
  // given:
  cpu.X = 5;

  mem[0xFFFC] = CPU::INS_LDA_ZPX;
  mem[0xFFFD] = 0x42;
  mem[0x0047] = 0x37;

  // when:
  CPU CPUCopy = cpu;
  s32 CyclesUses = cpu.Execute(4, mem);

  // then:
  EXPECT_EQ(cpu.A, 0x37);
  EXPECT_EQ(CyclesUses, 4);
  EXPECT_FALSE(cpu.Z);
  EXPECT_FALSE(cpu.N);
  EXPECT_EQ(cpu.C, CPUCopy.C);
  EXPECT_EQ(cpu.I, CPUCopy.I);
  EXPECT_EQ(cpu.D, CPUCopy.D);
  EXPECT_EQ(cpu.B, CPUCopy.B);
  EXPECT_EQ(cpu.V, CPUCopy.V);
}

TEST_F(M6502Test, LDAZeroPageXCanLoadAValueIntoTheARegisterWhenItWraps) {
  cpu.X = 0xFF;

  mem[0xFFFC] = CPU::INS_LDA_ZPX;
  mem[0xFFFD] = 0x80;
  mem[0x007F] = 0x37;

  CPU CPUCopy = cpu;
  s32 CyclesUses = cpu.Execute(4, mem);

  EXPECT_EQ(cpu.A, 0x37);
  EXPECT_EQ(CyclesUses, 4);
  EXPECT_FALSE(cpu.Z);
  EXPECT_FALSE(cpu.N);
  EXPECT_EQ(cpu.C, CPUCopy.C);
  EXPECT_EQ(cpu.I, CPUCopy.I);
  EXPECT_EQ(cpu.D, CPUCopy.D);
  EXPECT_EQ(cpu.B, CPUCopy.B);
  EXPECT_EQ(cpu.V, CPUCopy.V);
}

#if 0
int main() {
  Mem mem;
  CPU cpu;
  cpu.Reset(mem);
  // start - inline a little program
  mem[0xFFFC] = CPU::INS_JSR;
  mem[0xFFFD] = 0x42;
  mem[0xFFFE] = 0x42;
  mem[0x4242] = CPU::INS_LDA_IM;
  mem[0x4243] = 0x84;
  // end - inline a little program
  cpu.Execute(3, mem);
  return 0;
}
#endif
