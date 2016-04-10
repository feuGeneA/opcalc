#include "FormView.h"

#include <gtest/gtest.h>

#include <Wt/Test/WTestEnvironment>
#include <Wt/WApplication>
#include <Wt/WComboBox>
#include <Wt/WContainerWidget>
#include <Wt/WDoubleSpinBox>

class FormViewFixture : public ::testing::Test
{
public:
    Wt::Test::WTestEnvironment env;
    Wt::WApplication app;
    FormViewFixture() :app(env) {}
};

namespace {
    using opcalc::FormView;
    using opcalc::FormModel;
}

TEST_F(FormViewFixture, instantiation)
{
    FormView formView(nullptr);
}

TEST_F(FormViewFixture, spotFieldSticks)
{
    double spot = 100;
    FormView formView(nullptr);
    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::SpotField)
        )->setValue(spot);
    EXPECT_EQ(spot,
              dynamic_cast<Wt::WDoubleSpinBox*>(
                  formView.resolveWidget(FormModel::SpotField)
                  )->value() );
}

TEST_F(FormViewFixture, dividendFieldSticks)
{
    double dividend = 0.25;
    FormView formView(nullptr);
    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::DividendField)
        )->setValue(dividend);
    EXPECT_EQ(dividend,
              dynamic_cast<Wt::WDoubleSpinBox*>(
                  formView.resolveWidget(FormModel::DividendField)
                  )->value() );
}

TEST_F(FormViewFixture, interestField)
{
    double interest = 0.02;
    FormView formView(nullptr);
    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::InterestField)
        )->setValue(interest);
    EXPECT_EQ(interest,
              dynamic_cast<Wt::WDoubleSpinBox*>(
                  formView.resolveWidget(FormModel::InterestField)
                  )->value() );
}

TEST_F(FormViewFixture, volatilityFieldSticks)
{
    double volatility = 0.30;
    FormView formView(nullptr);
    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::VolatilityField)
        )->setValue(volatility);
    EXPECT_EQ(volatility,
              dynamic_cast<Wt::WDoubleSpinBox*>(
                  formView.resolveWidget(FormModel::VolatilityField)
                  )->value() );
}

TEST_F(FormViewFixture, strikeFieldSticks)
{
    double strike = 85;
    FormView formView(nullptr);
    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::StrikeField)
        )->setValue(strike);
    EXPECT_EQ(strike,
              dynamic_cast<Wt::WDoubleSpinBox*>(
                  formView.resolveWidget(FormModel::StrikeField)
                  )->value() );
}

TEST_F(FormViewFixture, termFieldSticks)
{
    double term = 0.25;
    FormView formView(nullptr);
    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::TermField)
        )->setValue(term);
    EXPECT_EQ(term,
              dynamic_cast<Wt::WDoubleSpinBox*>(
                  formView.resolveWidget(FormModel::TermField)
                  )->value() );
}

TEST_F(FormViewFixture, callPutFieldSticks)
{
    FormView formView(nullptr);

    dynamic_cast<Wt::WComboBox*>(
        formView.resolveWidget(FormModel::CallPutField)
        )->setValueText(std::string("Put"));
    EXPECT_EQ(
        std::string("Put"),
        dynamic_cast<Wt::WComboBox*>(
            formView.resolveWidget(FormModel::CallPutField)
            )->valueText() );

    dynamic_cast<Wt::WComboBox*>(
        formView.resolveWidget(FormModel::CallPutField)
        )->setValueText(std::string("Call"));
    EXPECT_EQ(
        std::string("Call"),
        dynamic_cast<Wt::WComboBox*>(
            formView.resolveWidget(FormModel::CallPutField)
            )->valueText() );
}

TEST_F(FormViewFixture, engineFieldSticks)
{
    FormView formView(nullptr);

    dynamic_cast<Wt::WComboBox*>(
        formView.resolveWidget(FormModel::EngineField)
        )->setValueText(std::string(
        "Barone-Adesi and Whaley pricing engine"
            " for American options (1987)") );
    EXPECT_EQ(
        std::string(
            "Barone-Adesi and Whaley pricing engine"
                " for American options (1987)"),
        dynamic_cast<Wt::WComboBox*>(
            formView.resolveWidget(FormModel::EngineField)
            )->valueText() );
}

TEST_F(FormViewFixture, valuesFromLiterature)
{
    FormView formView(nullptr);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::SpotField)
        )->setValue(90);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::DividendField)
        )->setValue(0.1);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::InterestField)
        )->setValue(0.1);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::VolatilityField)
        )->setValue(0.15);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::StrikeField)
        )->setValue(100);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::TermField)
        )->setValue(0.1);

    dynamic_cast<Wt::WComboBox*>(
        formView.resolveWidget(FormModel::CallPutField)
        )->setValueText(std::string("Call"));

    dynamic_cast<Wt::WComboBox*>(
        formView.resolveWidget(FormModel::EngineField)
        )->setValueText(std::string(
        "Barone-Adesi and Whaley pricing engine"
            " for American options (1987)") );

    formView.calculate();

    EXPECT_NEAR(
        0.0206,
        dynamic_cast<Wt::WDoubleSpinBox*>(
            formView.resolveWidget(FormModel::ResultField)
            )->value(),
        3.0e-3);
}

TEST_F(FormViewFixture, valuesFromBloomberg)
{
    FormView formView(nullptr);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::SpotField)
        )->setValue(90);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::DividendField)
        )->setValue(0.1);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::InterestField)
        )->setValue(0.1);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::VolatilityField)
        )->setValue(0.15);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::StrikeField)
        )->setValue(100);

    dynamic_cast<Wt::WDoubleSpinBox*>(
        formView.resolveWidget(FormModel::TermField)
        )->setValue(0.1);

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
