#ifndef CARDSELECTOR_H
#define CARDSELECTOR_H


#include <QLabel>
#include <QComboBox>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>

class CardSelector : public QWidget
{
    Q_OBJECT
public:
    explicit CardSelector(QString labelMessage,const QStringList& valueList_, const QStringList& colorList_,
                          QWidget *parent = 0);
    virtual ~CardSelector();

    std::pair<QComboBox*,QComboBox*> getCardBoxes() {return _boxes;}
    virtual bool selectionIsActive() = 0;

signals:
    void cardChanged(QString,QString);
public slots:

private slots:
    void cardParameterChanged(QString);

protected:
    QLabel* _label;
    std::pair<QComboBox*,QComboBox*> _boxes;



};

#endif // CARDSELECTOR_H
