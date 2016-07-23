#include "communitycardselector.h"

CommunityCardSelector::CommunityCardSelector(QString labelMessage, QObject *parent) :
    QObject(parent), _boxes(new QComboBox,new QComboBox), _label(new QLabel(labelMessage)), _enableChack(new QCheckBox)
{
    _boxes.first->setEnabled(false);
    _boxes.second->setEnabled(false);

    connect(_enableChack, SIGNAL(stateChanged(int)),,this,SLOT(setEnable(int)));

}

void CommunityCardSelector::setEnable(int status)
{
    _boxes.first->setEnabled(status == Qt::Checked);
    _boxes.second->setEnabled(status == Qt::Checked);

}
