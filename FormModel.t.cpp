#include <gtest/gtest.h>

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WObject>
#include <Wt/WStringListModel>

#include "FormModel.h"

// TODO: test labels

TEST(FormModel, instantiation)
{
    FormModel model(nullptr);
    ASSERT_EQ(10, model.fields().size());
    ASSERT_EQ(2, model.callPutModel->stringList().size());
}

TEST(FormModel, engineFieldSticks)
{
    FormModel model(NULL);
    model.setValue(
        FormModel::EngineField,
        model.engineModel->stringList()[0]);
    ASSERT_EQ(
        model.engineModel->stringList()[0],
        boost::any_cast<Wt::WString>(
            model.value(FormModel::EngineField) ) );
}

TEST(FormModel, spotFieldSticks)
{
    double value=100;
    FormModel model(nullptr);
    model.setValue(FormModel::SpotField, double(value));
    ASSERT_EQ(
        value,
        boost::any_cast<double>(
            model.value(FormModel::SpotField) ) );
}

TEST(FormModel, dividendFieldSticks)
{
    double value=0.3;
    FormModel model(nullptr);
    model.setValue(FormModel::DividendField, value);
    ASSERT_EQ(
        value,
        boost::any_cast<double>(
            model.value(FormModel::DividendField) ) );
}

TEST(FormModel, interestFieldSticks)
{
    double value=0.02;
    FormModel model(nullptr);
    model.setValue(FormModel::InterestField, value);
    ASSERT_EQ(
        value,
        boost::any_cast<double>(
            model.value(FormModel::InterestField) ) );
}

TEST(FormModel, volatilityFieldSticks)
{
    double value=0.3;
    FormModel model(nullptr);
    model.setValue(FormModel::VolatilityField, value);
    ASSERT_EQ(
        value,
        boost::any_cast<double>(
            model.value(FormModel::VolatilityField) ) );
}

TEST(FormModel, strikeFieldSticks)
{
    double value=125;
    FormModel model(nullptr);
    model.setValue(FormModel::StrikeField, value);
    ASSERT_EQ(
        value,
        boost::any_cast<double>(
            model.value(FormModel::StrikeField) ) );
}

TEST(FormModel, termFieldSticks)
{
    double value=0.5;
    FormModel model(nullptr);
    model.setValue(FormModel::TermField, value);
    ASSERT_EQ(
        value,
        boost::any_cast<double>(
            model.value(FormModel::TermField) ) );
}

TEST(FormModel, callPutFieldSticks)
{
    FormModel model(nullptr);

    model.setValue(FormModel::CallPutField, std::string("Call"));
    ASSERT_EQ(
        std::string("Call"),
        boost::any_cast<std::string>(
            model.value(FormModel::CallPutField) ) );

    model.setValue(FormModel::CallPutField, std::string("Put"));
    ASSERT_EQ(
        std::string("Put"),
        boost::any_cast<std::string>(
            model.value(FormModel::CallPutField) ) );
}

TEST(FormModel, valuesFromLiterature)
{
    FormModel model(nullptr);

    double spot = 90,
           dividend = 0.1,
           interest = 0.1,
           volatility = 0.15,
           strike = 100,
           term = 0.1;

    model.setValue(FormModel::SpotField, double(spot));
    model.setValue(FormModel::DividendField, dividend);
    model.setValue(FormModel::InterestField, interest);
    model.setValue(FormModel::VolatilityField, volatility);
    model.setValue(FormModel::StrikeField, strike);
    model.setValue(FormModel::TermField, term);
    model.setValue(FormModel::CallPutField, std::string("Call"));

    EXPECT_TRUE(model.validate());
    EXPECT_TRUE(model.valid());

    model.calculate();

    EXPECT_NEAR(
        0.0206,
        boost::any_cast<double>(model.value(FormModel::ResultField)),
        3.0e-3);
}

TEST(FormModel, valuesFromBloomberg)
{
    FormModel model(nullptr);

    double spot = 90,
           dividend = 0.1,
           interest = 0.1,
           volatility = 0.15,
           strike = 100,
           term = 0.1;

    model.setValue(
        FormModel::EngineField,
        Wt::WString("Finite-differences pricing engine for American one asset"
            " options, using Crank-Nicolson scheme"));
    model.setValue(FormModel::SpotField, double(spot));
    model.setValue(FormModel::DividendField, dividend);
    model.setValue(FormModel::InterestField, interest);
    model.setValue(FormModel::VolatilityField, volatility);
    model.setValue(FormModel::StrikeField, strike);
    model.setValue(FormModel::TermField, term);
    model.setValue(FormModel::CallPutField, std::string("Put"));

    EXPECT_TRUE(model.validate());
    EXPECT_TRUE(model.valid());

    model.calculate();

    EXPECT_NEAR(
        10.02,
        boost::any_cast<double>(model.value(FormModel::ResultField)),
        2.1e-2);
}

