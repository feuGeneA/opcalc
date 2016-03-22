#include "FormModel.h"

#include <ostream>

#include <Wt/WApplication>
#include <Wt/WDoubleValidator>
#include <Wt/WStringListModel>

#include "quantlib.h"

const Wt::WFormModel::Field FormModel::EngineField="engine";
const Wt::WFormModel::Field FormModel::ProcessField="model";
const Wt::WFormModel::Field FormModel::SpotField="spot";
const Wt::WFormModel::Field FormModel::DividendField="dividend";
const Wt::WFormModel::Field FormModel::InterestField="interest";
const Wt::WFormModel::Field FormModel::VolatilityField="volatility";
const Wt::WFormModel::Field FormModel::CallPutField="callput";
const Wt::WFormModel::Field FormModel::StrikeField="strike";
const Wt::WFormModel::Field FormModel::TermField="term";
const Wt::WFormModel::Field FormModel::ResultField="result";
const Wt::WFormModel::Field FormModel::DeltaField="delta";
const Wt::WFormModel::Field FormModel::GammaField="gamma";
const Wt::WFormModel::Field FormModel::ThetaField="theta";
const Wt::WFormModel::Field FormModel::VegaField="vega";
const Wt::WFormModel::Field FormModel::RhoField="rho";

FormModel::FormModel(
    Wt::WObject  * parent )
    : Wt::WFormModel(parent),
      engineModel(new StringSetModel()),
      processModel(new StringSetModel()),
      callPutModel(new StringSetModel())
{
    callPutModel->addString("Call");
    callPutModel->setData(0,0, QuantLib::Option::Call, Wt::ItemDataRole::UserRole);

    callPutModel->addString("Put");
    callPutModel->setData(1,0, QuantLib::Option::Put, Wt::ItemDataRole::UserRole);

    // from QuantLib doxygen:
    engineModel->addString("Barone-Adesi and Whaley pricing engine for"
        " American options (1987)");
    engineModel->setData(0,0, "BaroneAdesiWhaley", Wt::ItemDataRole::UserRole);

    // from QuantLib doxygen:
    engineModel->addString("Finite-differences pricing engine for American"
        " one asset options, using Crank-Nicolson scheme");
    engineModel->setData(1,0, "FDAmericanCrankNicolson",
        Wt::ItemDataRole::UserRole);

    // from QuantLib doxygen:
    engineModel->addString("Finite-differences pricing engine for dividend"
        " American options, using Crank-Nicolson scheme");
    engineModel->setData(2,0, "FDDividendAmericanCrankNicolson",
        Wt::ItemDataRole::UserRole);

    // from QuantLib doxygen:
    engineModel->addString("Bjerksund and Stensland pricing engine for"
        " American options (1993)");
    engineModel->setData(3,0, "BjerksundStensland",
        Wt::ItemDataRole::UserRole);

    addField(EngineField);
    setValue(EngineField, engineModel->stringList()[0]);

    // from QuantLib doxygen:
    processModel->addString("Merton (1973) extension to the Black-Scholes"
        " stochastic process");
    processModel->setData(0,0, "BlackScholesMerton",
        Wt::ItemDataRole::UserRole);

    // from QuantLib doxygen:
    processModel->addString("experimental Black-Scholes-Merton stochastic"
        " process");
    processModel->setData(1,0, "ExtendedBlackScholesMerton",
        Wt::ItemDataRole::UserRole);

    // from QuantLib doxygen:
    processModel->addString("Garman-Kohlhagen (1983) stochastic"
        " process");
    processModel->setData(2,0, "GarmanKohlagen",
        Wt::ItemDataRole::UserRole);

    // from QuantLib doxygen:
    processModel->addString("Black-Scholes process which supports"
        " local vega stress tests");
    processModel->setData(3,0, "VegaStressedBlackScholesProcess",
        Wt::ItemDataRole::UserRole);

    addField(ProcessField);
    setValue(ProcessField, processModel->stringList()[0]);

    Wt::WDoubleValidator *v = new Wt::WDoubleValidator();
    v->setBottom(0);
    v->setMandatory(true);

    addField(SpotField, "Current price of the underlying stock");
    setValue(SpotField, double(90));

    addField(DividendField, "Annual rate of dividend payout for the"
        " stock; for 1% enter 0.01");
    setValue(DividendField, double(0.1));

    addField(InterestField, "Annual rate of risk-free interest; for 1%"
        " enter 0.01");
    setValue(InterestField, double(0.1));

    addField(VolatilityField, "Volatility of the price of the underlying"
        " stock; for 1% enter 0.01");
    setValue(VolatilityField, double(0.15));

    addField(CallPutField);
    setValue(CallPutField, "Call");

    addField(StrikeField, "Exercise price of the option");
    setValue(StrikeField, double(100));

    addField(TermField, "Expiration term of the option, expressed as a"
        " fraction of a year; for 6 months, enter 0.5");
    setValue(TermField, double(0.1));

    addField(ResultField);
    setReadOnly(ResultField, true);
    setValue(ResultField, double());

    addField(DeltaField, "Expected % change in option price for each %"
        " change in stock price");
    setReadOnly(DeltaField, true);
    setVisible(DeltaField, false);

    addField(GammaField, "Derivative of Delta");
    setReadOnly(GammaField, true);
    setVisible(GammaField, false);

    addField(ThetaField, "Rate of time value decay");
    setReadOnly(ThetaField, true);
    setVisible(ThetaField, false);

    addField(VegaField, "Implied volatility? (What exactly IS vega?)");
    setReadOnly(VegaField, true);
    setVisible(VegaField, false);

    addField(RhoField, "Sensitivity to interest rates? (What exactly"
        " IS rho?)");
    setReadOnly(RhoField, true);
    setVisible(RhoField, false);
}

