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

#ifndef LLIUREX_DLS_LNF
#define LLIUREX_DLS_LNF

#include "plugin.hpp"

#include <QObject>
#include <QList>

namespace lliurex
{
    namespace dls
    {
        class Package: public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString name MEMBER name NOTIFY nameChanged)
            Q_PROPERTY(QString path MEMBER path NOTIFY pathChanged)
            
            signals:
            
            void nameChanged();
            void pathChanged();
            
            public:
                
            Package(QString name,QString path)
            {
                this->name=name;
                this->path=path;
            }
            
            QString name;
            QString path;
        };
        
        class LNF: public QObject
        {
            Q_OBJECT
            Q_PROPERTY(qint32 lnfCurrentIndex MEMBER currentIndex)
            Q_PROPERTY(qint32 lnfIndex MEMBER index NOTIFY indexChanged)
            Q_PROPERTY(QList<QObject*> lnfModel MEMBER packages NOTIFY modelChanged)

            public:
            explicit LNF(QObject* parent = nullptr);
            ~LNF();
            
            void setTheme(QString theme);
            
            signals:
            void indexChanged();
            void modelChanged();
    
            public:
            kcm::Plugin* plugin;
            QList<QObject*> packages;
            
            qint32 currentIndex;
            qint32 index;
    
        };
    }
}

#endif