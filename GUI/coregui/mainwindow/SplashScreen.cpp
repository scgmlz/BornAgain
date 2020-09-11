// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/SplashScreen.cpp
//! @brief     Implements class SplashScreen
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/SplashScreen.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QCoreApplication>
#include <QDebug>
#include <QElapsedTimer>
#include <QStyle>
#include <QTime>

SplashScreen::SplashScreen(QWidget* parent) : QSplashScreen(parent), m_percentage_done(0)

{
    this->setPixmap(QPixmap(":/images/splashscreen.png"));
    this->setCursor(Qt::BusyCursor);

    QFont font;
    font.setPointSize(StyleUtils::SystemPointSize() * 0.9);
    font.setBold(false);
    this->setFont(font);
}

void SplashScreen::start(int show_during)
{
    show();
    QTime dieTime = QTime::currentTime().addMSecs(show_during);
    QElapsedTimer timer;
    timer.start();
    while (QTime::currentTime() < dieTime) {
        setProgress(timer.elapsed() / (show_during / 100));
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void SplashScreen::setProgress(int value)
{
    m_percentage_done = value;
    if (m_percentage_done > 100)
        m_percentage_done = 100;
    if (m_percentage_done < 0)
        m_percentage_done = 0;
    update();
}

void SplashScreen::drawContents(QPainter* painter)
{
    QSplashScreen::drawContents(painter);

    auto img_rect = frameGeometry();
    auto char_height = StyleUtils::SizeOfLetterM().height();

    QRect textRect(img_rect.width() * 0.02, img_rect.height() - char_height * 2.5,
                   img_rect.width() * 0.5, char_height * 3);

    QString versionText = QString("version ").append(GUIHelpers::getBornAgainVersionString());
    style()->drawItemText(painter, textRect, 0, this->palette(), true, versionText);

    QString loadingText("loading . ");
    for (size_t i = 0; i < size_t(m_percentage_done / 20); ++i) {
        loadingText.append(". ");
    }

    QRect loadingRect(img_rect.width() * 0.8, img_rect.height() - char_height * 2.5,
                      img_rect.width(), char_height * 3);
    style()->drawItemText(painter, loadingRect, 0, this->palette(), true, loadingText);
}
