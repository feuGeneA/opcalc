#ifndef STRINGSETMODEL_INCLUDED_H
#define STRINGSETMODEL_INCLUDED_H

// TODO: try to fit this into Wt library code

#include <Wt/WModelIndex>
#include <Wt/WString>
#include <Wt/WStringListModel>

namespace opcalc {

class StringSetModel : public Wt::WStringListModel
{
public:
    Wt::WModelIndex index(Wt::WString target) const;
};

}

#endif
