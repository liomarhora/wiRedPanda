// Copyright 2015 - 2021, GIBIS-Unifesp and the wiRedPanda contributors
// SPDX-License-Identifier: GPL-3.0-or-later

#include "thememanager.h"

#include <QApplication>
#include <QSettings>

ThemeManager *ThemeManager::globalMngr = nullptr;

Theme ThemeManager::theme() const
{
    return m_theme;
}

void ThemeManager::setTheme(const Theme &theme)
{
    m_attrs.setTheme(theme);
    if (m_theme != theme) {
        m_theme = theme;
        QSettings settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
        settings.setValue("theme", static_cast<int>(theme));
        emit themeChanged();
    }
}

void ThemeManager::initialize()
{
    emit themeChanged();
}

ThemeAttrs ThemeManager::getAttrs() const
{
    return m_attrs;
}

ThemeManager::ThemeManager(QObject *parent)
    : QObject(parent)
    , m_theme(Theme::Panda_Light)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    if (settings.contains("theme")) {
        m_theme = static_cast<Theme>(settings.value("theme").toInt());
    }
    setTheme(m_theme);
}

ThemeAttrs::ThemeAttrs()
{
    setTheme(Theme::Panda_Light);
}

void ThemeAttrs::setTheme(const Theme &thm)
{
    switch (thm) {
    case Theme::Panda_Light:
        scene_bgBrush = QColor("#ffffe6");
        scene_bgDots = QColor(Qt::darkGray);
        selectionBrush = QColor(175, 0, 0, 80);
        selectionPen = QColor(175, 0, 0, 255);

        graphicElement_labelColor = QColor(Qt::black);

        qneConnection_selected = selectionPen;

        qneConnection_true = QColor(Qt::green);
        qneConnection_false = QColor(Qt::darkGreen);
        qneConnection_invalid = QColor(Qt::red);

#ifndef Q_OS_MAC
        qApp->setPalette(defaultPalette);
        qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
#endif

        break;
    case Theme::Panda_Dark:
        scene_bgBrush = QColor("#404552");
        scene_bgDots = QColor(Qt::black);
        selectionBrush = QColor(230, 255, 85, 150);
        selectionPen = QColor(230, 255, 85, 255);

        graphicElement_labelColor = QColor(Qt::white);

        qneConnection_selected = selectionPen;

        qneConnection_true = QColor(115, 255, 220, 255);
        qneConnection_false = QColor(65, 150, 130, 255);

        qneConnection_invalid = QColor(Qt::red);

#ifndef Q_OS_MAC
        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
        darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);

        darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(120, 120, 120));
        darkPalette.setColor(QPalette::Disabled, QPalette::Base, QColor(120, 120, 120));
        darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(120, 120, 120));

        qApp->setPalette(darkPalette);
        qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
#endif

        break;
    }
    qnePort_true_pen = QColor(Qt::black);
    qnePort_false_pen = QColor(Qt::black);
    qnePort_invalid_pen = QColor(Qt::red);

    qnePort_true_brush = qneConnection_true;
    qnePort_false_brush = qneConnection_false;
    qnePort_invalid_brush = qneConnection_invalid;

    qnePort_hoverPort = QColor(Qt::yellow);

    qnePort_output_pen = QColor(Qt::darkRed);
    qnePort_output_brush = QColor("#f35369");
}
