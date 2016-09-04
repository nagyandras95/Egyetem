#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QComboBox>
#include <QHBoxLayout>

namespace TexasHoldemView {
class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWidget(QWidget *parent = 0);

    int getBet() {return _bet->value();}
    void setBet(int value) {_bet->setValue(value);}
    QString getDesecition() {return _desecition->currentText();}

    void setActivePlayer(bool active) {
        _bet->setEnabled(active);
        _desecition->setEnabled(active);
    }
    void setChoiceList(const QStringList& list) {_desecition->addItems(list);}
    void changeChoiceList(const QStringList& list) {_desecition->clear(); setChoiceList(list);}
    void setDecesion(QString decesion) {_desecition->setEditText(decesion);}

    void changeLicitOptions() {}

signals:

public slots:

private slots:

private:
    QSpinBox *_bet;
    QComboBox *_desecition;

    QStringList _firstLicitOptions;
    QStringList _secondLicitOptions;

    QHBoxLayout* _mainLayout;


};
}



#endif // PLAYERWIDGET_H
