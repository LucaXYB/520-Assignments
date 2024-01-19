#include "Complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(Fractions, BascisAdd_1) {
        Complex a = (Complex) { 2.0, 3.0 },
                b = (Complex) { 4.0, 5.0};
        EXPECT_EQ(add(a,b).real,6.0);
        EXPECT_EQ(add(a,b).im,8.0);

    }

    TEST(Fractions, BascisAdd_2) {
        Complex a = (Complex) { 2.0, 3.0 },
                b = (Complex) { -2.0, 3.0 };
        EXPECT_EQ(add(a,b).real, 0.0);
        EXPECT_EQ(add(a,b).im, 6.0);

    }

    TEST(Fractions, BasicsMult_1) {
        Complex a = (Complex) { 2.0, 3.0},
                b = (Complex) { 4.0, 5.0};

        EXPECT_EQ(multiply(a,b).real, -7.0);
        EXPECT_EQ(multiply(a,b).im, 22.0);
    }

    TEST(Fractions, BasicsMult_2) {
        Complex a = (Complex) { 2.0, 3.0},
                b = (Complex) { 3.0, 2.0};

        EXPECT_EQ(multiply(a,b).real, 0);
        EXPECT_EQ(multiply(a,b).im, 13.0);
    }

    TEST(Fractions, BasicsNegate) {
        Complex a = (Complex) { 2.0, 3.0};

        EXPECT_EQ(negate(a).real,-2.0);
        EXPECT_EQ(negate(a).im,-3.0);
    }

    TEST(Fractions, BasicsNegate_2) {
        Complex a = (Complex) { 3.0, 2.0 };

        EXPECT_EQ(negate(a).real,-3.0);
        EXPECT_EQ(negate(a).im,-2.0);
    }

    TEST(Fractions, BasicsMagn) {
        Complex a = (Complex) {3.0, -4.0};

        EXPECT_EQ(magnitude(a), 5.0);
    }

    TEST(Fractions, BasicsMagn_2) {
        Complex a = (Complex) {-5.0, 12.0};

        EXPECT_EQ(magnitude(a), 13.0);
    }
}
