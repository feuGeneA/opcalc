#include <gtest/gtest.h>

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WObject>
#include <Wt/WStringListModel>

#include "FormModel.h"

// TODO: test labels

TEST(FormModel, instantiation)
{
    FormModel model(NULL);
}

TEST(FormModel, valuesFromLiterature)
{
    FormModel model(NULL);
    ASSERT_EQ(10, model.fields().size());
    ASSERT_EQ(2, model.callPutModel->stringList().size());

    double spot = 90,
           dividend = 0.1,
           interest = 0.1,
           volatility = 0.15,
           strike = 100,
           term = 0.1;

    model.setValue(FormModel::SpotField, double(spot));
    ASSERT_EQ(
        spot,
        boost::any_cast<double>(
            model.value(FormModel::SpotField) ) );

    model.setValue(FormModel::DividendField, dividend);
    ASSERT_EQ(
        dividend,
        boost::any_cast<double>(
            model.value(FormModel::DividendField) ) );

    model.setValue(FormModel::InterestField, interest);
    ASSERT_EQ(
        interest,
        boost::any_cast<double>(
            model.value(FormModel::InterestField) ) );

    model.setValue(FormModel::VolatilityField, volatility);
    ASSERT_EQ(
        volatility,
        boost::any_cast<double>(
            model.value(FormModel::VolatilityField) ) );

    model.setValue(FormModel::StrikeField, strike);
    ASSERT_EQ(
        strike,
        boost::any_cast<double>(
            model.value(FormModel::StrikeField) ) );

    model.setValue(FormModel::TermField, term);
    ASSERT_EQ(
        term,
        boost::any_cast<double>(
            model.value(FormModel::TermField) ) );

    model.setValue(FormModel::CallPutField, std::string("Call"));
    ASSERT_EQ(
        std::string("Call"),
        boost::any_cast<std::string>(
            model.value(FormModel::CallPutField) ) );

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
    FormModel model(NULL);

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
    model.setValue(FormModel::CallPutField, std::string("Put"));

    EXPECT_TRUE(model.validate());
    EXPECT_TRUE(model.valid());

    model.calculate();

    EXPECT_NEAR(
        10.02,
        boost::any_cast<double>(model.value(FormModel::ResultField)),
        2.1e-2);
}

