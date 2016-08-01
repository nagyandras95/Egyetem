#include "threadnumbersetdialog.h"

ThreadNumberSetDialog::ThreadNumberSetDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(trUtf8("Thread setter dialog"));

    _threadSetter = new AmountSetter("Set number of threads: ",1,10);

    _okButton = new QPushButton("Accept");
    _rejectButton = new QPushButton("Reject");

    _mainLayout = new QVBoxLayout;
    _mainLayout->addWidget(_threadSetter);
    _mainLayout->addWidget(_okButton);

    connect(_okButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(_rejectButton,SIGNAL(clicked()),this,SLOT(reject()));

    setLayout(_mainLayout);

}
