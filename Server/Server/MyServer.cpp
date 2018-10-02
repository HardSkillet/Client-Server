#include "myserver.h"
MyServer::MyServer(int nPort, QWidget* pwgt /*=0*/) : QWidget(pwgt)
, m_nNextBlockSize(0)
{
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        QMessageBox::critical(0,
            "Server Error",
            "Unable to start the server:"
            + m_ptcpServer->errorString()
        ); 
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, SIGNAL(newConnection()),
        this, SLOT(slotNewConnection())
    );

    m_ptxt = new QTextEdit;
    m_ptxt->setReadOnly(true);

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Server</H1>"));
    pvbxLayout->addWidget(m_ptxt);
    setLayout(pvbxLayout);
}
/*virtual*/ void MyServer::slotNewConnection()
{
    QTcpSocket *socket = m_ptcpServer->nextPendingConnection();

    QFile file("VNATURE.jpg");
    file.open(QIODevice::WriteOnly);

    while (socket->waitForReadyRead(3000)) {
        qDebug() << "Reading: " << socket->bytesAvailable();
        QByteArray str = QByteArray::fromBase64(socket->readAll());
        file.write(str);
    }
    file.close();
    cv::Mat img0 = cv::imread("VNATURE.jpg", 0);

    cv::Canny(img0, img0, 45, 200);
    cv::imwrite("tmp.jpg", img0);
    QFile file1("tmp.jpg");

    file1.open(QIODevice::ReadOnly);
    QByteArray buf = file1.readAll();
    file1.close();

    socket->write(buf.toBase64());
    qDebug() << buf.size();
    socket->waitForBytesWritten(-1);

    socket->close();
}

