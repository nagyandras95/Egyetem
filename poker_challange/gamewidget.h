#ifndef GEMEWIDGET_H
#define GEMEWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include <QLabel>
#include <QLineEdit>
#include <QStringList>
#include <QString>
#include <QCheckBox>
#include "card.h"
#include "texasholdemmodel.h"
#include "communitycardselector.h"


class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);


signals:
    void hintAdded(QString hint);
public slots:
    void getHint();

private:

    void setConfiguration();
    card resolveCard(std::pair<QComboBox*,QComboBox*>);
    QString matchColors(card::color);
    card::color invertMatchColor(QString colorString);

    TexasHoldemModel _model;

    std::pair<QComboBox*,QComboBox*> _firstCardBoxes;
    std::pair<QComboBox*,QComboBox*> _secondCardBoxes;

    std::vector<CommunityCardSelector*> _communityCards;

    QStringList _valuesList;
    QStringList _colorsList;


    QLabel* _card1Label;
    QLabel* _card2Label;
    QHBoxLayout *_myCardsLayout;
    QHBoxLayout *_communityCardsLayout;
    QVBoxLayout *_mainLayout;




};

#endif // GEMEWIDGET_H
