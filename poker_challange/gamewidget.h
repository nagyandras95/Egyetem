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
#include <QSpinBox>
#include <map>
#include "card.h"
#include "texasholdemmodel.h"
#include "cardselector.h"
#include "amountsetter.h"


class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();


signals:
    void hintAdded(QString hint);
public slots:
    void getHint();

private:

    void setConfiguration();
    void initColorMatchingMap();
    void initDesecationMatching();

    card resolveCard(std::pair<QComboBox*,QComboBox*>);

    QString matchColors(card::color);
    card::color invertMatchColor(QString colorString);

    QString matchValue(int);
    int invertMatchValue(QString value);

    TexasHoldemModel _model;

    CardSelector* _firstCard;
    CardSelector* _secondCard;

    std::vector<CardSelector*> _communityCards;

    AmountSetter* _potSetter;
    AmountSetter* _yourBetSetter;
    AmountSetter* _nOfPlayersSetter;

    QStringList _valuesList;
    QStringList _colorsList;

    QHBoxLayout *_myCardsLayout;
    QHBoxLayout *_communityCardsLayout;
    QHBoxLayout *_extraInfoLayout;
    QVBoxLayout *_mainLayout;


    std::map<card::color,QString> _colorMatchingMap;
    std::map<GamingTableConfiguration::options,QString> _decesationMatching;




};

#endif // GEMEWIDGET_H
