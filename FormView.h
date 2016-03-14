#ifndef FORMVIEW_INCLUDED_H
#define FORMVIEW_INCLUDED_H

#include <Wt/WTemplateFormView>
#include "FormModel.h"

namespace Wt { class WComboBox;
               class WContainerWidget;
               class WDoubleSpinBox; }

class FormView : public Wt::WTemplateFormView
{
public:
    FormView(Wt::WContainerWidget  * parent = 0);
    void calculate();
private:
    FormModel * model;

    Wt::WLineEdit *engineField, *processField;

    Wt::WDoubleSpinBox *spotEdit, *dividendEdit, *interestEdit,
        *volatilityEdit, *strikeEdit, *termEdit, *resultEdit;

    Wt::WComboBox *callputInput;

    void setDoubleWidget(Wt::WFormModel::Field, Wt::WDoubleSpinBox*);
};

#endif
