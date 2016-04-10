#include "StringSetModel.h"

namespace opcalc {

Wt::WModelIndex StringSetModel::index(Wt::WString target) const
{
    std::vector<Wt::WString>::const_iterator
        pTarget = std::find(stringList().begin(),
                            stringList().end  (), target);

    if ( pTarget == stringList().end() )
        return Wt::WModelIndex(); // invalid index

    return createIndex(
        std::distance(stringList().begin(), pTarget),0,(void*)0);
}

}
