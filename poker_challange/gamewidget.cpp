#include "gamewidget.h"
#include <QTextStream>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <assert.h>
#include <algorithm>
#include "communitycardselector.h"
#include "privatecardselector.h"
#include "model/card.h"

namespace TexasHoldemView
{
GameWidget::GameWidget(TexasHoldemModel *model, QWidget *parent) : QWidget(parent)
{
    _model = model;

    _decesionMatcher = new DecesionMatcher();
    _cardValueMatcher = new CardValueMatcher();
    _cardColorMatcher = new CardColorMatcher();
    initChoiceLists();
    initValueAndColorList();

    _firstCard = new PrivateCardSelector("First card:",_valuesList,_colorsList);
    _secondCard = new PrivateCardSelector("Second card:",_valuesList,_colorsList);
    for(unsigned int i = 0; i < 5; i++)
    {
        _communityCards.push_back(new CommunityCardSelector("Card dilerred: ",_valuesList,_colorsList));
    }

    _potSetter = new AmountSetter("Pot:",0,1000);
    _yourBetSetter = new AmountSetter("Your Bet:",0,500);
    _nOfPlayersSetter = new AmountSetter("Plyers:",2,10);
    _yourNumberSetter = new AmountSetter("Your number:",1,23);
    _smallBlindSetter = new AmountSetter("Small blind bet:",1,500);
    _bigBlindSetter = new AmountSetter("Big blind bet:",2,500);

    _playersWidget = new PlayersControlWidget();


    _myCardsLayout = new QHBoxLayout;
    _communityCardsLayout = new QHBoxLayout;
    _extraInfoLayout = new QHBoxLayout;

    _myCardsLayout->addWidget(_firstCard);
    _myCardsLayout->addWidget(_secondCard);
    for(unsigned int i = 0; i < _communityCards.size(); i++)
    {
        _communityCardsLayout->addWidget(_communityCards[i]);
    }

    _extraInfoLayout->addWidget(_potSetter);
    _extraInfoLayout->addWidget(_yourBetSetter);
    _extraInfoLayout->addWidget(_nOfPlayersSetter);
    _extraInfoLayout->addWidget(_yourNumberSetter);
    _extraInfoLayout->addWidget(_smallBlindSetter);
    _extraInfoLayout->addWidget(_bigBlindSetter);

    _mainLayout = new QVBoxLayout;
    _mainLayout->addWidget(_playersWidget);
    _mainLayout->addLayout(_communityCardsLayout);
    _mainLayout->addLayout(_myCardsLayout);
    _mainLayout->addLayout(_extraInfoLayout);

    setLayout(_mainLayout);

    _potSetter->setActive(false);
    _yourBetSetter->setActive(false);
    initSelections();



}

GameWidget::~GameWidget()
{
    delete _decesionMatcher;
    delete _cardValueMatcher;
    delete _cardColorMatcher;

    for(unsigned int i = 0; i < _communityCards.size(); i++)
    {
        _communityCardsLayout->removeWidget(_communityCards[i]);
        delete _communityCards[i];
    }

    _myCardsLayout->removeWidget(_firstCard);
    _myCardsLayout->removeWidget(_secondCard);
    delete _firstCard;
    delete _secondCard;

    _extraInfoLayout->removeWidget(_potSetter);
    _extraInfoLayout->removeWidget(_yourBetSetter);
    _extraInfoLayout->removeWidget(_nOfPlayersSetter);

    delete _potSetter;
    delete _yourBetSetter;
    delete _nOfPlayersSetter;

    delete _communityCardsLayout;
    delete _myCardsLayout;
    delete _extraInfoLayout;
    delete _mainLayout;

}


void GameWidget::newGameStarted(std::vector<Player> state)
{
    _playersWidget->setNOfPlayer((int) state.size());
    _playersWidget->setPossibleChoices(_afterBidList);
    for(unsigned int i = 0; i < state.size(); ++i)
    {
        _playersWidget->setPlayerTextDecesion(i,_decesionMatcher->match(state[i].lastDesecition));
        _playersWidget->setPlayerBet(i,state[i].bet);
        _playersWidget->setPalyerActive(i,false);
    }


    for(CardSelector* selector : _communityCards)
    {
        selector->setEnabled(false);
    }

    _potSetter->setActive(false);
    _yourBetSetter->setActive(false);
    _nOfPlayersSetter->setActive(false);
    _yourNumberSetter->setActive(false);
    _smallBlindSetter->setActive(false);
    _bigBlindSetter->setActive(false);

}

void GameWidget::stepGame()
{
    _model->stepGame(_decesionMatcher->invertMatch(_playersWidget->getActivePlayerDecesion()),
                     _playersWidget->getActivePlayerBet());
}

void GameWidget::changeActivePlayer(int playerNumber)
{
    _playersWidget->changeActivePlayer(playerNumber);
}

void GameWidget::switchCoiceOption(bool beforeBet)
{
    if(beforeBet)
    {
        _playersWidget->setPossibleChoices(_beforeBidList);
    }
    else
    {
        _playersWidget->setPossibleChoices(_afterBidList);
    }
}

void GameWidget::givePairs()
{
    _model->setYourCards(resolveCard(_firstCard->getCardBoxes()),resolveCard(_secondCard->getCardBoxes()));
    _firstCard->setEnabled(false);
    _secondCard->setEnabled(false);
    _model->startRound();

}

void GameWidget::enableCommunityCardSelection(int from, int to)
{
    _playersWidget->inactivatePlayer();
    for(int i = from; i <= to; ++i)
    {
        _communityCards[i]->setEnabled(true);
    }
}

void GameWidget::addActiveCommunityCards()
{

    std::list<card> cards;
    for(CardSelector* selector : _communityCards)
    {
        if(selector->isEnabled())
            cards.push_back(resolveCard(selector->getCardBoxes()));

        selector->setEnabled(false);

    }
    _model->addCommunityCards(cards);
    _model->startRound();

}

void GameWidget::changeNofPlayers(int n) {
    _nOfPlayersSetter->setAmount(n);
}

void GameWidget::changePot(int n) {
    _potSetter->setAmount(n);
}

void GameWidget::changeYourBet(int n) {
    _yourBetSetter->setAmount(n);
}

void GameWidget::initSelections()
{
    _playersWidget->clearPlayers();
    for(CardSelector* selector : _communityCards)
    {
        selector->setEnabled(false);
    }

    _firstCard->setEnabled(true);
    _secondCard->setEnabled(true);
    _nOfPlayersSetter->setActive(true);
    _yourNumberSetter->setActive(true);
    _smallBlindSetter->setActive(true);
    _bigBlindSetter->setActive(true);
}

void GameWidget::initValueAndColorList()
{
    for(int i = 2; i <= 14; i++)
    {
        _valuesList.push_back(_cardValueMatcher->match(i));
    }

    _colorsList.push_back(_cardColorMatcher->match(card::color::hearts));
    _colorsList.push_back(_cardColorMatcher->match(card::color::diamonds));
    _colorsList.push_back(_cardColorMatcher->match(card::color::clubs));
    _colorsList.push_back(_cardColorMatcher->match(card::color::spades));
}

void GameWidget::initChoiceLists()
{
    _beforeBidList.append(_decesionMatcher->match(TexasHoldem::none));
    _beforeBidList.append(_decesionMatcher->match(TexasHoldem::bet));
    _beforeBidList.append(_decesionMatcher->match(TexasHoldem::check));
    _beforeBidList.append(_decesionMatcher->match(TexasHoldem::fold));

    _afterBidList.append(_decesionMatcher->match(TexasHoldem::none));
    _afterBidList.append(_decesionMatcher->match(TexasHoldem::fold));
    _afterBidList.append(_decesionMatcher->match(TexasHoldem::call));
    _afterBidList.append(_decesionMatcher->match(TexasHoldem::raise));

}

card GameWidget::resolveCard(std::pair<QComboBox*,QComboBox*> pair)
{

    return card(_cardValueMatcher->invertMatch(pair.first->currentText()) ,
                _cardColorMatcher->invertMatch(pair.second->currentText()));
}
}




