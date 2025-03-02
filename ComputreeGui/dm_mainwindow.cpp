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

#include "dm_mainwindow.h"

#include "cdm_scriptmanagerxmlallversions.h"
#include "cdm_configfile.h"

#include "ct_global/ct_context.h"

DM_MainWindow::DM_MainWindow()
{
    _pluginManager = new CDM_PluginManager();
    _scriptManager = new CDM_ScriptManagerXMLAllVersions(*_pluginManager);
    _stepManager = new CDM_StepManager(_scriptManager, &m_actionsManager);

    _ioParser = new CDM_StdIOParser(*_scriptManager, *_stepManager, *_pluginManager);

    _ioListener = new CDM_StdIOListener();
    _ioListener->setParser(_ioParser);

    _ioParser = nullptr;
    _ioListener = nullptr;

    m_actionsManager.setPluginManager(_pluginManager);
    m_actionsManager.setStepManager(_stepManager);
}

DM_MainWindow::~DM_MainWindow()
{
    delete _ioListener;
    delete _ioParser;

    delete _stepManager;
    delete _scriptManager;
    delete _pluginManager;

    delete CONFIG_FILE;
    //delete PS_CONTEXT;
}

CDM_PluginManager* DM_MainWindow::getPluginManager() const
{
    return _pluginManager;
}

CDM_ScriptManagerAbstract* DM_MainWindow::getScriptManager() const
{
    return _scriptManager;
}

CDM_StepManager* DM_MainWindow::getStepManager() const
{
    return _stepManager;
}

ActionsManagerInterface* DM_MainWindow::actionsManager() const
{
    return getActionsManager();
}

DM_ActionsManager* DM_MainWindow::getActionsManager() const
{
    return (DM_ActionsManager*)&m_actionsManager;
}
