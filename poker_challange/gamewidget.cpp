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
#include "card.h"

GameWidget::GameWidget(TexasHoldemModel *model, QWidget *parent) : QWidget(parent)
{
    _model = model;

    initColorMatchingMap();
    initValueMatchingMap();
    initDesecationMatching();
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

QString GameWidget::matchColors(card::color c)
{
    return _colorMatchingMap[c];
}

card::color GameWidget::invertMatchColor(QString colorString)
{

    return std::find_if(_colorMatchingMap.begin(), _colorMatchingMap.end(),
                        [colorString](std::pair<card::color,QString> p){return p.second == colorString;})->first;

}

QString GameWidget::matchDecesion(TexasHoldem::desecition d)
{
    return _decesationMatching[d];
}

TexasHoldem::desecition GameWidget::invertMatchDecesion(QString decesionString)
{
    return std::find_if(_decesationMatching.begin(), _decesationMatching.end(),
                        [decesionString](std::pair<TexasHoldem::desecition,QString> p){return p.second == decesionString;})->first;
}

QString GameWidget::matchValue(int value)
{
    return _valueMatching[value];
}

int GameWidget::invertMatchValue(QString valueString)
{
    return std::find_if(_valueMatching.begin(), _valueMatching.end(),
                        [valueString](std::pair<int,QString> p){return p.second == valueString;})->first;
}

void GameWidget::getHint()
{
    //setConfiguration();
    QString hint = _decesationMatching[_model->evaluate()];
    emit hintAdded(hint);

}

void GameWidget::newGameStarted(std::vector<Player> state)
{
    _playersWidget->setNOfPlayer((int) state.size());
    _playersWidget->setPossibleChoices(_afterBidList);
    for(unsigned int i = 0; i < state.size(); ++i)
    {
        _playersWidget->setPlayerTextDecesion(i,matchDecesion(state[i].lastDesecition));
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
    _model->stepGame(invertMatchDecesion(_playersWidget->getActivePlayerDecesion()),
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

void GameWidget::setConfiguration()
{
    _model->setYourCards(resolveCard(_firstCard->getCardBoxes()),resolveCard(_secondCard->getCardBoxes()));
    std::vector<card> cards;
    for(unsigned int i = 0; i < _communityCards.size(); i++)
    {
        if(_communityCards[i]->selectionIsActive())
        {
            cards.push_back(resolveCard(_communityCards[i]->getCardBoxes()));
        }
    }
    _model->setCommunityCards(cards);
    _model->setNOfPlayers(_nOfPlayersSetter->getAmount());
    _model->setTotalPot(_potSetter->getAmount());
    _model->setYourBet(_yourBetSetter->getAmount());

}

void GameWidget::initValueAndColorList()
{
    for(int i = 2; i <= 14; i++)
    {
        _valuesList.push_back(matchValue(i));
    }

    _colorsList.push_back(matchColors(card::color::hearts));
    _colorsList.push_back(matchColors(card::color::diamonds));
    _colorsList.push_back(matchColors(card::color::clubs));
    _colorsList.push_back(matchColors(card::color::spades));
}

void GameWidget::initColorMatchingMap()
{


    _colorMatchingMap[card::color::clubs] = "Clubs";
    _colorMatchingMap[card::color::diamonds] = "Diamonds";
    _colorMatchingMap[card::color::hearts] = "Hearts";
    _colorMatchingMap[card::color::spades] = "Spades";


}

void GameWidget::initValueMatchingMap()
{
    for(int i = 2; i <= 10; ++i)
    {
        _valueMatching[i] = QString(std::to_string(i).c_str());
    }

    _valueMatching[11] = "B";
    _valueMatching[12] = "D";
    _valueMatching[13] = "K";
    _valueMatching[14] = "A";

}

void GameWidget::initDesecationMatching()
{
    _decesationMatching[TexasHoldem::none] = "";
    _decesationMatching[TexasHoldem::fold] = "Fold";
    _decesationMatching[TexasHoldem::call] = "Call";
    _decesationMatching[TexasHoldem::check] = "Check";
    _decesationMatching[TexasHoldem::bet] = "Bet";
    _decesationMatching[TexasHoldem::raise] = "Raise";

}

void GameWidget::initChoiceLists()
{
    _beforeBidList.append(_decesationMatching[TexasHoldem::none]);
    _beforeBidList.append(_decesationMatching[TexasHoldem::fold]);
    _beforeBidList.append(_decesationMatching[TexasHoldem::check]);
    _beforeBidList.append(_decesationMatching[TexasHoldem::bet]);

    _afterBidList.append(_decesationMatching[TexasHoldem::none]);
    _afterBidList.append(_decesationMatching[TexasHoldem::fold]);
    _afterBidList.append(_decesationMatching[TexasHoldem::call]);
    _afterBidList.append(_decesationMatching[TexasHoldem::raise]);

}

card GameWidget::resolveCard(std::pair<QComboBox*,QComboBox*> pair)
{

   return card( invertMatchValue(pair.first->currentText()) ,
                invertMatchColor(pair.second->currentText()));
}


