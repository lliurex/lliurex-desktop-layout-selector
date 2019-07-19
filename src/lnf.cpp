/*
    lliurex desktop layout selector

    Copyright (C) 2019  Enrique Medina Gremaldos <quiqueiii@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "lnf.hpp"

#include <KPluginLoader>
#include <KPluginFactory>
#include <QDebug>

#define KCM_PATH "/usr/lib/x86_64-linux-gnu/qt5/plugins/kcms/kcm_lookandfeel"

using namespace lliurex::dls;

LnF::LnF()
{
    KPluginLoader* loader = new KPluginLoader(KCM_PATH);
    KPluginFactory* factory = loader->factory();
    
    if (factory) {
        plugin = factory->create<QObject>();
        QMetaObject::invokeMethod(plugin,"load");
    }
    else {
        qWarning()<<"Failed to load KCM Look and feel plugin";
    }
}

LnF::~LnF()
{
}

QString LnF::getSelectedTheme()
{
    QVariant result = plugin->property("selectedPlugin");
    return result.value<QString>();
}