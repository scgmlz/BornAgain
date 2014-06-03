#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>
#include "mainwindow.h"
#include "mainwindow_constants.h"
#include "projectmanager.h"
#include <QString>
#include "qpushbutton.h"
#include <QCommandLinkButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QSignalMapper>


class ContainerWidget : public QWidget
{
    Q_OBJECT
public:
    ContainerWidget(QWidget *parent = 0);
    virtual ~ContainerWidget(){}
    QSize sizeHint() const;
};


class WelcomeView : public QWidget
{
    Q_OBJECT

public:
    WelcomeView(MainWindow *parent);

public slots:
    void onWebLinkClicked(const QUrl &url);
    //void onNewProject();
    //void onOpenProject();
    void onNewUser();
    void updateRecentProjectPanel();

private:
    QPushButton *newProjectButton;
    QPushButton *openProjectButton;
    QPushButton *newUsertButton;
    MainWindow *m_mainWindow;
    ProjectManager *m_projectManager;
    void generateRecentProjectList();
    QSignalMapper *m_signalMapper;
    QVBoxLayout *m_recentProjectLayout;
    void clearLayout(QLayout* layout, bool deleteWidgets = true);
};

#endif // WELCOMEVIEW_H
