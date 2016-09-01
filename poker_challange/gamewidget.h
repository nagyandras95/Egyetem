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
#include "model/texasholdemmodel.h"
#include "cardselector.h"
#include "amountsetter.h"
#include "threadnumbersetdialog.h"
#include "playerscontrolwidget.h"

namespace TexasHoldemView {
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(TexasHoldemModel* model,QWidget *parent = 0);
    ~GameWidget();

    int getnOfPlayers() {return _nOfPlayersSetter->getAmount();}
    int getYourNumber() {return _yourNumberSetter->getAmount();}
    int getSmallBlindBet() {return _smallBlindSetter->getAmount();}
    int getBigBlindBet() {return _bigBlindSetter->getAmount();}


signals:
    void hintAdded(QString hint);
public slots:
    void getHint();

    void newGameStarted(std::vector<Player> state);
    void stepGame();
    void changeActivePlayer(int playerNumber);
    void switchCoiceOption(bool beforeBet);
    void givePairs();
    void enableCommunityCardSelection(int,int);
    void addActiveCommunityCards();

    void changeNofPlayers(int n);
    void changePot(int n);
    void changeYourBet(int n);

    void initSelections();

private:

    void setConfiguration();
    void initValueAndColorList();
    void initColorMatchingMap();
    void initValueMatchingMap();
    void initDesecationMatching();
    void initChoiceLists();

    card resolveCard(std::pair<QComboBox*,QComboBox*>);

    QString matchColors(card::color);
    card::color invertMatchColor(QString colorString);

    QString matchValue(int);
    int invertMatchValue(QString valueString);

    QString matchDecesion(TexasHoldem::desecition);
    TexasHoldem::desecition invertMatchDecesion(QString);

    TexasHoldemModel* _model;

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

    QStringList _valuesList;
    QStringList _colorsList;
    QStringList _beforeBidList;
    QStringList _afterBidList;

    QHBoxLayout *_myCardsLayout;
    QHBoxLayout *_communityCardsLayout;
    QHBoxLayout *_extraInfoLayout;
    QVBoxLayout *_mainLayout;


    std::map<card::color,QString> _colorMatchingMap;
    std::map<int,QString> _valueMatching;
    std::map<TexasHoldem::desecition,QString> _decesationMatching;




};
}



#endif // GEMEWIDGET_H
