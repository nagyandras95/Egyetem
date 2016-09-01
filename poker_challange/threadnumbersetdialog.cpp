#include "threadnumbersetdialog.h"

namespace TexasHoldemView
{
ThreadNumberSetDialog::ThreadNumberSetDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(trUtf8("Thread setter dialog"));

    _threadSetter = new AmountSetter("Set number of threads: ",1,10);

    _okButton = new QPushButton("Accept");
    _rejectButton = new QPushButton("Cancel");

    _mainLayout = new QVBoxLayout;
    _buttonLayout = new QHBoxLayout;
    _mainLayout->addWidget(_threadSetter);
    _buttonLayout->addWidget(_okButton);
    _buttonLayout->addWidget(_rejectButton);
    _mainLayout->addLayout(_buttonLayout);

    connect(_okButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(_rejectButton,SIGNAL(clicked()),this,SLOT(reject()));

    setLayout(_mainLayout);

}
}