Wt::WString FormModel::label(Field field) const
{
    static Wt::WString
        engineLabel("Pricing engine:"),
        processLabel("Stochastic process:"),
        spotLabel("Spot:"),
        dividendLabel("Annual dividend rate:"),
        interestLabel("Annual risk-free interest rate:"),
        volatilityLabel("Volatility:"),
        callputLabel("Type of option:"),
        strikeLabel("Strike:"),
        termLabel("Term:"),
        resultLabel("Result:"),
        deltaLabel("Delta:"),
        gammaLabel("Gamma:"),
        thetaLabel("Theta:"),
        vegaLabel("Vega:"),
        rhoLabel("Rho:"),
        unknown("FormModel::label doesn't know what to return for "
                "field "+std::string(field));

    if ( field==    EngineField ) return     engineLabel;
    if ( field==   ProcessField ) return    processLabel;
    if ( field==      SpotField ) return       spotLabel;
    if ( field==  DividendField ) return   dividendLabel;
    if ( field==  InterestField ) return   interestLabel;
    if ( field==VolatilityField ) return volatilityLabel;
    if ( field==   CallPutField ) return    callputLabel;
    if ( field==    StrikeField ) return     strikeLabel;
    if ( field==      TermField ) return       termLabel;
    if ( field==    ResultField ) return     resultLabel;
    if ( field==     DeltaField ) return      deltaLabel;
    if ( field==     GammaField ) return      gammaLabel;
    if ( field==     ThetaField ) return      thetaLabel;
    if ( field==      VegaField ) return       vegaLabel;
    if ( field==       RhoField ) return        rhoLabel;
    return unknown;
}

void FormModel::calculate()
{
    quantlib::AmericanOptionInput input;
    input.spot   = boost::any_cast<double>(value(  SpotField));
    input.strike = boost::any_cast<double>(value(StrikeField));

    input.type = boost::any_cast<QuantLib::Option::Type>(
        callPutModel->data(
            callPutModel->index(
                boost::any_cast<std::string>(value(CallPutField))),
            Wt::ItemDataRole::UserRole) );

    input.timeToMaturity = boost::any_cast<double>(value(TermField));
    input.dividend = boost::any_cast<double>(value(DividendField));
    input.riskFreeRate = boost::any_cast<double>(value(InterestField));
    input.volatility = boost::any_cast<double>(value(VolatilityField));

    QuantLib::VanillaOption option =
        quantlib::value(
            boost::any_cast<const char*>(
                engineModel->data(
                    engineModel->index(
                        boost::any_cast<Wt::WString>(value(EngineField))
                        ),
                        Wt::ItemDataRole::UserRole
                    )
                ),
                boost::any_cast<const char*>(
                    processModel->data(
                        processModel->index(
                            boost::any_cast<Wt::WString>(value(ProcessField))
                    ),
                    Wt::ItemDataRole::UserRole
                )
            ),
            input
        );

    setValue(ResultField, double(option.NPV()));

    try {
        setValue(DeltaField, double(option.delta()));
        setVisible(DeltaField, true);
    } catch(...) {
        setVisible(DeltaField, false);
    }

    try {
        setValue(GammaField, double(option.gamma()));
        setVisible(GammaField, true);
    } catch(...) {
        setVisible(GammaField, false);
    }

    try {
        setValue(ThetaField, double(option.theta()));
        setVisible(ThetaField, true);
    } catch(...) {
        setVisible(ThetaField, false);
    }

    try {
        setValue(VegaField, double(option.vega()));
        setVisible(VegaField, true);
    } catch(...) {
        setVisible(VegaField, false);
    }

    try {
        setValue(RhoField, double(option.vega()));
        setVisible(RhoField, true);
    } catch(...) {
        setVisible(RhoField, false);
    }
}
