#ifndef COMMUNITYCARDSELECTOR_H
#define COMMUNITYCARDSELECTOR_H

#include <QObject>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>

#include "cardselector.h"

class CommunityCardSelector : public CardSelector
{
    Q_OBJECT
public:
    explicit CommunityCardSelector(QString labelMessage,const QStringList& valueList_, const QStringList& colorList_,
                                   QWidget *parent = 0);
    virtual ~CommunityCardSelector();

    virtual bool selectionIsActive() {return _enableChack->isChecked();}

signals:

public slots:
private slots:
    void setEnable(int);
private:
    QCheckBox* _enableChack;

    QVBoxLayout *_mainLayout;
    QHBoxLayout *_communityCardLayout;
    QHBoxLayout *_communityCardInfoLayout;
};

#endif // COMMUNITYCARDSELECTOR_H
