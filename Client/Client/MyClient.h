#ifndef _MyClient_h_
#define _MyClient_h_

#include "OpenCV.h"
#include <QFile>
#include <QWidget>
#include <QTcpSocket>
#include <QLineEdit>
#include <QTextEdit>
#include <QTime>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class QTextEdit;
class QLineEdit;

class MyClient : public QWidget {
    Q_OBJECT
private:
    QTcpSocket * m_pTcpSocket;
    QTextEdit*  m_ptxtInfo;
    QLineEdit*  m_ptxtInput;
    quint16     m_nNextBlockSize;

public:
    MyClient(const QString& strHost, int nPort, QWidget* pwgt = 0);

    private slots:
    void slotSendToServer();
    void slotConnected();
};
#endif    //_MyClient_h_