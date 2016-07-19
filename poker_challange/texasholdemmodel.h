#ifndef TEXASHOLDEMMODEL_H
#define TEXASHOLDEMMODEL_H

#include <QObject>
#include "hand_evaluator.h"

class TexasHoldemModel : public QObject
{
    Q_OBJECT
public:
    explicit TexasHoldemModel(QObject *parent = 0);

signals:

public slots:

private:
    hand_evaluator evalator;

};

#endif // TEXASHOLDEMMODEL_H
