#include "cardselector.h"

CardSelector::CardSelector(QString labelMessage, const QStringList &valueList_, const QStringList &colorList_,
                           QWidget *parent) : QWidget(parent), _label(new QLabel(labelMessage)), _boxes(new QComboBox,new QComboBox)
{
    _boxes.first->addItems(valueList_);
    _boxes.second->addItems(colorList_);

    connect(_boxes.first,SIGNAL(currentTextChanged(QString)),this,SLOT(cardParameterChanged(QString)));
    connect(_boxes.second,SIGNAL(currentTextChanged(QString)),this,SLOT(cardParameterChanged(QString)));
}

CardSelector::~CardSelector()
{
    delete _boxes.first;
    delete _boxes.second;
    delete _label;
}

void CardSelector::cardParameterChanged(QString)
{
    if(_boxes.first->isEnabled() && _boxes.second->isEnabled())
        emit cardChanged(_boxes.first->currentText(), _boxes.second->currentText());
}
