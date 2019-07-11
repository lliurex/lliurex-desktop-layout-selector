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

#include "window.hpp"


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QQmlContext>

#include <iostream>

using namespace lliurex::dls;
using namespace std;

Window::Window() : QWidget()
{
    QVBoxLayout* vbox = new QVBoxLayout();
    QHBoxLayout* hbox = new QHBoxLayout();
    
    QPushButton* btnApply = new QPushButton("Apply");
    QPushButton* btnCancel = new QPushButton("Cancel");
    
    hbox->addWidget(btnApply);
    hbox->addWidget(btnCancel);
    
    qmlWidget = new QQuickWidget();
    
    QList<QObject*> data;
    
    QVariantList args;
    //KCMLookandFeel* kcm = new KCMLookandFeel(nullptr,args);
    
    data.append(new LNFPackage("Default","/usr/share/plasma/look-and-feel/lliurex-desktop"));
    data.append(new LNFPackage("Classic","/usr/share/plasma/look-and-feel/lliurex-desktop-classic"));
    
    QQmlContext* ctxt = qmlWidget->rootContext();
    ctxt->setContextProperty("kcm", QVariant::fromValue(data));
    
    qmlWidget->setClearColor(QColor(0xf1,0xf2,0xf3));
    qmlWidget->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    
    vbox->addWidget(qmlWidget);
    vbox->addLayout(hbox);
    
    setLayout(vbox);
}

Window::~Window()
{
}