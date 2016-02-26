#ifndef FORMMODEL_INCLUDED_H
#define FORMMODEL_INCLUDED_H

#include <Wt/WFormModel>
#include <Wt/WString>

namespace Wt { class WStringListModel; }

class FormModel : public Wt::WFormModel
{
public:
    static const Field
             SpotField,
         DividendField,
         InterestField,
       VolatilityField,
          //CallPutField,
           StrikeField,
             TermField,
           ResultField;

    FormModel(Wt::WObject  * parent = 0);

    Wt::WString label(Field field) const;

    void calculate();

    //Wt::WStringListModel * callputModel;
};

#endif
