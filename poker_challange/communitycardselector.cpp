#include "communitycardselector.h"

namespace TexasHoldemView
{
CommunityCardSelector::CommunityCardSelector(QString labelMessage, const QStringList &valueList_, const QStringList &colorList_, QWidget *parent) :
    CardSelector(labelMessage,valueList_,colorList_,parent), _enableChack(new QCheckBox),
    _mainLayout(new QVBoxLayout), _communityCardLayout(new QHBoxLayout), _communityCardInfoLayout(new QHBoxLayout)
{
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

CommunityCardSelector::~CommunityCardSelector()
{
    _communityCardLayout->removeWidget(_boxes.first);
    _communityCardLayout->removeWidget(_boxes.second);
    _communityCardInfoLayout->removeWidget(_label);
    _communityCardInfoLayout->removeWidget(_enableChack);

    delete _communityCardLayout;
    delete _communityCardInfoLayout;
    delete _mainLayout;
    delete _enableChack;
}

void CommunityCardSelector::setEnable(int status)
{
    _boxes.first->setEnabled(status == Qt::Checked);
    _boxes.second->setEnabled(status == Qt::Checked);

}
}


