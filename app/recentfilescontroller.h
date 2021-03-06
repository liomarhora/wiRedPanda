/*
 * Copyright 2015 - 2021, GIBIS-Unifesp and the wiRedPanda contributors
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef RECENTFILESCONTROLLER_H
#define RECENTFILESCONTROLLER_H

#include <QObject>

/**
 * Class to hold the list of recent open files and IC
 */
class RecentFilesController : public QObject
{
    Q_OBJECT

public:
    static constexpr int MaxRecentFiles = 10;
    explicit RecentFilesController(const QString &_attrName, QObject *parent = nullptr, bool saveSetting = true);
    QStringList getRecentFiles();

signals:
    void recentFilesUpdated();

public slots:
    void addRecentFile(const QString &fname);

private:
    void saveRecentFiles();
    QString m_attrName;
    bool m_saveSetting;
    QStringList m_files;
};

#endif /* RECENTFILESCONTROLLER_H */
