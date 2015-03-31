#include "gui_resources.h"

#include <qglobal.h>

void initContribResources()
{
  Q_INIT_RESOURCE(images);
}

void cleanupContribResources()
{
  Q_CLEANUP_RESOURCE(images);
}

namespace gui_resources
{

  void init()
  {
    initContribResources();
  }

  void cleanUp()
  {
    cleanupContribResources();
  }
}
