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

GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    initColorMatchingMap();

    for(int i = 2; i <= 14; i++)
    {
        _valuesList.push_back(QString(std::to_string(i).c_str()));
    }

    _colorsList.push_back(matchColors(card::color::hearts));
    _colorsList.push_back(matchColors(card::color::diamonds));
    _colorsList.push_back(matchColors(card::color::clubs));
    _colorsList.push_back(matchColors(card::color::spades));

    _firstCard = new PrivateCardSelector("First card:",_valuesList,_colorsList);
    _secondCard = new PrivateCardSelector("Second card:",_valuesList,_colorsList);
    for(unsigned int i = 0; i < 5; i++)
    {
        _communityCards.push_back(new CommunityCardSelector("Card dilerred: ",_valuesList,_colorsList));
    }

    _myCardsLayout = new QHBoxLayout;
    _communityCardsLayout = new QHBoxLayout;

    _myCardsLayout->addWidget(_firstCard);
    _myCardsLayout->addWidget(_secondCard);
    for(unsigned int i = 0; i < _communityCards.size(); i++)
    {
        _communityCardsLayout->addWidget(_communityCards[i]);
    }

    _mainLayout = new QVBoxLayout;
    _mainLayout->addLayout(_communityCardsLayout);
    _mainLayout->addLayout(_myCardsLayout);

    setLayout(_mainLayout);



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

    delete _communityCardsLayout;
    delete _myCardsLayout;
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

void GameWidget::getHint()
{
    setConfiguration();
    QString hint = QString::number(_model.evaluate());
    emit hintAdded(hint);

}

void GameWidget::setConfiguration()
{
    _model.set_your_cards(resolveCard(_firstCard->getCardBoxes()),resolveCard(_secondCard->getCardBoxes()));
    std::vector<card> cards;
    for(unsigned int i = 0; i < _communityCards.size(); i++)
    {
        if(_communityCards[i]->selectionIsActive())
        {
            cards.push_back(resolveCard(_communityCards[i]->getCardBoxes()));
        }
    }
    _model.set_community_cards(cards);

}

void GameWidget::initColorMatchingMap()
{


    _colorMatchingMap[card::color::clubs] = "Clubs";
    _colorMatchingMap[card::color::diamonds] = "Diamonds";
    _colorMatchingMap[card::color::hearts] = "Hearts";
    _colorMatchingMap[card::color::spades] = "Spades";


}

card GameWidget::resolveCard(std::pair<QComboBox*,QComboBox*> pair)
{

   return card( pair.first->currentText().toInt() ,
                invertMatchColor(pair.second->currentText()));
}


