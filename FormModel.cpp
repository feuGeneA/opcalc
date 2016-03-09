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

    for ( auto const& f :
        { SpotField, DividendField, InterestField, VolatilityField,
          StrikeField, TermField } )
    {
        addField(f);
        //setValidator(f, v);
        setValue(f, double());
    }

    addField(CallPutField);
    setValue(CallPutField, std::string("Call"));

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
