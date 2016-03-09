#ifndef QUANTLIB_INCLUDED_H
#define QUANTLIB_INCLUDED_H

#include <ql/option.hpp>
#include <ql/types.hpp>

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
