#include "texasholdemmodel.h"
#include "card.h"
#include "qdebug.h"
#include "hand_evaluator.h"

TexasHoldemModel::TexasHoldemModel(QObject *parent) : QObject(parent)
{
    evalator = new hand_evaluator();
}


TexasHoldemModel::~TexasHoldemModel()
{
    delete evalator;
}
