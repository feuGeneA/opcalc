#include <gtest/gtest.h>

#include "quantlib.h"

namespace { using namespace opcalc; }

TEST(quantlib, supportModelsAndProcesses)
{
    for ( auto engine : { "BaroneAdesiWhaley", "FDAmericanCrankNicolson",
                    "FDDividendAmericanCrankNicolson", "BjerksundStensland" } )
    {
        for ( auto process : { "BlackScholesMerton", "GarmanKohlagen",
            "ExtendedBlackScholesMerton", "VegaStressedBlackScholesProcess" } )
        {
            ASSERT_NO_THROW(
                quantlib::value(engine, process,
                    quantlib::OptionInput() ) );

            ASSERT_THROW(
                quantlib::value("BogusEngine", process,
                    quantlib::OptionInput() ),
                std::runtime_error);
        }

        ASSERT_THROW(
            quantlib::value(engine, "BogusProcess",
                quantlib::OptionInput() ),
            std::runtime_error);
    }
}

TEST(quantlib, valuesFromLiterature)
{
    /* case taken from QuantLib test suite, which itself cites "the literature"
     * as the source of these values */
    quantlib::OptionInput input;
    input.type = QuantLib::Option::Call;
    input.strike = 100;
    input.timeToMaturity = 0.10;
    input.spot = 90.00;
    input.dividend = 0.10;
    input.riskFreeRate = 0.10;
    input.volatility = 0.15;

    EXPECT_NEAR(0.0206,
                quantlib::value(
                    "BaroneAdesiWhaley",
                    "BlackScholesMerton",
                    input).NPV(),
                3.0e-3);
}

TEST(quantlib, valuesFromBloomberg)
{
    // case values taken from OVME on the Bloomberg Terminal

    quantlib::OptionInput input;
    input.type = QuantLib::Option::Put;
    input.strike = 100;
    input.timeToMaturity = 0.10;
    input.spot = 90.00;
    input.dividend = 0.10;
    input.riskFreeRate = 0.10;
    input.volatility = 0.15;

    QuantLib::VanillaOption result
        = quantlib::value(
            "FDDividendAmericanCrankNicolson",
            "BlackScholesMerton",
            input);

    EXPECT_NEAR(10.04,   result.NPV(),   0.04);
    EXPECT_NEAR(-0.9943, result.delta(), 0.0025);
    EXPECT_NEAR(0.00691, result.gamma(), 0.0037); // quite far off!
}
