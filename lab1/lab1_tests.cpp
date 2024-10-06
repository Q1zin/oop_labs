#include <iostream>
#include "gtest/gtest.h"
#include "BitArray.h"
#include <type_traits>

TEST(BitArrayTest, DefaultConstructor) {
  BitArray* bitArray = new BitArray();
  ASSERT_EQ(bitArray->size(), 0);
  ASSERT_TRUE(bitArray->empty());
}

TEST(BitArrayTest, ConstructorWithSize) {
  BitArray* bitArray = new BitArray(10);
  ASSERT_EQ(bitArray->size(), 10);
  ASSERT_EQ(bitArray->count(), 0);
  ASSERT_FALSE(bitArray->empty());
}

TEST(BitArrayTest, ConstructorWithValue) {
  BitArray* bitArray = new BitArray(10, 5);
  ASSERT_EQ(bitArray->size(), 10);
  ASSERT_EQ(bitArray->count(), 2);
  ASSERT_EQ(bitArray->to_string(), "0000000101");
}

TEST(BitArrayTest, ConstructorCopy) {
  BitArray* bitArray = new BitArray(10, 5);
  BitArray* bitArrayCopy = new BitArray(*bitArray);
  ASSERT_EQ(bitArrayCopy->size(), 10);
  ASSERT_EQ(bitArrayCopy->count(), 2);
  ASSERT_EQ(bitArrayCopy->to_string(), "0000000101");
}

TEST(BitArrayTest, SwapArrays) {
  BitArray* bitArray1 = new BitArray(10, 5);
  BitArray* bitArray2 = new BitArray(5, 1);
  bitArray1->swap(*bitArray2);
  ASSERT_EQ(bitArray1->size(), 5);
  ASSERT_EQ(bitArray1->to_string(), "00001");
  ASSERT_EQ(bitArray2->size(), 10);
  ASSERT_EQ(bitArray2->to_string(), "0000000101");
}

TEST(BitArrayTest, Assignment) {
  BitArray bitArray(10, 5);
  BitArray bitArray2;
  bitArray2 = bitArray;
  ASSERT_EQ(bitArray2.size(), 10);
  ASSERT_EQ(bitArray2.to_string(), "0000000101");
}

TEST(BitArrayTest, AssignmentSelf) {
  BitArray bitArray(10, 5);
  bitArray = bitArray;
  ASSERT_EQ(bitArray.size(), 10);
  ASSERT_EQ(bitArray.to_string(), "0000000101");
}

TEST(BitArrayTest, ConstructorWithInvalidSize) {
  ASSERT_THROW(BitArray(-1), std::invalid_argument);
}

TEST(BitArrayTest, ResizeInvalidSize) {
  BitArray* bitArray = new BitArray(10, 5);
  ASSERT_THROW(bitArray->resize(-5), std::invalid_argument);
}

TEST(BitArrayTest, ResizeLess) {
  BitArray* bitArray = new BitArray(10, 5);
  bitArray->resize(5);
  ASSERT_EQ(bitArray->size(), 5);
  ASSERT_EQ(bitArray->to_string(), "00101");
}

TEST(BitArrayTest, ResizeGreater) {
  BitArray* bitArray = new BitArray(10, 5);
  bitArray->resize(20);
  ASSERT_EQ(bitArray->size(), 20);
  ASSERT_EQ(bitArray->to_string(), "00000000000000000101");
}

TEST(BitArrayTest, ResizeGreaterTrue) {
  BitArray* bitArray = new BitArray(10, 5);
  bitArray->resize(20, true);
  ASSERT_EQ(bitArray->size(), 20);
  ASSERT_EQ(bitArray->to_string(), "11111111110000000101");
}

TEST(BitArrayTest, CheckPushBack) {
  BitArray* bitArray = new BitArray(3, 5);
  bitArray->push_back(1);
  bitArray->push_back(1);
  bitArray->push_back(0);
  bitArray->push_back(1);
  bitArray->push_back(1);
  ASSERT_EQ(bitArray->size(), 8);
  ASSERT_EQ(bitArray->count(), 6);
  ASSERT_EQ(bitArray->to_string(), "11011101");
}

TEST(BitArrayTest, CheckClear) {
  BitArray* bitArray = new BitArray(3, 5);
  bitArray->clear();
  ASSERT_EQ(bitArray->size(), 0);
  ASSERT_EQ(bitArray->to_string(), "");
}

TEST(BitArrayTest, SetOutOfRange) {
  BitArray* bitArray = new BitArray(3, 5);
  ASSERT_THROW(bitArray->set(5), std::out_of_range);
}

TEST(BitArrayTest, CheckSetValue) {
  BitArray* bitArray = new BitArray(2);
  bitArray->set(0);
  bitArray->set(1, 0);
  ASSERT_EQ(bitArray->to_string(), "01");
}

