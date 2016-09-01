#include "playerwidget.h"

namespace TexasHoldemView
{
PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent),
    _bet(new QSpinBox), _desecition(new QComboBox), _mainLayout(new QHBoxLayout)
{
    _mainLayout->addWidget(_desecition);
    _mainLayout->addWidget(_bet);

    setLayout(_mainLayout);
}
}


