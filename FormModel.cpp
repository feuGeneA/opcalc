#include "FormModel.h"

#include <ostream>

#include <Wt/WApplication>
#include <Wt/WDoubleValidator>
#include <Wt/WStringListModel>

#include "quantlib.h"

const Wt::WFormModel::Field FormModel::SpotField="spot";
const Wt::WFormModel::Field FormModel::DividendField="dividend";
const Wt::WFormModel::Field FormModel::InterestField="interest";
const Wt::WFormModel::Field FormModel::VolatilityField="volatility";
const Wt::WFormModel::Field FormModel::CallPutField="callput";
const Wt::WFormModel::Field FormModel::StrikeField="strike";
const Wt::WFormModel::Field FormModel::TermField="term";
const Wt::WFormModel::Field FormModel::ResultField="result";

FormModel::CallPutModel::CallPutModel()
{
    addString ("Call");
    //setData(0,0, "Call");
    setData(0,0, QuantLib::Option::Call, Wt::ItemDataRole::UserRole);

    addString ("Put");
    //setData(1,0, "Put");
    setData(1,0, QuantLib::Option::Put, Wt::ItemDataRole::UserRole);
}

FormModel::FormModel(
    Wt::WObject  * parent )
    : Wt::WFormModel(parent),
      callPutModel(new CallPutModel())
      //log(logStream)
{
    Wt::WDoubleValidator *v = new Wt::WDoubleValidator();
    v->setBottom(0);
    v->setMandatory(true);

    addField(SpotField, "Current price of the underlying stock");

    addField(DividendField, "Annual rate of dividend payout for the"
        " stock; for 1% enter 0.01");

    addField(InterestField, "Annual rate of risk-free interest; for 1%"
        " enter 0.01");

    addField(VolatilityField, "Volatility of the price of the underlying"
        " stock; for 1% enter 0.01");

    addField(CallPutField);

    addField(StrikeField, "Exercise price of the option");

    addField(TermField, "Expiration term of the option, expressed as a"
        " fraction of a year; for 6 months, enter 0.5");

    addField(ResultField);
    setReadOnly(ResultField, true);
    //setValue(ResultField, double());
}

Wt::WString FormModel::label(Field field) const
{
    static Wt::WString
        spotLabel("Spot:"),
        dividendLabel("Annual dividend rate:"),
        interestLabel("Annual risk-free interest rate:"),
        volatilityLabel("Volatility:"),
        callputLabel("Type of option:"),
        strikeLabel("Strike:"),
        termLabel("Term:"),
        resultLabel("Result:"),
        unknown("FormModel::label doesn't know what to return for "
                "field "+std::string(field));

    if ( field==      SpotField ) return       spotLabel;
    if ( field==  DividendField ) return   dividendLabel;
    if ( field==  InterestField ) return   interestLabel;
    if ( field==VolatilityField ) return volatilityLabel;
    if ( field==   CallPutField ) return    callputLabel;
    if ( field==    StrikeField ) return     strikeLabel;
    if ( field==      TermField ) return       termLabel;
    if ( field==    ResultField ) return     resultLabel;
    return unknown;
}

void FormModel::calculate()
{
    quantlib::AmericanOptionSpec spec;
    spec.spot   = boost::any_cast<double>(value(  SpotField));
    spec.strike = boost::any_cast<double>(value(StrikeField));

    spec.type = boost::any_cast<QuantLib::Option::Type>(
        callPutModel->data(
            callPutModel->index(
                boost::any_cast<std::string>(value(CallPutField))),
            Wt::ItemDataRole::UserRole) );

    spec.timeToMaturity = boost::any_cast<double>(value(TermField));
    spec.dividend = boost::any_cast<double>(value(DividendField));
    spec.riskFreeRate = boost::any_cast<double>(value(InterestField));
    spec.volatility = boost::any_cast<double>(value(VolatilityField));

    setValue(ResultField, double(quantlib::value(spec)));
}
