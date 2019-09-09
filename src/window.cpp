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

#include <klocalizedstring.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QQmlContext>
#include <QQuickItem>
#include <QLabel>

#include <iostream>

using namespace lliurex::dls;
using namespace std;

#include <vector>
#include <utility>
#include <algorithm>

Window::Window() : QWidget()
{
    setWindowIcon(QIcon::fromTheme("preferences-desktop-theme"));
    setWindowTitle("LliureX desktop selector");
    QVBoxLayout* vbox = new QVBoxLayout();
    
    QLabel* label = new QLabel(i18n("Visual theme"));
    label->setStyleSheet("font: 16pt;");
    vbox->addWidget(label);
    
    qmlWidget = new QQuickWidget();
    qmlWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    
    lnf = new LNF();
    QQmlContext* ctxt = qmlWidget->rootContext();
    
    connect(lnf, &LNF::indexChanged, this, &Window::indexChanged);
    ctxt->setContextObject(lnf);
    
    qmlWidget->setClearColor(QColor(0x32,0xf9,0xf9));
    qmlWidget->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    qmlWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    
    vbox->addWidget(qmlWidget);
    vbox->setAlignment(Qt::AlignHCenter);
    
    dlg = new QDialogButtonBox(QDialogButtonBox::Apply);
    dlg->button(QDialogButtonBox::Apply)->setEnabled(false);
    
    connect(dlg, &QDialogButtonBox::clicked, this, &Window::clicked);
    vbox->addWidget(dlg);
    
    setLayout(vbox);
}

Window::~Window()
{
    delete lnf;
}

void Window::indexChanged()
{
    dlg->button(QDialogButtonBox::Apply)->setEnabled(true);
}

void Window::clicked(QAbstractButton* button)
{
    if (dlg->buttonRole(button)==QDialogButtonBox::ApplyRole) {
        button->setEnabled(false);
        
        Package* pkg = static_cast<Package*>(lnf->packages[lnf->index]);
        qDebug()<<"using "<<pkg->path;
        lnf->setTheme(pkg->path);
    }
}

