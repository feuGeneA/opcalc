#include "FormView.h"

#include <Wt/WApplication>
#include <Wt/WComboBox>
#include <Wt/WContainerWidget>
#include <Wt/WDoubleSpinBox>
#include <Wt/WPushButton>
#include <Wt/WString>
#include <Wt/WStringListModel>

#include "FormModel.h"
#include "StringSetModel.h"

namespace opcalc {

FormView::FormView( Wt::WContainerWidget * parent )
    : WTemplateFormView(parent),
               model(new FormModel(this)),
            spotEdit(new Wt::WDoubleSpinBox),
        dividendEdit(new Wt::WDoubleSpinBox),
        interestEdit(new Wt::WDoubleSpinBox),
      volatilityEdit(new Wt::WDoubleSpinBox),
          strikeEdit(new Wt::WDoubleSpinBox),
            termEdit(new Wt::WDoubleSpinBox),
          resultEdit(new Wt::WDoubleSpinBox),
         engineInput(new Wt::WComboBox),
        processInput(new Wt::WComboBox),
        callputInput(new Wt::WComboBox)
{
    setTemplateText(
        "<label for=\"${id:engine}\">${engine-label}</label>"
        "${engine} ${engine-info}<br/>"

        "<label for=\"${id:model}\">${model-label}</label>"
        "${model} ${model-info}<br/>"

        "<label for=\"${id:spot}\">${spot-label}</label>"
        "${spot} ${spot-info}<br/>"

        "<label for=\"${id:dividend}\">${dividend-label}</label>"
        "${dividend} ${dividend-info}<br/>"

        "<label for=\"${id:interest}\">${interest-label}</label>"
        "${interest} ${interest-info}<br/>"

        "<label for=\"${id:volatility}\">${volatility-label}</label>"
        "${volatility} ${volatility-info}<br/>"

        "<label for=\"${id:callput}\">${callput-label}</label>"
        "${callput} ${callput-info}<br/>"

        "<label for=\"${id:strike}\">${strike-label}</label>"
        "${strike} ${strike-info}<br/>"

        "<label for=\"${id:term}\">${term-label}</label>"
        "${term} ${term-info}<br/>"

        "${submit-button} ${submit-info}<br/>"

        "<label for=\"${id:result}\">${result-label}</label>"
        "${result}<br/>"

        "${<if:delta>}"
        "<label for=\"${id:delta}\">${delta-label}</label>"
        "${delta} ${delta-info}<br/>"
        "${</if:delta>}"

        "${<if:gamma>}"
        "<label for=\"${id:gamma}\">${gamma-label}</label>"
        "${gamma} ${gamma-info}<br/>"
        "${</if:gamma>}"

        "${<if:theta>}"
        "<label for=\"${id:theta}\">${theta-label}</label>"
        "${theta} ${theta-info}<br/>"
        "${</if:theta>}"

        "${<if:vega>}"
        "<label for=\"${id:vega}\">${vega-label}</label>"
        "${vega} ${vega-info}<br/>"
        "${</if:vega>}"

        "${<if:rho>}"
        "<label for=\"${id:rho}\">${rho-label}</label>"
        "${rho} ${rho-info}<br/>"
        "${</if:rho>}"
        );

    engineInput->setModel(model->engineModel);
    engineInput->setCurrentIndex(0);
    setFormWidget(FormModel::EngineField, engineInput,
        [=]() { // updateViewValue
            // model never changes independent of view. no-op.
        },
        [=]() { // updateModelValue
            model->setValue(
                FormModel::EngineField,
                static_cast<Wt::WString>(
                    model->engineModel->stringList()[
                        engineInput->currentIndex() ] ) );
        } );

    processInput->setModel(model->processModel);
    processInput->setCurrentIndex(0);
    setFormWidget(FormModel::ProcessField, processInput,
        [=]() { // updateViewValue
            // model never changes independent of view. no-op.
        },
        [=]() { // updateModelValue
            model->setValue(
                FormModel::ProcessField,
                static_cast<Wt::WString>(
                    model->processModel->stringList()[
                        processInput->currentIndex() ] ) );
        } );

    setDoubleWidget(FormModel::      SpotField,       spotEdit);
    setDoubleWidget(FormModel::  DividendField,   dividendEdit);
    setDoubleWidget(FormModel::  InterestField,   interestEdit);
    setDoubleWidget(FormModel::VolatilityField, volatilityEdit);
    setDoubleWidget(FormModel::    StrikeField,     strikeEdit);
    setDoubleWidget(FormModel::      TermField,       termEdit);

    setFormWidget(FormModel::ResultField, resultEdit);

    callputInput->setModel(model->callPutModel);
    callputInput->setCurrentIndex(0);
    setFormWidget(FormModel::CallPutField, callputInput,
        [=] () { // updateViewValue
            // model never changes independent of view. no-op.
        },
        [=] () { // updateModelValue
            model->setValue(
                FormModel::CallPutField,
                static_cast<std::string>(
                    model->callPutModel->stringList()[
                        callputInput->currentIndex() ].narrow() ) );
        } );

    Wt::WPushButton * submitButton
        = new Wt::WPushButton("Calculate");
    bindWidget("submit-button", submitButton);
    bindString("submit-info", Wt::WString());
    submitButton->clicked().connect(this, &FormView::calculate);

    updateView(model);
}

void FormView::setDoubleWidget(
    Wt::WFormModel::Field field,
    Wt::WDoubleSpinBox* widget)
{
    setFormWidget(
        field,
        widget,
        [=] {
            widget->setValue(
                boost::any_cast<double>(
                    model->value(field) ) );
        },
        [=] {
            model->setValue(field, widget->value());
        });
}

void FormView::calculate()
{
    updateModel(model);
    if ( model->validate() ) model->calculate();
    else
    {
        std::string validationMsg("Validation failed: ");
        for ( std::vector<Wt::WFormModel::Field>::const_iterator
            f  = model->fields().begin() ;
            f != model->fields().end  () ; ++f )
        {
            if ( model->validation(*f).state() != Wt::WValidator::Valid )
            {
                validationMsg
                    += std::string(*f)
                    +": "+model->validation(*f).message().narrow();
            }
        }
        bindString("submit-info",validationMsg);
    }

    if ( model->isVisible(FormModel::DeltaField)
        && !resolveWidget(FormModel::DeltaField) )
    {
        setFormWidget(FormModel::DeltaField, new Wt::WDoubleSpinBox);
    }

    if ( model->isVisible(FormModel::GammaField)
        && !resolveWidget(FormModel::GammaField) )
    {
        setFormWidget(FormModel::GammaField, new Wt::WDoubleSpinBox);
    }

    if ( model->isVisible(FormModel::ThetaField)
        && !resolveWidget(FormModel::ThetaField) )
    {
        setFormWidget(FormModel::ThetaField, new Wt::WDoubleSpinBox);
    }

    if ( model->isVisible(FormModel::VegaField)
        && !resolveWidget(FormModel::VegaField) )
    {
        setFormWidget(FormModel::VegaField, new Wt::WDoubleSpinBox);
    }

    if ( model->isVisible(FormModel::RhoField)
        && !resolveWidget(FormModel::RhoField) )
    {
        setFormWidget(FormModel::RhoField, new Wt::WDoubleSpinBox);
    }

    updateView(model);
}

}
