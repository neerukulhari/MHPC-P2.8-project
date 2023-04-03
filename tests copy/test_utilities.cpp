#include <gtest/gtest.h>
#include "utilities.h"

TEST(AzzeroTest, ZeroArray) {
    /* Create an array and initialize it to some non-zero values */
    const int n = 5;
    double a[n] = {1.0, 2.0, 3.0, 4.0, 5.0};

    /* Call the function to be tested */
    azzero(a, n);

    /* Check that the array has been zeroed out */
    for (int i = 0; i < n; ++i) {
        EXPECT_EQ(0.0, a[i]);
    }
}


TEST(PBCTest, XisGreater) {
    /* Set up the input values */
    const double x = 2.5;
    const double boxby2 = 1.0;

    /* Call the function to be tested */
    const double result = pbc(x, boxby2);

    /* Check that the function returns the expected output */
    EXPECT_DOUBLE_EQ(0.5, result);
}

TEST(PBCTest, XisSmaller) {
    /* Set up the input values */
    const double x = -2.5;
    const double boxby2 = 1.0;

    /* Call the function to be tested */
    const double result = pbc(x, boxby2);

    /* Check that the function returns the expected output */
    EXPECT_DOUBLE_EQ(-0.5, result);
}