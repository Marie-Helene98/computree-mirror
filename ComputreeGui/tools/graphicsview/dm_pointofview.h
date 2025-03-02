/****************************************************************************

 Copyright (C) 2010-2012 the Office National des Forêts (ONF), France
                     and the Association de Recherche Technologie et Sciences (ARTS), Ecole Nationale Suprieure d'Arts et Métiers (ENSAM), Cluny, France.
                     All rights reserved.

 Contact : alexandre.piboule@onf.fr

 Developers : MichaÃ«l KREBS (ARTS/ENSAM)

 This file is part of Computree version 2.0.

 Computree is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Computree is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Computree.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************/


#ifndef DM_POINTOFVIEW_H
#define DM_POINTOFVIEW_H

#include <QString>

class DM_PointOfView
{
public:
    DM_PointOfView();
    DM_PointOfView(QString name,
                   double cx, double cy, double cz,
                   double px, double py, double pz,
                   double q0, double q1, double q2, double q3);
    //DM_PointOfView(const DM_PointOfView &) = default;

    inline QString name() const { return _name; }
    inline double cx() const { return _cx; }
    inline double cy() const { return _cy; }
    inline double cz() const { return _cz; }
    inline double px() const { return _px; }
    inline double py() const { return _py; }
    inline double pz() const { return _pz; }
    inline double q0() const { return _q0; }
    inline double q1() const { return _q1; }
    inline double q2() const { return _q2; }
    inline double q3() const { return _q3; }

    double distanceFromSceneCenter() const;

    QString toString() const;
    QString toSaveString() const;
    static DM_PointOfView loadFromString(QString saveString, bool &ok);

    bool operator==(const DM_PointOfView &other) const;

private:

    QString _name;
    double _cx;
    double _cy;
    double _cz;
    double _px;
    double _py;
    double _pz;
    double _q0;
    double _q1;
    double _q2;
    double _q3;
};

#endif // DM_POINTOFVIEW_H
