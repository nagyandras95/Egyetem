#include "gamewidget.h"
#include <QTextStream>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <assert.h>
#include "card.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    for(int i = 2; i <= 14; i++)
    {
        _valuesList.push_back(QString(std::to_string(i).c_str()));
    }

    _colorsList.push_back(matchColors(card::color::hearts));
    _colorsList.push_back(matchColors(card::color::diamonds));
    _colorsList.push_back(matchColors(card::color::clubs));
    _colorsList.push_back(matchColors(card::color::spades));

    _card1Label = new QLabel(trUtf8("first card:"));
    //_card1Label->setGeometry(2, 2, 50, 20);

    _card2Label = new QLabel(trUtf8("second card:"));
    //_card2Label->setGeometry(2, 2, 50, 20);

    _firstCardBoxes.first = new QComboBox();
    _firstCardBoxes.first->addItems(_valuesList);
    _firstCardBoxes.second = new QComboBox();
    _firstCardBoxes.second->addItems(_colorsList);
    _secondCardBoxes.first = new QComboBox();
    _secondCardBoxes.first->addItems(_valuesList);
    _secondCardBoxes.second = new QComboBox();
    _secondCardBoxes.second->addItems(_colorsList);


    for(unsigned int i = 0; i < 5; i++)
    {
        _communityCards.push_back(new CommunityCardSelector("card dilerred: ",_valuesList,_colorsList));
    }

    _myCardsLayout = new QHBoxLayout;
    _communityCardsLayout = new QHBoxLayout;

    _myCardsLayout->addWidget(_card1Label);
    _myCardsLayout->addWidget(_firstCardBoxes.first);
    _myCardsLayout->addWidget(_firstCardBoxes.second);
    _myCardsLayout->addWidget(_card2Label);
    _myCardsLayout->addWidget(_secondCardBoxes.first);
    _myCardsLayout->addWidget(_secondCardBoxes.second);

    for(unsigned int i = 0; i < _communityCards.size(); i++)
    {
        _communityCardsLayout->addWidget(_communityCards[i]);
    }

    _mainLayout = new QVBoxLayout;
    _mainLayout->addLayout(_communityCardsLayout);
    _mainLayout->addLayout(_myCardsLayout);

    setLayout(_mainLayout);



}

QString GameWidget::matchColors(card::color c)
{
    QString match = "";
    switch (c) {
    case card::color::hearts :
        return match = "Hearts";
        break;
    case card::color::diamonds :
        return match = "Diamonds";
        break;
    case card::color::clubs :
        return match = "Clubs";
        break;
    case card::color::spades :
        return match = "Spades";
        break;
    }
    return match;
}

card::color GameWidget::invertMatchColor(QString colorString)
{
    card::color c;
    if(matchColors(card::color::hearts) == colorString) c = card::color::hearts;
    else if(matchColors(card::color::diamonds) == colorString) c =  card::color::diamonds;
    else if(matchColors(card::color::clubs) == colorString) c = card::color::clubs;
    else if(matchColors(card::color::spades) == colorString) c = card::color::spades;

    return c;

}

void GameWidget::getHint()
{
    setConfiguration();
    QString hint = QString::number(_model.evaluate(),'d',2);
    emit hintAdded(hint);

}

void GameWidget::setConfiguration()
{
    _model.set_your_cards(resolveCard(_firstCardBoxes),resolveCard(_secondCardBoxes));
    std::list<card> cards;
    for(unsigned int i = 0; i < _communityCards.size(); i++)
    {
        if(_communityCards[i]->comminityCardIsActive())
        {
            cards.push_back(resolveCard(_communityCards[i]->getCardBoxes()));
        }
    }
    _model.set_community_cards(cards);

}

card GameWidget::resolveCard(std::pair<QComboBox*,QComboBox*> pair)
{

   return card( pair.first->currentText().toInt() ,
                invertMatchColor(pair.second->currentText()));
}


