#include "FloatPoint.hpp"
#include "FixedPoint.hpp"
#include <gtest/gtest.h>

using Float16 = FloatPoint<8>; // 8 бит дробной части

TEST(FloatPointTests, CanCreateFromFloat) {
    Float16 a(5.5f);
    EXPECT_FLOAT_EQ(a.ToFloat(), 5.5f);
}

TEST(FloatPointTests, CanAdd) {
    Float16 a(1.5f);
    Float16 b(2.5f);
    DecimalNumber* result = a + b;
    EXPECT_FLOAT_EQ(result->ToFloat(), 4.0f);
    delete result;
}

TEST(FloatPointTests, CanSubtract) {
    Float16 a(5.5f);
    Float16 b(2.0f);
    DecimalNumber* result = a - b;
    EXPECT_FLOAT_EQ(result->ToFloat(), 3.5f);
    delete result;
}

TEST(FloatPointTests, CanMultiply) {
    Float16 a(2.0f);
    Float16 b(3.5f);
    DecimalNumber* result = a * b;
    EXPECT_FLOAT_EQ(result->ToFloat(), 7.0f);
    delete result;
}

TEST(FloatPointTests, CanDivide) {
    Float16 a(10.0f);
    Float16 b(2.0f);
    DecimalNumber* result = a / b;
    EXPECT_FLOAT_EQ(result->ToFloat(), 5.0f);
    delete result;
}

TEST(FloatPointTests, DivisionByZeroThrows) {
    Float16 a(10.0f);
    Float16 b(0.0f);
    EXPECT_THROW(a / b, DivisionByZero);
}

TEST(FixedPointTests, CanCreateFromFloat) {
    FixedPoint<8, 8> a(3.25f);
    EXPECT_FLOAT_EQ(a.ToFloat(), 3.25f);
}

TEST(FixedPointTests, CanAdd) {
    FixedPoint<8, 8> a(1.25f);
    FixedPoint<8, 8> b(2.0f);
    DecimalNumber* result = a + b;
    EXPECT_FLOAT_EQ(result->ToFloat(), 3.25f);
    delete result;
}

TEST(FixedPointTests, CanSubtract) {
    FixedPoint<8, 8> a(4.5f);
    FixedPoint<8, 8> b(1.5f);
    DecimalNumber* result = a - b;
    EXPECT_FLOAT_EQ(result->ToFloat(), 3.0f);
    delete result;
}

TEST(FixedPointTests, CanMultiply) {
    FixedPoint<8, 8> a(1.5f);
    FixedPoint<8, 8> b(2.0f);
    DecimalNumber* result = a * b;
    EXPECT_FLOAT_EQ(result->ToFloat(), 3.0f);
    delete result;
}

TEST(FixedPointTests, CanDivide) {
    FixedPoint<8, 8> a(3.0f);
    FixedPoint<8, 8> b(1.5f);
    DecimalNumber* result = a / b;
    EXPECT_FLOAT_EQ(result->ToFloat(), 2.0f);
    delete result;
}

TEST(FixedPointTests, DivisionByZeroThrows) {
    FixedPoint<8, 8> a(5.0f);
    FixedPoint<8, 8> b(0.0f);
    EXPECT_THROW(a / b, DivisionByZero);
}

TEST(FixedPointTests, ThrowsOnOverflowPositive) {
    EXPECT_THROW(([]() { FixedPoint<8, 8> f(65536.0f); }()), FixedPointOutOfRange);
}

TEST(FixedPointTests, ThrowsOnOverflowNegative) {
    EXPECT_THROW(([]() { FixedPoint<8, 8> f(-65536.0f); }()), FixedPointOutOfRange);
}

TEST(FixedPointTests, HandlesMaxBoundaryCorrectly) {
    float maxValue = (1 << 8) - (1.0f / (1 << 8)); 
    FixedPoint<8, 8> a(maxValue);
    EXPECT_FLOAT_EQ(a.ToFloat(), maxValue);
}

TEST(FixedPointTests, HandlesMinBoundaryCorrectly) {
    float minValue = -((1 << 8)); 
    FixedPoint<8, 8> a(minValue);
    EXPECT_FLOAT_EQ(a.ToFloat(), minValue);
}
