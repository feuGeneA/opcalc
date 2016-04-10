#include "FormModel.h"
#include <gtest/gtest.h>

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WObject>
#include <Wt/WStringListModel>

#include "StringSetModel.h"

namespace { using opcalc::FormModel; }

TEST(FormModel, instantiation)
{
    FormModel model(nullptr);
    ASSERT_EQ(15, model.fields().size());
    ASSERT_EQ(2, model.callPutModel->stringList().size());
    ASSERT_EQ(4, model. engineModel->stringList().size());
    ASSERT_EQ(4, model.processModel->stringList().size());
    ASSERT_FALSE(model.isVisible(FormModel::DeltaField));
    ASSERT_FALSE(model.isVisible(FormModel::GammaField));
    ASSERT_FALSE(model.isVisible(FormModel::ThetaField));
    ASSERT_FALSE(model.isVisible(FormModel::VegaField));
    ASSERT_FALSE(model.isVisible(FormModel::RhoField));
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
    /* test case taken from QuantLib test suite, which itself cites "the
     * literature" as the source of these values */

    FormModel model(nullptr);

    model.setValue(FormModel::SpotField, 90.0);
    model.setValue(FormModel::DividendField, 0.1);
    model.setValue(FormModel::InterestField, 0.1);
    model.setValue(FormModel::VolatilityField, 0.15);
    model.setValue(FormModel::StrikeField, 100.0);
    model.setValue(FormModel::TermField, 0.1);
    model.setValue(FormModel::CallPutField, std::string("Call"));

    model.calculate();

    EXPECT_NEAR(
        0.0206,
        boost::any_cast<double>(model.value(FormModel::ResultField)),
        3.0e-3);
}

TEST(FormModel, valuesFromBloomberg)
{
    // test case values taken from OVME on the Bloomberg Terminal

    FormModel model(nullptr);

    model.setValue(FormModel::SpotField, 90.0);
    model.setValue(FormModel::DividendField, 0.1);
    model.setValue(FormModel::InterestField, 0.1);
    model.setValue(FormModel::VolatilityField, 0.15);
    model.setValue(FormModel::StrikeField, 100.0);
    model.setValue(FormModel::TermField, 0.1);
    model.setValue(FormModel::CallPutField, std::string("Put"));

    // select an engine that supports delta & gamma
    model.setValue(
        FormModel::EngineField,
        Wt::WString("Finite-differences pricing engine for American one"
            " asset options, using Crank-Nicolson scheme"));

    model.calculate();

    EXPECT_NEAR(
        10.04,
        boost::any_cast<double>(model.value(FormModel::ResultField)),
        0.04);

    ASSERT_TRUE(model.isVisible(FormModel::DeltaField));
    EXPECT_NEAR(
        -0.9943,
        boost::any_cast<double>(model.value(FormModel::DeltaField)),
        0.0026);

    ASSERT_TRUE(model.isVisible(FormModel::GammaField));
    EXPECT_NEAR(
        0.00691,
        boost::any_cast<double>(model.value(FormModel::GammaField)),
        0.0037); // quite far off!
}

TEST(FormModel, atTheMoneyCallDelta)
{
    // a simple sanity check
    FormModel model(NULL);
    model.setValue(
        FormModel::EngineField,
        Wt::WString("Finite-differences pricing engine for American one"
            " asset options, using Crank-Nicolson scheme"));
    model.setValue(FormModel::SpotField,   90.0);
    model.setValue(FormModel::StrikeField, 90.0);
    model.setValue(FormModel::CallPutField, std::string("Call"));
    model.calculate();

    EXPECT_NEAR(
        0.5,
        boost::any_cast<double>(model.value(FormModel::DeltaField)),
        0.01);
}
