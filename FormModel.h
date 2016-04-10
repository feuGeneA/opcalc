#ifndef FORMMODEL_INCLUDED_H
#define FORMMODEL_INCLUDED_H

#include <Wt/WFormModel>
#include <Wt/WString>
#include <Wt/WStringListModel>

namespace opcalc {

class StringSetModel;

class FormModel : public Wt::WFormModel
{
public:
    static const Field EngineField,
                      ProcessField,
                         SpotField,
                     DividendField,
                     InterestField,
                   VolatilityField,
                      CallPutField,
                       StrikeField,
                         TermField,
                       ResultField,
                        DeltaField,
                        GammaField,
                        ThetaField,
                         VegaField,
                          RhoField;

    FormModel(Wt::WObject * parent = 0);

    Wt::WString label(Field field) const;

    void calculate();

    StringSetModel *engineModel, *processModel, *callPutModel;
};

}

#endif
