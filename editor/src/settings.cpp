/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2011 ~ 2018 Deepin, Inc.
 *               2011 ~ 2018 Wang Yong
 *
 * Author:     Wang Yong <wangyong@deepin.com>
 * Maintainer: Wang Yong <wangyong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "settings.h"

#include "dthememanager.h"
#include <DSettings>
#include <DSettingsOption>
#include <QStyleFactory>
#include <QFontDatabase>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>

DWIDGET_USE_NAMESPACE
DTK_USE_NAMESPACE

Settings::Settings(QObject *parent) : QObject(parent)
{
    backend = new Dtk::Core::QSettingBackend(QDir(QDir(QDir(QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first()).filePath(qApp->organizationName())).filePath(qApp->applicationName())).filePath("config.conf"));

    settings = Dtk::Core::DSettings::fromJsonFile(":/resource/settings.json");
    settings->setBackend(backend);

    connect(settings, &Dtk::Core::DSettings::valueChanged, this,
            [=] (const QString &, const QVariant &) {
                settings->sync();
            });

    auto fontSize = settings->option("base.font.size");
    connect(fontSize, &Dtk::Core::DSettingsOption::valueChanged,
            this, [=](QVariant value) {
                      adjustFontSize(value.toInt());
                  });

    auto tabSpaceNumber = settings->option("advance.editor.tab_space_number");
    connect(fontSize, &Dtk::Core::DSettingsOption::valueChanged,
            this, [=](QVariant value) {
                      adjustTabSpaceNumber(value.toInt());
                  });

    QFontDatabase fontDatabase;
    auto fontFamliy = settings->option("base.font.family");
    QMap<QString, QVariant> fontDatas;

    QStringList values = fontDatabase.families();
    QStringList keys = values;
    fontDatas.insert("keys", keys);
    fontDatas.insert("values", values);
    fontFamliy->setData("items", fontDatas);

    if (fontFamliy->value().toString().isEmpty()) {
        fontFamliy->setValue(QFontDatabase::systemFont(QFontDatabase::FixedFont).family());
    }

    connect(fontFamliy, &Dtk::Core::DSettingsOption::valueChanged,
            this, [=](QVariant value) {
                      adjustFont(value.toString());
                  });

    auto keymap = settings->option("shortcuts.keymap.keymap");
    keymap->setData("items", QStringList() << "Standard" << "Emacs" << "Customize");

    auto windowState = settings->option("advance.window.window_state");
    QMap<QString, QVariant> windowStateMap;
    windowStateMap.insert("keys", QStringList() << "window_normal" << "window_maximum" << "fullscreen");
    windowStateMap.insert("values", QStringList() << "Window" << "Maximum" << "Fullscreen");
    windowState->setData("items", windowStateMap);
    
    settingsDialog.setProperty("_d_dtk_theme", "light");
    settingsDialog.setProperty("_d_QSSFilename", "DSettingsDialog");
    DThemeManager::instance()->registerWidget(&settingsDialog);
    settingsDialog.updateSettings(settings);
    dtkThemeWorkaround(&settingsDialog, "dlight");
}

Settings::~Settings()
{
}

void Settings::popupSettingsDialog()
{
    settingsDialog.exec();
}

// This function is workaround, it will remove after DTK fixed SettingDialog theme bug.
void Settings::dtkThemeWorkaround(QWidget *parent, const QString &theme)
{
    parent->setStyle(QStyleFactory::create(theme));
    for (auto obj : parent->children()) {

        auto w = qobject_cast<QWidget *>(obj);
        if (!w) {
            continue;
        }

        dtkThemeWorkaround(w, theme);
    }
}
