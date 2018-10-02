#include "myclient.h"
#include "OpenCV.h"
MyClient::MyClient(const QString& strHost, int nPort, QWidget* pwgt /*=0*/) : 
QWidget(pwgt), m_nNextBlockSize(0)
{
    m_pTcpSocket = new QTcpSocket(this);

    m_pTcpSocket->connectToHost(strHost, nPort);

    m_ptxtInfo = new QTextEdit;
    m_ptxtInput = new QLineEdit;

    connect(m_pTcpSocket, SIGNAL(connected()), this, SLOT(slotSendToServer()));

    //Layout setup
}



void MyClient::slotSendToServer()
{   
    QFile file("VNATURE.jpg");
    file.open(QIODevice::ReadOnly);
    QByteArray buf = file.readAll();
    file.close();

    QFile file1("ANS.jpg");
    file1.open(QIODevice::WriteOnly);

    m_pTcpSocket->write(buf.toBase64());
    qDebug() << buf.size();
    m_pTcpSocket->waitForBytesWritten(-1);

    while (m_pTcpSocket->waitForReadyRead(-1)) {
        qDebug() << "Reading: " << m_pTcpSocket->bytesAvailable();
        QByteArray str = QByteArray::fromBase64(m_pTcpSocket->readAll());
        file1.write(str);
    }

    file1.close();
    m_pTcpSocket->close();

}
void MyClient::slotConnected()
{
    m_ptxtInfo->append("Received the connected() signal");
}