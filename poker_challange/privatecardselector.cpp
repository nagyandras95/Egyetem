#include "privatecardselector.h"

namespace TexasHoldemView
{
PrivateCardSelector::PrivateCardSelector(QString labelMessage, const QStringList &valueList_, const QStringList &colorList_, QWidget *parent)
    : CardSelector(labelMessage,valueList_,colorList_,parent), _mainLayout(new QHBoxLayout)
{

    _mainLayout->addWidget(_label);
    _mainLayout->addWidget(_boxes.first);
    _mainLayout->addWidget(_boxes.second);
    setLayout(_mainLayout);

}

PrivateCardSelector::~PrivateCardSelector()
{
    _mainLayout->removeWidget(_label);
    _mainLayout->removeWidget(_boxes.first);
    _mainLayout->removeWidget(_boxes.second);
    delete _mainLayout;
}
}


