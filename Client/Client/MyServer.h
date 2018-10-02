#ifndef MyServer_h
#define MyServer_h

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTextEdit>
#include <QBoxLayout>
#include <QLabel>
#include <QTime>

class QTcpServer;
class QTextEdit;
class QTcpSocket;

class MyServer : public QWidget {
    Q_OBJECT
private:
    QTcpServer * m_ptcpServer;
    QTextEdit*  m_ptxt;
    quint16     m_nNextBlockSize;

private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);

public:
    MyServer(int nPort, QWidget* pwgt = 0);

    public slots:
    virtual void slotNewConnection();
    void slotReadClient();
};
#endif  //_MyServer_h_