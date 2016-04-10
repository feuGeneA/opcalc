#ifndef QUANTLIB_INCLUDED_H
#define QUANTLIB_INCLUDED_H

#include <ql/instruments/vanillaoption.hpp>
#include <ql/option.hpp>
#include <ql/types.hpp>

namespace opcalc {

// namespace to contain our abstractions to encapsulate the QuantLib
// symbols. lower case to differentiate.
namespace quantlib {

struct OptionInput {
    QuantLib::Option::Type type;
    QuantLib::Real         strike;
    QuantLib::Real         spot;
    QuantLib::Rate         dividend;       // annual. [0,1]
    QuantLib::Rate         riskFreeRate;   // annual. [0,1]
    QuantLib::Time         timeToMaturity; // fraction of year. [0,1]
    QuantLib::Volatility   volatility;     // annual. [0,1]
};

QuantLib::VanillaOption value(
    std::string const& engine,
    std::string const& process,
    OptionInput const& input);
    /*
     * engine must be one of "BaroneAdesiWhaley", "BjerksundStensland",
     * "FDAmericanCrankNicolson", "FDDividendAmericanCrankNicolson".
     *
     * process must be one of "BlackScholesMerton", "GarmanKohlagen",
     * "ExtendedBlackScholesMerton", or "VegaStressedBlackScholesProcess".
     *
     * For further descriptions, see QuantLib doxygen. */

}}

#endif
