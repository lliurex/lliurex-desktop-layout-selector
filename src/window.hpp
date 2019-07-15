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

#ifndef LLIUREX_DLS_WINDOW
#define LLIUREX_DLS_WINDOW

#include <QWidget>
#include <QQuickWidget>
#include <QDialogButtonBox>

namespace lliurex
{
    namespace dls
    {
        class LNFPackage : public QObject
        {
            Q_OBJECT

            Q_PROPERTY(QString name MEMBER name NOTIFY onNameChanged)
            Q_PROPERTY(QString path MEMBER path NOTIFY onPathChanged)
            
            signals:
                
            void onNameChanged();
            void onPathChanged();
                
            public:
            
            QString name;
            QString path;
            
            LNFPackage(QString name,QString path)
            {
                this->name=name;
                this->path=path;
            }
        };
        
        class Window: public QWidget
        {
            Q_OBJECT
            
            private:
            
            QQuickWidget* qmlWidget;
            QDialogButtonBox* dlg;
            
            private slots:
            
            void clicked(QAbstractButton* button);
            
            public:
            
            Window();
            virtual ~Window();
        };
    }
}

#endif