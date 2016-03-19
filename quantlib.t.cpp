#include <gtest/gtest.h>

#include "quantlib.h"

TEST(quantlib, valuesFromLiterature)
{
    quantlib::AmericanOptionSpec input;
    input.type = QuantLib::Option::Call;
    input.strike = 100;
    input.timeToMaturity = 0.10;
    input.spot = 90.00;
    input.dividend = 0.10;
    input.riskFreeRate = 0.10;
    input.volatility = 0.15;

    EXPECT_NEAR(0.0206,
                quantlib::value("BaroneAdesiWhaley",input),
                3.0e-3);
}

TEST(quantlib, valuesFromBloomberg)
{
    quantlib::AmericanOptionSpec input;
    input.type = QuantLib::Option::Put;
    input.strike = 100;
    input.timeToMaturity = 0.10;
    input.spot = 90.00;
    input.dividend = 0.10;
    input.riskFreeRate = 0.10;
    input.volatility = 0.15;

    EXPECT_NEAR(10.02,
                quantlib::value("BaroneAdesiWhaley",input),
                2.1e-2);
}
