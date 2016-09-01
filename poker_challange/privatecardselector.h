#ifndef PRIVATECARDSELECTOR_H
#define PRIVATECARDSELECTOR_H

#include "cardselector.h"
#include <QHBoxLayout>

namespace TexasHoldemView
{
class PrivateCardSelector : public CardSelector
{
    Q_OBJECT
public:
    PrivateCardSelector(QString labelMessage,const QStringList& valueList_, const QStringList& colorList_,
                        QWidget *parent = 0);
    virtual ~PrivateCardSelector();

    virtual bool selectionIsActive() {return true;}

private:
    QHBoxLayout *_mainLayout;
};
}


#endif // PRIVATECARDSELECTOR_H
