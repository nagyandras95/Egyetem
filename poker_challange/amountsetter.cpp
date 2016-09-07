#include "amountsetter.h"

namespace TexasHoldemView
{
AmountSetter::AmountSetter(QString labelMessage, int min, int max, QWidget *parent) : QWidget(parent),
    _label(new QLabel(labelMessage)), _setterSpinBox(new QSpinBox), _setterLayout(new QHBoxLayout)
{
    _setterLayout->addWidget(_label);
    _setterLayout->addWidget(_setterSpinBox);

    _setterSpinBox->setMinimum(min);
    _setterSpinBox->setMaximum(max);

    connect(_setterSpinBox,SIGNAL(valueChanged(int)),this, SLOT(valueChanged(int)));

    setLayout(_setterLayout);
}

AmountSetter::~AmountSetter()
{
    _setterLayout->removeWidget(_label);
    _setterLayout->removeWidget(_setterSpinBox);
    delete _label;
    delete _setterSpinBox;
    delete _setterLayout;
}

void AmountSetter::valueChanged(int value)
{
    emit amountChanged(value);
}
}


