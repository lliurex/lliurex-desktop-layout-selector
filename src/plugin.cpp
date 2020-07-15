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

#include "plugin.hpp"

#include <KPluginLoader>
#include <KPluginFactory>
#include <QStandardItemModel>
#include <QMetaProperty>
#include <QMetaObject>
#include <QDebug>

using namespace lliurex::dls::kcm;

Plugin::Plugin()
{
    QString path;
    path = KPluginLoader::findPlugin("kcms/kcm_lookandfeel");
    
    KPluginLoader* loader = new KPluginLoader(path);
    KPluginFactory* factory = loader->factory();
    
    if (factory) {
        plugin = factory->create<QObject>();
        QMetaObject::invokeMethod(plugin,"load");
        
        QVariant value = plugin->property("lookAndFeelModel");
        QStandardItemModel* model = value.value<QStandardItemModel* >();
        
        for (int n=0;n<model->rowCount();n++) {
            for (int m=0;m<model->columnCount();m++) {
                QStandardItem* item = model->item(n,m);
                qDebug()<<"* "<<item->text();
            }
        }
    }
    else {
        qWarning()<<"Failed to load KCM Look and feel plugin";
    }
}

Plugin::~Plugin()
{
}

QString Plugin::getSelectedTheme()
{
    QVariant value = plugin->property("lookAndFeelSettings");
    QObject* obj=value.value<QObject*>();
    
    value = obj->property("lookAndFeelPackage");
    return value.value<QString>();
}

void Plugin::setTheme(QString name)
{
    plugin->setProperty("resetDefaultLayout",true);
    
    QVariant value = plugin->property("lookAndFeelSettings");
    QObject* obj=value.value<QObject*>();
    
    obj->setProperty("lookAndFeelPackage",name);
    
    QMetaObject::invokeMethod(plugin,"save");
    
}