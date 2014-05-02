#ifndef CONVOTAB_H
#define CONVOTAB_H

#include <QWidget>
#include <tabdialog.h>
#include <QString>
#include "sendtoencrypt.h"
#include "sendtoclient.h"

namespace Ui {
class convoTab;
}

class convoTab : public QWidget
{
    Q_OBJECT
    
public:
    explicit convoTab(const QString &name, QWidget *parent = 0);
    QString sender;
    int* sock;

    void receiveMsg(string mess);
    ~convoTab();
private slots:
void sendmessage();
    
private:
    Ui::convoTab *ui;
    QString getmessage();

    void updateconvo(QString addmsg);
};

#endif // CONVOTAB_H
