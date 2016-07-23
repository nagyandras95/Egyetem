#include "communitycardselector.h"

CommunityCardSelector::CommunityCardSelector(QString labelMessage, const QStringList &valueList_, const QStringList &colorList_, QWidget *parent) :
    QWidget(parent), _boxes(new QComboBox,new QComboBox), _label(new QLabel(labelMessage)), _enableChack(new QCheckBox),
    _mainLayout(new QVBoxLayout), _communityCardLayout(new QHBoxLayout), _communityCardInfoLayout(new QHBoxLayout)
{
    _boxes.first->addItems(valueList_);
    _boxes.second->addItems(colorList_);
    _boxes.first->setEnabled(false);
    _boxes.second->setEnabled(false);


    _communityCardLayout->addWidget(_boxes.first);
    _communityCardLayout->addWidget(_boxes.second);

    _communityCardInfoLayout->addWidget(_label);
    _communityCardInfoLayout->addWidget(_enableChack);

    _mainLayout->addLayout(_communityCardInfoLayout);
    _mainLayout->addLayout(_communityCardLayout);


    setLayout(_mainLayout);

    connect(_enableChack, SIGNAL(stateChanged(int)),this,SLOT(setEnable(int)));

}

void CommunityCardSelector::setEnable(int status)
{
    _boxes.first->setEnabled(status == Qt::Checked);
    _boxes.second->setEnabled(status == Qt::Checked);

}
