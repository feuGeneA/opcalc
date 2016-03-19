#ifndef FORMMODEL_INCLUDED_H
#define FORMMODEL_INCLUDED_H

#include <Wt/WFormModel>
#include <Wt/WString>
#include <Wt/WStringListModel>

class FormModel : public Wt::WFormModel
{
public:
    static const Field
           EngineField,
          ProcessField,
             SpotField,
         DividendField,
         InterestField,
       VolatilityField,
          CallPutField,
           StrikeField,
             TermField,
           ResultField;

    FormModel(Wt::WObject  * parent = 0);

    Wt::WString label(Field field) const;

    void calculate();

private:
    class StringSetModel : public Wt::WStringListModel
    {
    public:
        Wt::WModelIndex index(Wt::WString target) const
        {
            std::vector<Wt::WString>::const_iterator
                pTarget = std::find(stringList().begin(),
                                    stringList().end  (), target);

            if ( pTarget == stringList().end() )
                return Wt::WModelIndex(); // invalid index

            return createIndex(
                std::distance(stringList().begin(), pTarget),0,(void*)0);
        }
    };

public:

    StringSetModel *engineModel, *callPutModel;
};

 #endif
