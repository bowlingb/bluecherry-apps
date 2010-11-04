#include "ServerConfigWindow.h"
#include "core/DVRServer.h"
#include "core/BluecherryApp.h"
#include "ui/MainWindow.h"
#include <QBoxLayout>
#include <QWebView>

ServerConfigWindow *ServerConfigWindow::m_instance = 0;

ServerConfigWindow *ServerConfigWindow::instance()
{
    if (!m_instance)
    {
        m_instance = new ServerConfigWindow(bcApp->mainWindow);
        m_instance->setAttribute(Qt::WA_DeleteOnClose);
    }

    return m_instance;
}

ServerConfigWindow::ServerConfigWindow(QWidget *parent)
    : QWidget(parent, Qt::Window), m_server(0)
{
    setWindowTitle(tr("Bluecherry DVR - Server Configuration"));
    setMinimumSize(970, 600);
    resize(minimumSize());

    QBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);

    m_webView = new QWebView;
    m_webView->page()->setNetworkAccessManager(bcApp->nam);
    layout->addWidget(m_webView);
}

ServerConfigWindow::~ServerConfigWindow()
{
    if (m_instance == this)
        m_instance = 0;
}

void ServerConfigWindow::setServer(DVRServer *server)
{
    if (m_server == server)
        return;

    m_server = server;

    if (server)
    {
        m_webView->load(server->api->serverUrl());
        setWindowTitle(tr("Bluecherry DVR - %1").arg(server->displayName()));
    }

    emit serverChanged(m_server);
}
