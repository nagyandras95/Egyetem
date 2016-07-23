#ifndef GEMEWIDGET_H
#define GEMEWIDGET_H

#include <QWidget>
#include <QGridLayout>
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
    card::color invert_match_colors(QString colorString);

    TexasHoldemModel _model;

    QGridLayout* _layout;

    std::pair<QComboBox*,QComboBox*> _firstCardBoxes;
    std::pair<QComboBox*,QComboBox*> _secondCardBoxes;

    std::vector<std::pair<QComboBox*,QComboBox*> > _communityCardsBoxes;
    std::vector<QLabel*> _communityCardsLabels;
    std::vector<QCheckBox*> _communityCardsChackes;

    QStringList _valuesList;
    QStringList _colorsList;


    QLabel* _card1Label;
    QLabel* _card2Label;

    QHBoxLayout *_communityCardsLayout;
    QHBoxLayout *_communityCardsInfoLayout;
    QHBoxLayout *_myCardsLayout;
    QVBoxLayout *_mainLayout;




};

#endif // GEMEWIDGET_H
