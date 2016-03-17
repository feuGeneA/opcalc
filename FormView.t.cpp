#include <iostream> // TODO: delete me

#include <gtest/gtest.h>

#include <Wt/Test/WTestEnvironment>
#include <Wt/WApplication>
#include <Wt/WComboBox>
#include <Wt/WContainerWidget>
#include <Wt/WDoubleSpinBox>

#include "FormView.h"

TEST(FormView, valuesFromLiterature)
{
    double spot = 90,
           dividend = 0.1,
           interest = 0.1,
           volatility = 0.15,
           strike = 100,
           term = 0.1;
    
    Wt::Test::WTestEnvironment env;
    Wt::WApplication app(env);

    FormView formView(nullptr);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::SpotField)
        )->setValue(spot);
    EXPECT_EQ(spot,
              dynamic_cast<Wt::WDoubleSpinBox*>(
                  formView.resolveWidget(FormModel::SpotField)
                  )->value() );

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::DividendField)
        )->setValue(dividend);
    EXPECT_EQ(dividend,
              dynamic_cast<Wt::WDoubleSpinBox*>(
                  formView.resolveWidget(FormModel::DividendField)
                  )->value() );

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::InterestField)
        )->setValue(interest);
    EXPECT_EQ(interest,
              dynamic_cast<Wt::WDoubleSpinBox*>(
                  formView.resolveWidget(FormModel::InterestField)
                  )->value() );

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::VolatilityField)
        )->setValue(volatility);
    EXPECT_EQ(volatility,
              dynamic_cast<Wt::WDoubleSpinBox*>(
                  formView.resolveWidget(FormModel::VolatilityField)
                  )->value() );

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::StrikeField)
        )->setValue(strike);
    EXPECT_EQ(strike,
              dynamic_cast<Wt::WDoubleSpinBox*>(
                  formView.resolveWidget(FormModel::StrikeField)
                  )->value() );

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::TermField)
        )->setValue(term);
    EXPECT_EQ(term,
              dynamic_cast<Wt::WDoubleSpinBox*>(
                  formView.resolveWidget(FormModel::TermField)
                  )->value() );

    dynamic_cast<Wt::WComboBox*>(
        formView.resolveWidget(FormModel::CallPutField)
        )->setValueText(std::string("Call"));
    EXPECT_EQ(
        std::string("Call"),
        dynamic_cast<Wt::WComboBox*>(
            formView.resolveWidget(FormModel::CallPutField)
            )->valueText() );

    formView.calculate();

    EXPECT_NEAR(
        0.0206,
        dynamic_cast<Wt::WDoubleSpinBox*>(
            formView.resolveWidget(FormModel::ResultField)
            )->value(),
        3.0e-3);
}

TEST(FormView, valuesFromBloomberg)
{
    double spot = 90,
           dividend = 0.1,
           interest = 0.1,
           volatility = 0.15,
           strike = 100,
           term = 0.1;
    
    Wt::Test::WTestEnvironment env;
    Wt::WApplication app(env);

    FormView formView(nullptr);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::SpotField)
        )->setValue(spot);
    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::DividendField)
        )->setValue(dividend);
    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::InterestField)
        )->setValue(interest);
    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::VolatilityField)
        )->setValue(volatility);
    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::StrikeField)
        )->setValue(strike);
    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::TermField)
        )->setValue(term);
    dynamic_cast<Wt::WComboBox*>(
        formView.resolveWidget(FormModel::CallPutField)
        )->setValueText(std::string("Put"));

    formView.calculate();

    EXPECT_NEAR(
        10.02,
        dynamic_cast<Wt::WDoubleSpinBox*>(
            formView.resolveWidget(FormModel::ResultField)
            )->value(),
        2.1e-2);
}