TEST(BitArrayTest, CheckSetAll) {
  BitArray* bitArray = new BitArray(65);
  bitArray->set();
  ASSERT_EQ(bitArray->count(), 65);
}

TEST(BitArrayTest, CheckResetOutOfRange) {
  BitArray* bitArray = new BitArray(65);
  ASSERT_THROW(bitArray->reset(65), std::out_of_range);
}

TEST(BitArrayTest, CheckResetValue) {
  BitArray* bitArray = new BitArray(5, 0b11111);
  bitArray->reset(1);
  ASSERT_EQ(bitArray->to_string(), "11101");
}

TEST(BitArrayTest, CheckResetAll) {
  BitArray* bitArray = new BitArray(6);
  bitArray->reset();
  ASSERT_EQ(bitArray->to_string(), "000000");
}

TEST(BitArrayTest, CheckAny) {
  BitArray* bitArray = new BitArray(6, 3);
  ASSERT_EQ(bitArray->any(), true);
  bitArray->reset();
  ASSERT_EQ(bitArray->any(), false);
}

TEST(BitArrayTest, CheckNone) {
  BitArray* bitArray = new BitArray(6, 3);
  ASSERT_EQ(!bitArray->none(), true);
  bitArray->reset();
  ASSERT_EQ(!bitArray->none(), false);
}

TEST(BitArrayTest, CheckIndex) {
  BitArray* bitArray = new BitArray(6, 5);
  ASSERT_EQ((*bitArray)[0], true);
  ASSERT_EQ((*bitArray)[1], false);
  ASSERT_EQ((*bitArray)[2], true);
  ASSERT_EQ((*bitArray)[3], false);
}

TEST(BitArrayTest, CheckInvert) {
  BitArray* bitArray = new BitArray(6, 5);
  ASSERT_EQ((~(*bitArray)).to_string(), "111010");
}

TEST(BitArrayTest, CheckCount) {
  BitArray* bitArray = new BitArray(6, 5);
  ASSERT_EQ(bitArray->count(), 2);
  bitArray->resize(100);
  bitArray->set();
  ASSERT_EQ(bitArray->count(), 100);
  bitArray->resize(64);
  ASSERT_EQ(bitArray->count(), 64);
}

TEST(BitArrayTest, CheckSize) {
  BitArray* bitArray = new BitArray(6, 5);
  ASSERT_EQ(bitArray->size(), 6);
  bitArray->resize(100);
  ASSERT_EQ(bitArray->size(), 100);
  bitArray->resize(64);
  ASSERT_EQ(bitArray->size(), 64);
}

TEST(BitArrayTest, CheckEmpty) {
  BitArray* bitArray = new BitArray(6, 5);
  ASSERT_EQ(bitArray->empty(), false);
  bitArray->resize(0);
  ASSERT_EQ(bitArray->empty(), true);
}

TEST(BitArrayTest, CheckToString) {
  BitArray* bitArray = new BitArray(6, 5);
  ASSERT_EQ(bitArray->to_string(), "000101");
}

TEST(BitArrayTest, CheckANDAssigInvalidArgument) {
  BitArray* bitArray1 = new BitArray(5);
  BitArray* bitArray2 = new BitArray(10);
  ASSERT_THROW((*bitArray1) &= (*bitArray2), std::invalid_argument);
}

TEST(BitArrayTest, CheckANDAssig) {
  BitArray* bitArray1 = new BitArray(5, 5);
  BitArray* bitArray2 = new BitArray(5, 2);
  (*bitArray1) &= (*bitArray2);
  ASSERT_EQ(bitArray1->to_string(), "00000");
}

TEST(BitArrayTest, CheckORAssigInvalidArgument) {
  BitArray* bitArray1 = new BitArray(5);
  BitArray* bitArray2 = new BitArray(10);
  ASSERT_THROW((*bitArray1) |= (*bitArray2), std::invalid_argument);
}

TEST(BitArrayTest, CheckORAssig) {
  BitArray* bitArray1 = new BitArray(5, 5);
  BitArray* bitArray2 = new BitArray(5, 2);
  (*bitArray1) |= (*bitArray2);
  ASSERT_EQ(bitArray1->to_string(), "00111");
}

TEST(BitArrayTest, CheckXORAssigInvalidArgument) {
  BitArray* bitArray1 = new BitArray(5);
  BitArray* bitArray2 = new BitArray(10);
  ASSERT_THROW((*bitArray1) ^= (*bitArray2), std::invalid_argument);
}

TEST(BitArrayTest, CheckXORAssig) {
  BitArray* bitArray1 = new BitArray(5, 21);
  BitArray* bitArray2 = new BitArray(5, 2);
  (*bitArray1) ^= (*bitArray2);
  ASSERT_EQ(bitArray1->to_string(), "10111");
}

