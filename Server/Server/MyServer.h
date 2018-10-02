#ifndef MyServer_h
#define MyServer_h

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTextEdit>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QBoxLayout>
#include <QLabel>
#include <QTime>
#include <QFile>

class QTcpServer;
class QTextEdit;
class QTcpSocket;

class MyServer : public QWidget {
    Q_OBJECT
private:
    QTcpServer * m_ptcpServer;
    QTextEdit*  m_ptxt;
    quint16     m_nNextBlockSize;

public:
    MyServer(int nPort, QWidget* pwgt = 0);

    public slots:
    virtual void slotNewConnection();
};
#endif  //_MyServer_h_