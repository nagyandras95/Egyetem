#ifndef COMMUNITYCARDSELECTOR_H
#define COMMUNITYCARDSELECTOR_H

#include <QObject>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>

class CommunityCardSelector : public QObject
{
    Q_OBJECT
public:
    explicit CommunityCardSelector(QString labelMessage,QObject *parent = 0);

signals:

public slots:
private slots:
    void setEnable(int);
private:
    std::pair<QComboBox*,QComboBox*> _boxes;
    QLabel* _label;
    QCheckBox* _enableChack;
};

#endif // COMMUNITYCARDSELECTOR_H
