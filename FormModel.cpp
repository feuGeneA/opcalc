#include "FormModel.h"

#include <ostream>

#include <Wt/WApplication>
#include <Wt/WDoubleValidator>
#include <Wt/WStringListModel>

#include "opval.h"

const Wt::WFormModel::Field FormModel::SpotField="spot";
const Wt::WFormModel::Field FormModel::DividendField="dividend";
const Wt::WFormModel::Field FormModel::InterestField="interest";
const Wt::WFormModel::Field FormModel::VolatilityField="volatility";
//const Wt::WFormModel::Field FormModel::CallPutField="callput";
const Wt::WFormModel::Field FormModel::StrikeField="strike";
const Wt::WFormModel::Field FormModel::TermField="term";
const Wt::WFormModel::Field FormModel::ResultField="result";

FormModel::FormModel(
    Wt::WObject  * parent )
    : Wt::WFormModel(parent)
    //: //callputModel(new Wt::WStringListModel({"Call","Put"},this)),
      //log(logStream)
{
    Wt::WDoubleValidator *v = new Wt::WDoubleValidator();
    v->setBottom(0);
    v->setMandatory(true);

    for ( auto const& f :
        { SpotField, DividendField, InterestField, VolatilityField,
          StrikeField, TermField } )
    {
        addField(f);
        //setValidator(f, v);
        setValue(f, double());
    }

    addField(ResultField);
    setReadOnly(ResultField, true);
    setValue(ResultField, double());
}

Wt::WString FormModel::label(Field field) const
{
    static Wt::WString
        spotLabel("Spot:"),
        dividendLabel("Annual dividend rate:"),
        interestLabel("Annual risk-free interest rate:"),
        volatilityLabel("Volatility:"),
        //callputLabel("Type of option:"),
        strikeLabel("Strike:"),
        termLabel("Term:"),
        resultLabel("Result:"),
        unknown("FormModel::label doesn't know what to return");

    if ( field==      SpotField ) return       spotLabel;
    if ( field==  DividendField ) return   dividendLabel;
    if ( field==  InterestField ) return   interestLabel;
    if ( field==VolatilityField ) return volatilityLabel;
    //if ( field==   CallPutField ) return    callputLabel;
    if ( field==    StrikeField ) return     strikeLabel;
    if ( field==      TermField ) return       termLabel;
    if ( field==    ResultField ) return     resultLabel;
    return unknown;
}

void FormModel::calculate()
{
    opval::AmericanOptionSpec spec;
    spec.spot   = boost::any_cast<double>(value(  SpotField));
    spec.strike = boost::any_cast<double>(value(StrikeField));
    spec.type = QuantLib::Option::Call;
    spec.timeToMaturity = boost::any_cast<double>(value(TermField));
    spec.dividend = boost::any_cast<double>(value(DividendField));
    spec.riskFreeRate = boost::any_cast<double>(value(InterestField));
    spec.volatility = boost::any_cast<double>(value(VolatilityField));

    setValue(ResultField, double(opval::value(spec)));
}