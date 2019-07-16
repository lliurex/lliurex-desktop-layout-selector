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
#include <QQuickItem>
#include <QLabel>

#include <iostream>

using namespace lliurex::dls;
using namespace std;

Window::Window() : QWidget()
{
    QVBoxLayout* vbox = new QVBoxLayout();
    
    vbox->addWidget(new QLabel("Aspecto visual"));
    
    qmlWidget = new QQuickWidget();
    qmlWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    
    QList<QObject*> data;
    
    QVariantList args;
    
    data.append(new LNFPackage("Default","/usr/share/plasma/look-and-feel/lliurex-desktop"));
    data.append(new LNFPackage("Classic","/usr/share/plasma/look-and-feel/lliurex-desktop-classic"));
    
    QQmlContext* ctxt = qmlWidget->rootContext();
    ctxt->setContextProperty("kcm", QVariant::fromValue(data));
    ctxt->setContextProperty("kcm.selection",32);
    
    qmlWidget->setClearColor(QColor(0x32,0xf9,0xf9));
    qmlWidget->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    qmlWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    
    vbox->addWidget(qmlWidget);
    vbox->setAlignment(Qt::AlignHCenter);
    
    dlg = new QDialogButtonBox(QDialogButtonBox::Apply);
    connect(dlg, &QDialogButtonBox::clicked, this, &Window::clicked);
    vbox->addWidget(dlg);
    
    setLayout(vbox);
}

Window::~Window()
{
}

void Window::clicked(QAbstractButton* button)
{
    if (dlg->buttonRole(button)==QDialogButtonBox::ApplyRole) {
        clog<<"Apply"<<endl;
        
        QQuickItem* root = qmlWidget->rootObject();
        
        if (root!=nullptr) {
            QQuickItem* selector = root->findChild<QQuickItem*>("lliurex.lnf.selector");
            
            if (selector!=nullptr) {
                QVariant value = selector->property("currentIndex");
                qDebug()<<value;
            }
        }
        
    }
}

