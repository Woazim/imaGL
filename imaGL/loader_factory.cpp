#include "loader_factory.h"
#include "privateimagldata.h"

namespace imaGL {

  CLoaderFactory::CLoaderFactory()
  {
    using namespace string_literals;
    m_mapLoaders["    "_FF] = &m_unknown;
#ifdef _HAS_PNG
    m_mapLoaders["PNG "_FF] = &m_png;
    m_setLoaders.insert(&m_png);
#endif
#ifdef _HAS_JPEG
    m_mapLoaders["JPEG"_FF] = &m_jpeg;
    m_mapLoaders["JPG "_FF] = &m_jpeg;
    m_setLoaders.insert(&m_jpeg);
#endif
  }

  ILoader& CLoaderFactory::getLoader(CFileFormat ff)
  {
    auto it = getInstance().m_mapLoaders.find(ff);
    if (it != getInstance().m_mapLoaders.end())
      return *(it->second);
    throw loader_not_found(ff);
  }

  CPrivateImaGLData CLoaderUnknown::load(std::istream& is)
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