TEST(BitArrayTest, CheckAND) {
  BitArray* bitArray1 = new BitArray(5, 5);
  BitArray* bitArray2 = new BitArray(5, 2);
  ASSERT_EQ(((*bitArray1) & (*bitArray2)).to_string(), "00000");
}

TEST(BitArrayTest, CheckOR) {
  BitArray* bitArray1 = new BitArray(5, 5);
  BitArray* bitArray2 = new BitArray(5, 2);
  ASSERT_EQ(((*bitArray1) | (*bitArray2)).to_string(), "00111");
}

TEST(BitArrayTest, CheckXOR) {
  BitArray* bitArray1 = new BitArray(5, 21);
  BitArray* bitArray2 = new BitArray(5, 2);
  ASSERT_EQ(((*bitArray1) ^ (*bitArray2)).to_string(), "10111");
}

TEST(BitArrayTest, CheckEqually) {
  BitArray* bitArray1 = new BitArray(5, 21);
  BitArray* bitArray2 = new BitArray(5, 2);
  ASSERT_EQ((*bitArray1) == (*bitArray2), false);
  bitArray1->set();
  bitArray2->set();
  ASSERT_EQ((*bitArray1) == (*bitArray2), true);
}

TEST(BitArrayTest, CheckNotEqually) {
  BitArray* bitArray1 = new BitArray(5, 21);
  BitArray* bitArray2 = new BitArray(5, 2);
  ASSERT_EQ((*bitArray1) != (*bitArray2), true);
  bitArray1->set();
  bitArray2->set();
  ASSERT_EQ((*bitArray1) != (*bitArray2), false);
}

TEST(BitArrayTest, ShiftToLeftAssignInvalidArgument) {
  BitArray* bitArray = new BitArray(5, 5);
  ASSERT_THROW((*bitArray) <<= -5, std::invalid_argument);
}

TEST(BitArrayTest, ShiftToLeftAssign) {
  BitArray* bitArray = new BitArray(100, 4326);
  BitArray* bitArray2 = new BitArray(*bitArray);
  ASSERT_EQ((*bitArray) <<= 1000, bitArray2->reset());

  BitArray* bitArray3 = new BitArray(100, 0);
  for (int i = 0; i <= 50; i+=10)
    bitArray3->set(i);

  (*bitArray3) <<= 20;
  for (int i = 20; i <= 70; i+=10)
    ASSERT_EQ((*bitArray3)[i], true);

  ASSERT_EQ(bitArray3->count(), 6);
}

TEST(BitArrayTest, ShiftToLeft) {
  BitArray* bitArray = new BitArray(100, 4326);
  BitArray* bitArray2 = new BitArray(*bitArray);
  ASSERT_EQ((*bitArray) << 1000, bitArray2->reset());

  BitArray* bitArray3 = new BitArray(100, 0);
  for (int i = 0; i <= 50; i+=10)
    bitArray3->set(i);

  ASSERT_EQ(((*bitArray3) << 20).to_string(), "0000000000000000000000000000010000000001000000000100000000010000000001000000000100000000000000000000");

  ASSERT_EQ(((*bitArray3) << 20).count(), 6);
}

TEST(BitArrayTest, ShiftToRightAssignInvalidArgument) {
  BitArray* bitArray = new BitArray(5, 5);
  ASSERT_THROW((*bitArray) >>= -5, std::invalid_argument);
}

TEST(BitArrayTest, ShiftToRightAssign) {
  BitArray* bitArray = new BitArray(100, 4326);
  BitArray* bitArray2 = new BitArray(*bitArray);
  ASSERT_EQ((*bitArray) >>= 1000, bitArray2->reset());

  BitArray* bitArray3 = new BitArray(100, 0);
  for (int i = 0; i <= 50; i+=10)
    bitArray3->set(i);

  (*bitArray3) >>= 20;
  for (int i = 0; i <= 30; i+=10)
    ASSERT_EQ((*bitArray3)[i], true);

  ASSERT_EQ(bitArray3->count(), 4);
}

TEST(BitArrayTest, ShiftToRight) {
  BitArray* bitArray = new BitArray(100, 4326);
  BitArray* bitArray2 = new BitArray(*bitArray);
  ASSERT_EQ((*bitArray) >> 1000, bitArray2->reset());

  BitArray* bitArray3 = new BitArray(100, 0);
  for (int i = 0; i <= 50; i+=10)
    bitArray3->set(i);

  ASSERT_EQ(((*bitArray3) >> 20).to_string(), "0000000000000000000000000000000000000000000000000000000000000000000001000000000100000000010000000001");

  ASSERT_EQ(((*bitArray3) >> 20).count(), 4);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}