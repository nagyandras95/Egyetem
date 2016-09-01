#ifndef AMOUNTSETTER_H
#define AMOUNTSETTER_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>
namespace TexasHoldemView {

class AmountSetter : public QWidget
{
    Q_OBJECT
public:
    explicit AmountSetter(QString labelMessage, int min, int max, QWidget *parent = 0);

    int getAmount() const {return _setterSpinBox->value();}
    void setAmount(int value) {_setterSpinBox->setValue(value);}
    void setActive(bool value = true) {_setterSpinBox->setEnabled(value);}

signals:
    void amountChanged(int);
public slots:

private slots:
    void valueChanged(int);

private:
    QLabel *_label;
    QSpinBox *_setterSpinBox;

    QHBoxLayout *_setterLayout;
};

}


#endif // AMOUNTSETTER_H
