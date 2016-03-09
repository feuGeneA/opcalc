#include <gtest/gtest.h>

#include "opval.h"

TEST(opval, valuesFromLiterature)
{
    opval::AmericanOptionSpec input;
    input.type = QuantLib::Option::Call;
    input.strike = 100;
    input.timeToMaturity = 0.10;
    input.spot = 90.00;
    input.dividend = 0.10;
    input.riskFreeRate = 0.10;
    input.volatility = 0.15;

    EXPECT_NEAR(0.0206, opval::value(input), 3.0e-3);
}

TEST(opval, valuesFromBloomberg)
{
    opval::AmericanOptionSpec input;
    input.type = QuantLib::Option::Put;
    input.strike = 100;
    input.timeToMaturity = 0.10;
    input.spot = 90.00;
    input.dividend = 0.10;
    input.riskFreeRate = 0.10;
    input.volatility = 0.15;

    EXPECT_NEAR(10.02, opval::value(input), 2.1e-2);
}
