#include "loader_factory.h"
#include "privateimagldata.h"

namespace ImaGL {

  CLoaderFactory::CLoaderFactory()
  {
#ifdef _HAS_LIBPNG
    m_mapLoaders[IMAGL_MAKE_SIG("PNG ")] = &m_png;
    m_setLoaders.insert(&m_png);
#endif
  }

  ILoader& CLoaderFactory::getLoader(uint32_t typeSig)
  {
    auto it = getInstance().m_mapLoaders.find(typeSig);
    if (it != getInstance().m_mapLoaders.end())
      return *(it->second);
    throw loader_not_found(typeSig);
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