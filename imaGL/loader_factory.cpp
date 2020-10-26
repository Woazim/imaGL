#include "loader_factory.h"
#include "privateimagldata.h"

namespace ImaGL {

  CLoaderFactory::CLoaderFactory()
  {
#ifdef _HAS_LIBPNG
    m_mapLoaders["PNG "] = &m_png;
    m_setLoaders.insert(&m_png);
#endif
  }

  ILoader& CLoaderFactory::getLoader(CFileFormat ff)
  {
    auto it = getInstance().m_mapLoaders.find(ff);
    if (it != getInstance().m_mapLoaders.end())
      return *(it->second);
    throw loader_not_found(ff);
  }

  SPrivateImaGLData CLoaderUnknown::load(std::istream& is)
  {
    for (auto loader : CLoaderFactory::getInstance().m_setLoaders)
    {
      try
      {
        return loader->load(is);
      }
      catch (const bad_format&)
      {
      }
    }
    //If program is here, no compatible loader has been found
    throw compatible_loader_not_found();
  }

}