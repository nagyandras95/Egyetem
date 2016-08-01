#ifndef THREADNUMBERSETDIALOG_H
#define THREADNUMBERSETDIALOG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include "amountsetter.h"

class ThreadNumberSetDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ThreadNumberSetDialog(QWidget *parent = 0);

signals:

public slots:

public:
    int getNOfThreads() {return _threadSetter->getAmount();}

private:
    AmountSetter* _threadSetter;
    QPushButton *_okButton;
    QPushButton *_rejectButton;


    QVBoxLayout* _mainLayout;

};

#endif // THREADNUMBERSETDIALOG_H
