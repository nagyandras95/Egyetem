#ifndef MODELVIEWMATCHING_H
#define MODELVIEWMATCHING_H
#include <map>
#include <QString>
#include <algorithm>

/*
 * Base class for String-Value matching.
 */

template<typename ValueType, typename SpecalType>
class ModelViewMatching
{
public:
    ModelViewMatching() {init();}

    QString match(const ValueType& value)
    {
        return _matchingMap[value];
    }

    const ValueType& invertMatch(QString valueString)
    {
        return std::find_if(_matchingMap.begin(), _matchingMap.end(),
                            [valueString](std::pair<ValueType,QString> p){return p.second == valueString;})->first;
    }

    //template interface..
    void init()
    {
        static_cast<SpecalType*>(this)->implementInit();
    }

protected:
    std::map<ValueType, QString> _matchingMap;
};

#endif // MODELVIEWMATCHING_H
