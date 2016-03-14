#ifndef QUANTLIB_INCLUDED_H
#define QUANTLIB_INCLUDED_H

#include <ql/option.hpp>
#include <ql/types.hpp>

// namespace to contain our abstractions to encapsulate the QuantLib
// symbols. lower case to differentiate.
namespace quantlib {

struct AmericanOptionSpec {
    QuantLib::Option::Type type;
    QuantLib::Real         strike;
    QuantLib::Real         spot;
    QuantLib::Rate         dividend;
    QuantLib::Rate         riskFreeRate;
    QuantLib::Time         timeToMaturity;
    QuantLib::Volatility   volatility;
};

QuantLib::Real value(AmericanOptionSpec const& input);

}

#endif
