// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/aboutapplicationdialog.cpp
//! @brief     Implements class AboutApplicationDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/aboutapplicationdialog.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include "GUI/coregui/utils/CustomEventFilters.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QDate>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace
{

QLabel* createLinkLabel()
{
    auto result = new QLabel();
    result->setTextFormat(Qt::RichText);
    result->setTextInteractionFlags(Qt::TextBrowserInteraction);
    result->setText("<a href=\"http://www.bornagainproject.org\">www.bornagainproject.org</a>");
    result->setOpenExternalLinks(true);
    return result;
}

QLabel* createCopyrightLabel()
{
    QDate date = QDate::currentDate();
    QString copyright =
        QString("Copyright: Forschungszentrum Jülich GmbH ").append(date.toString("yyyy"));

    auto result = new QLabel(copyright);
    result->setContentsMargins(0, 0, 0, 15);
    return result;
}

QLabel* createLogoLabel()
{
    QPixmap logo(":/images/about_icon.awk", "JPG");
    auto result = new QLabel;
    result->setPixmap(logo.scaled(656, 674, Qt::KeepAspectRatio));
    return result;
}
} // namespace

AboutApplicationDialog::AboutApplicationDialog(QWidget* parent) : QDialog(parent)
{
    QColor bgColor(240, 240, 240, 255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);

    setWindowTitle("About BornAgain");
    setWindowFlags(Qt::Dialog);

    QHBoxLayout* detailsLayout = new QHBoxLayout;
    detailsLayout->addLayout(createLogoLayout());
    detailsLayout->addLayout(createTextLayout());

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(detailsLayout);
    mainLayout->addLayout(createButtonLayout());

    setLayout(mainLayout);
}

QBoxLayout* AboutApplicationDialog::createLogoLayout()
{
    auto result = new QVBoxLayout;

    QPixmap logo(":/images/about_icon.png");
    auto label = new QLabel;
    label->setPixmap(logo.scaled(120, 120, Qt::KeepAspectRatio));

    result->addWidget(label);
    result->addStretch(1);
    result->setContentsMargins(5, 5, 5, 5);

    return result;
}

QBoxLayout* AboutApplicationDialog::createTextLayout()
{
    auto result = new QVBoxLayout;

    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getLabelFontSize() + 2);
    titleFont.setBold(true);

    QFont normalFont;
    normalFont.setPointSize(DesignerHelper::getLabelFontSize());
    normalFont.setBold(false);

    // title
    auto aboutTitleLabel =
        new QLabel(QString("BornAgain version ").append(GUIHelpers::getBornAgainVersionString()));
    aboutTitleLabel->setFont(titleFont);
    aboutTitleLabel->setContentsMargins(0, 0, 0, 15);

    // copyright
    auto copyrightLabel = createCopyrightLabel();
    copyrightLabel->setFont(normalFont);

    // description
    QString description = "A software to simulate and fit grazing-incidence small-angle "
                          "scattering (GISAS) using distorted wave Born approximation (DWBA).";
    auto descriptionLabel = new QLabel(description);
    descriptionLabel->setFont(normalFont);
    descriptionLabel->setWordWrap(true);

    result->addWidget(aboutTitleLabel);
    result->addWidget(descriptionLabel);
    result->addStretch(1);
    result->addWidget(copyrightLabel);
    result->addWidget(createLinkLabel());
    result->addStretch(1);
    result->setContentsMargins(0, 5, 5, 5);

    return result;
}

QBoxLayout* AboutApplicationDialog::createButtonLayout()
{
    auto result = new QHBoxLayout;

    auto closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, this, &QDialog::reject);

    result->addStretch(1);
    result->addWidget(closeButton);

    static const char mydata[] = {0x64, 0x65, 0x76, 0x73};
    QByteArray b = QByteArray::fromRawData(mydata, sizeof(mydata));
    auto f = new ShortcodeFilter(b, this);
    connect(f, &ShortcodeFilter::found, this, [=]() { layout()->addWidget(createLogoLabel()); });
    installEventFilter(f);

    return result;
}
