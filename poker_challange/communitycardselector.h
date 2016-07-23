#ifndef COMMUNITYCARDSELECTOR_H
#define COMMUNITYCARDSELECTOR_H

#include <QObject>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>

class CommunityCardSelector : public QWidget
{
    Q_OBJECT
public:
    explicit CommunityCardSelector(QString labelMessage,const QStringList& valueList_, const QStringList& colorList_,
                                   QWidget *parent = 0);

    bool comminityCardIsActive() {return _enableChack->isChecked();}
    std::pair<QComboBox*,QComboBox*> getCardBoxes() {return _boxes;}

signals:

public slots:
private slots:
    void setEnable(int);
private:
    std::pair<QComboBox*,QComboBox*> _boxes;
    QLabel* _label;
    QCheckBox* _enableChack;

    QVBoxLayout *_mainLayout;
    QHBoxLayout *_communityCardLayout;
    QHBoxLayout *_communityCardInfoLayout;
};

#endif // COMMUNITYCARDSELECTOR_H
