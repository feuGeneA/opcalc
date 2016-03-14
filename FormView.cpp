#include "FormView.h"

#include <iostream> // TODO: delete me

#include <Wt/WApplication>
#include <Wt/WComboBox>
#include <Wt/WContainerWidget>
#include <Wt/WDoubleSpinBox>
#include <Wt/WPushButton>
#include <Wt/WString>
#include <Wt/WStringListModel>

#include "FormModel.h"

FormView::FormView( Wt::WContainerWidget * parent )
    : WTemplateFormView(parent),
      model(new FormModel(this)),
       engineField(new Wt::WLineEdit),
      processField(new Wt::WLineEdit),
            spotEdit(new Wt::WDoubleSpinBox),
        dividendEdit(new Wt::WDoubleSpinBox),
        interestEdit(new Wt::WDoubleSpinBox),
      volatilityEdit(new Wt::WDoubleSpinBox),
          strikeEdit(new Wt::WDoubleSpinBox),
            termEdit(new Wt::WDoubleSpinBox),
          resultEdit(new Wt::WDoubleSpinBox),
        callputInput(new Wt::WComboBox)
{
    //model = new FormModel(/*app.log("info"),*/ this);

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
        "${result}" );

    setFormWidget(FormModel::EngineField, engineField);
    engineField->setTextSize(50);

    setFormWidget(FormModel::ProcessField, processField);
    processField->setTextSize(50);

    setDoubleWidget(FormModel::SpotField, spotEdit);
    setDoubleWidget(FormModel::DividendField, dividendEdit);
    setDoubleWidget(FormModel::InterestField, interestEdit);
    setDoubleWidget(FormModel::VolatilityField, volatilityEdit);
    setDoubleWidget(FormModel::StrikeField, strikeEdit);
    setDoubleWidget(FormModel::TermField, termEdit);

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
    // callbacks without c++11:
    //boost::bind(&FormView::updateViewValue_strike, this),
    //boost::bind(&FormView::updateModelValue_strike, this));
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
    updateView(model);
}
