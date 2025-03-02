#include "dm_graphicsviewsynchronizedgroup.h"

DM_GraphicsViewSynchronizedGroup::DM_GraphicsViewSynchronizedGroup() : DM_AbstractViewSynchronizedGroup()
{
}

void DM_GraphicsViewSynchronizedGroup::setOptions(const DM_GraphicsViewSynchronizedGroupOptions &newOptions)
{
    _options = newOptions;
}

void DM_GraphicsViewSynchronizedGroup::addGraphicsView(DM_GraphicsView *gw)
{
    if(!_gwList.isEmpty())
    {
        gw->getCamera()->syncWithCamera(_gwList.first()->getCamera());
        gw->setOptions(((const DM_GraphicsView*)_gwList.first())->constGetOptionsInternal());
    }

    connect(gw->getCamera(), SIGNAL(coordinatesChanged()), this, SLOT(syncCamera()));
    connect((DM_GraphicsViewOptions*)&(gw->constGetOptionsInternal()), SIGNAL(optionsChanged()), this, SLOT(syncOptions()));

    _gwList.append(gw);
}

void DM_GraphicsViewSynchronizedGroup::removeGraphicsView(DM_GraphicsView *gw)
{
    if(gw != nullptr)
    {
        disconnect(gw->getCamera(), nullptr, this, nullptr);
        disconnect((DM_GraphicsViewOptions*)&(gw->constGetOptionsInternal()), nullptr, this, nullptr);

        _gwList.removeOne(gw);
    }
}

void DM_GraphicsViewSynchronizedGroup::setCameraPointOfViewForAll(const DM_GraphicsViewCamera *cam)
{
    if(_options.mustSyncGraphicsViewCamera()
            && (cam != nullptr))
    {
        QListIterator<DM_GraphicsView*> it(_gwList);

        while(it.hasNext())
        {
            DM_GraphicsView *gw = it.next();

            if(gw->getCamera() != cam)
            {
                gw->getCamera()->syncWithCamera(cam);
            }
        }
    }
}

void DM_GraphicsViewSynchronizedGroup::setGraphicsViewOptionsForAll(DM_GraphicsViewOptions *newOptions)
{
    if(_options.mustSyncGraphicsViewOptions()
            && (newOptions != nullptr))
    {
        QListIterator<DM_GraphicsView*> it(_gwList);

        while(it.hasNext())
        {
            DM_GraphicsView *gw = it.next();

            if(&(gw->constGetOptionsInternal()) != newOptions)
                gw->setOptions(*newOptions);
        }
    }
}

void DM_GraphicsViewSynchronizedGroup::syncCamera()
{
    setCameraPointOfViewForAll((const DM_GraphicsViewCamera*)sender());
}

void DM_GraphicsViewSynchronizedGroup::syncOptions()
{
    setGraphicsViewOptionsForAll((DM_GraphicsViewOptions*)sender());
}
