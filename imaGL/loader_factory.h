#pragma once
#include "public/imaGL/imaGL.h"
#include "loader.h"
#include "loader_png.h"
#include "loader_jpeg.h"
#include <map>
#include <set>

namespace imaGL {

  //Special loader when type is unknown
  class CLoaderUnknown : public ILoader
  {
  public:
    SPrivateImaGLData load(std::istream& is) override;
  };

  //The factory (as singleton)
  class CLoaderFactory
  {
    friend class CLoaderUnknown;
    CLoaderUnknown m_unknown;
#ifdef _HAS_PNG
    CLoaderPNG m_png;
#endif // _HAS_PNG
#ifdef _HAS_JPEG
    CLoaderJPEG m_jpeg;
#endif // _HAS_JPEG

    //associative map between ff and loaders
    ::std::map<CFileFormat, ILoader*> m_mapLoaders;
    //set of all loaders (ensuring they are unique in this container)
    ::std::set<ILoader*> m_setLoaders;

  private:
    //Singleton definition
    static CLoaderFactory& getInstance() {
      static CLoaderFactory f;
      return f;
    }
    CLoaderFactory();

  public:
    CLoaderFactory(const CLoaderFactory&) = delete;
    CLoaderFactory& operator=(const CLoaderFactory&) = delete;

    //only public static members
  public:
    static ILoader& getLoader(CFileFormat ff);
  };


}