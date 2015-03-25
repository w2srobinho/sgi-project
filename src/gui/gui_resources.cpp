#include "gui_resources.h"

#include <qglobal.h>

void initContribResources()
{
   // must be on global namespace
   Q_INIT_RESOURCE(images);
}

void cleanupContribResources()
{
   // must be on global namespace
   Q_CLEANUP_RESOURCE(images);
}

namespace gui_resources
{

void Init()
{
   initContribResources();
}

void CleanUp()
{
   cleanupContribResources();
}

}
