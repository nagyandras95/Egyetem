#include "amountsetter.h"

AmountSetter::AmountSetter(QString labelMessage, QWidget *parent) : QWidget(parent),
    _label(new QLabel(labelMessage)), _setterSpinBox(new QSpinBox), _setterLayout(new QHBoxLayout)
{
    _setterLayout->addWidget(_label);
    _setterLayout->addWidget(_setterSpinBox);

    setLayout(_setterLayout);
}
