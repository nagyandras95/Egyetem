#ifndef GEMEWIDGET_H
#define GEMEWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStringList>
#include <QString>
#include <QCheckBox>
#include <QSpinBox>

#include <map>
#include <vector>

#include "model/card.h"
#include "model/itexasholdemmodel.h"
#include "cardselector.h"
#include "amountsetter.h"
#include "threadnumbersetdialog.h"
#include "playerscontrolwidget.h"
#include "modelviewmatching.h"
#include "cardcolormatcher.h"
#include "cardvaluematcher.h"
#include "decesionmatcher.h"

namespace TexasHoldemView {
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(Model::ITexasHoldemModel* model,QWidget *parent = 0);
    ~GameWidget();

    int getnOfPlayers() const {return _nOfPlayersSetter->getAmount();}
    int getYourNumber() const {return _yourNumberSetter->getAmount();}
    int getSmallBlindBet() const {return _smallBlindSetter->getAmount();}
    int getBigBlindBet() const {return _bigBlindSetter->getAmount();}
    std::pair<Model::Card,Model::Card> getYourHand() const;

signals:
    void hintAdded(QString hint);
public slots:
    void newGameStarted(std::vector<Player> state);
    void stepGame();
    void changeActivePlayer(int playerNumber);
    void switchCoiceOption(bool beforeBet);
    void enableCommunityCardSelection(int,int);
    void disableAllCommunityCardSelection();
    void addActiveCommunityCards();

    void changeNofPlayers(int n);
    void changePot(int n);
    void changeYourBet(int n);

    void initSelections();

private:
    void initValueAndColorList();
    void initChoiceLists();

    Model::Card resolveCard(std::pair<QComboBox*,QComboBox*>) const;

    Model::ITexasHoldemModel* _model;

    CardSelector* _firstCard;
    CardSelector* _secondCard;
    std::vector<CardSelector*> _communityCards;

    AmountSetter* _potSetter;
    AmountSetter* _yourBetSetter;
    AmountSetter* _nOfPlayersSetter;
    AmountSetter* _yourNumberSetter;

    AmountSetter* _smallBlindSetter;
    AmountSetter* _bigBlindSetter;

    PlayersControlWidget *_playersWidget;

    QHBoxLayout *_myCardsLayout;
    QHBoxLayout *_communityCardsLayout;
    QHBoxLayout *_extraInfoLayout;
    QVBoxLayout *_mainLayout;

    QStringList _valuesList;
    QStringList _colorsList;
    QStringList _beforeBidList;
    QStringList _afterBidList;


    ModelViewMatching<TexasHoldem::desecition,DecesionMatcher>* _decesionMatcher;
    ModelViewMatching<TexasHoldem::CardValueType,CardValueMatcher>* _cardValueMatcher;
    ModelViewMatching<TexasHoldem::color,CardColorMatcher>* _cardColorMatcher;




};
}



#endif // GEMEWIDGET_H
