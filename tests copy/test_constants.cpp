#include <gtest/gtest.h>
#include "constants.h"

TEST(ConstantsTest, Boltzmann)
{
    double expected = 0.0019872067; /* boltzman constant in kcal/mol/K */
    ASSERT_DOUBLE_EQ(kboltz, expected);
}

TEST(ConstantsTest, MVSQ2E)
{
    double expected = 2390.05736153349; /* m*v^2 in kcal/mol */
    ASSERT_DOUBLE_EQ(mvsq2e, expected);
}
