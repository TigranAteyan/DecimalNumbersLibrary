#include <gtest/gtest.h>
#include "FloatPoint.hpp"
#include "FixedPoint.hpp"
#include "../MyExceptions/DivisionByZero.hpp"
#include "../MyExceptions/FixedPointOutOfRange.hpp"

TEST(FloatPointTests, CanCreateFromString) {
    FloatPoint a("1.25");
    EXPECT_FLOAT_EQ(a.ToFloat(), 1.25f);
}

TEST(FloatPointTests, CanAdd) {
    FloatPoint a("1.5");
    FloatPoint b("2.5");
    DecimalNumber* result = a + b;
    EXPECT_FLOAT_EQ(result->ToFloat(), 4.0f);
    delete result;
}

TEST(FloatPointTests, CanSubtract) {
    FloatPoint a("5.5");
    FloatPoint b("2.0");
    DecimalNumber* result = a - b;
    EXPECT_FLOAT_EQ(result->ToFloat(), 3.5f);
    delete result;
}

TEST(FloatPointTests, CanMultiply) {
    FloatPoint a("2.0");
    FloatPoint b("3.5");
    DecimalNumber* result = a * b;
    EXPECT_FLOAT_EQ(result->ToFloat(), 7.0f);
    delete result;
}

TEST(FloatPointTests, CanDivide) {
    FloatPoint a("10.0");
    FloatPoint b("2.0");
    DecimalNumber* result = a / b;
    EXPECT_FLOAT_EQ(result->ToFloat(), 5.0f);
    delete result;
}

TEST(FloatPointTests, DivisionByZeroThrows) {
    FloatPoint a("10.0");
    FloatPoint b("0.0");
    EXPECT_THROW(a / b, DivisionByZero);
}

TEST(FixedPointTests, CanCreateFromFloat) {
    FixedPoint<3, 4> a(3.25f);
    EXPECT_FLOAT_EQ(a.ToFloat(), 3.25f);
}

TEST(FixedPointTests, AdditionWorks) {
    FixedPoint<3,4> a(1.5f);
    FixedPoint<3,4> b(2.25f);
    DecimalNumber* result = a + b;
    EXPECT_NEAR(result->ToFloat(), 3.75f, 0.001f);
    delete result;
}

TEST(FixedPointTests, SubtractionWorks) {
    FixedPoint<3,4> a(5.0f);
    FixedPoint<3,4> b(1.75f);
    DecimalNumber* result = a - b;
    EXPECT_NEAR(result->ToFloat(), 3.25f, 0.001f);
    delete result;
}

TEST(FixedPointTests, MultiplicationWorks) {
    FixedPoint<3,4> a(2.0f);
    FixedPoint<3,4> b(3.0f);
    DecimalNumber* result = a * b;
    EXPECT_NEAR(result->ToFloat(), 6.0f, 0.001f);
    delete result;
}

TEST(FixedPointTests, DivisionWorks) {
    FixedPoint<3,4> a(6.0f);
    FixedPoint<3,4> b(2.0f);
    DecimalNumber* result = a / b;
    EXPECT_NEAR(result->ToFloat(), 3.0f, 0.001f);
    delete result;
}

TEST(FixedPointTests, DivisionByZeroThrows) {
    FixedPoint<3,4> a(6.0f);
    FixedPoint<3,4> b(0.0f);
    EXPECT_THROW({
        DecimalNumber* result = a / b;
        delete result;
    }, DivisionByZero);
}

TEST(FixedPointTests, ThrowsWhenOutOfRange) {
    EXPECT_THROW((FixedPoint<3,4>(16.0f)), FixedPointOutOfRange);
    EXPECT_THROW((FixedPoint<3,4>(-9.0f)), FixedPointOutOfRange);
}
