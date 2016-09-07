#include "cardselector.h"

namespace TexasHoldemView
{
CardSelector::CardSelector(QString labelMessage, const QStringList &valueList_, const QStringList &colorList_,
                           QWidget *parent) : QWidget(parent), _label(new QLabel(labelMessage)), _boxes(new QComboBox,new QComboBox)
{
    _boxes.first->addItems(valueList_);
    _boxes.second->addItems(colorList_);
}

CardSelector::~CardSelector()
{
    delete _boxes.first;
    delete _boxes.second;
    delete _label;
}

}


