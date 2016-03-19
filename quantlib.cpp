#include "quantlib.h"

#include <boost/shared_ptr.hpp>

#include <gtest/gtest.h>

#include <ql/exercise.hpp>
#include <ql/instruments/vanillaoption.hpp>
#include <ql/option.hpp>
#include <ql/pricingengines/vanilla/baroneadesiwhaleyengine.hpp>
#include <ql/pricingengines/vanilla/fdamericanengine.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <ql/termstructures/volatility/equityfx/blackconstantvol.hpp>
#include <ql/time/daycounters/actual360.hpp>
#include <ql/time/calendars/nullcalendar.hpp>

using namespace QuantLib;

namespace quantlib {

QuantLib::Real value(std::string        const& engine,
                     AmericanOptionSpec const& input)
{
    Date today = Date::todaysDate();
    DayCounter dc = Actual360();

    boost::shared_ptr<SimpleQuote> spot(new SimpleQuote(input.spot));

    boost::shared_ptr<YieldTermStructure>
        dividendTermStruct(
            new FlatForward(
                today,
                Handle<Quote>(
                    boost::shared_ptr<SimpleQuote>(
                        new SimpleQuote(input.dividend) ) ),
                dc) );

    boost::shared_ptr<YieldTermStructure>
        riskFreeRateTermStruct(
            new FlatForward(
                today,
                Handle<Quote>(
                    boost::shared_ptr<SimpleQuote>(
                        new SimpleQuote(input.riskFreeRate) ) ),
                dc) );

    boost::shared_ptr<BlackVolTermStructure>
        volTS(
            new BlackConstantVol(
                today,
                NullCalendar(),
                Handle<Quote>(
                    boost::shared_ptr<SimpleQuote>(
                        new SimpleQuote(input.volatility) ) ),
                dc) );

    boost::shared_ptr<StrikedTypePayoff> payoff(
        new PlainVanillaPayoff(input.type, input.strike));
    // FLOATING_POINT_EXCEPTION

    boost::shared_ptr<Exercise>
        exercise(
            new AmericanExercise(
                today, today + Integer(input.timeToMaturity*360+0.5) ) );

    boost::shared_ptr<BlackScholesMertonProcess> stochProcess(new
        BlackScholesMertonProcess(
            Handle<Quote>(spot),
            Handle<YieldTermStructure>(dividendTermStruct),
            Handle<YieldTermStructure>(riskFreeRateTermStruct),
            Handle<BlackVolTermStructure>(volTS)));

    boost::shared_ptr<PricingEngine> pEngine;

    if ( engine == "BaroneAdesiWhaley" )
        pEngine =
            boost::shared_ptr<PricingEngine>(
                new BaroneAdesiWhaleyApproximationEngine(stochProcess));
    else if ( engine == "FDAmericanCrankNicolson" )
        pEngine =
            boost::shared_ptr<PricingEngine>(
                new FDAmericanEngine<CrankNicolson>(stochProcess));
    else
        throw std::runtime_error("Unknown engine type '"+engine+"'");

    VanillaOption option(payoff, exercise);
    option.setPricingEngine(pEngine);

    return option.NPV();
}

}
