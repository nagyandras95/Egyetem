#ifndef AMOUNTSETTER_H
#define AMOUNTSETTER_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>

class AmountSetter : public QWidget
{
    Q_OBJECT
public:
    explicit AmountSetter(QString labelMessage,QWidget *parent = 0);

    int getAmount() const {return _setterSpinBox->value();}

signals:

public slots:

private:
    QLabel *_label;
    QSpinBox *_setterSpinBox;

    QHBoxLayout *_setterLayout;
};

#endif // AMOUNTSETTER_H
