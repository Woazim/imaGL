#pragma once
#include "imaGL.h"
#include "loader.h"
#include "loader_png.h"
#include <map>
#include <set>

namespace ImaGL {

  class loader_not_found : public ::std::runtime_error {
  public:
    loader_not_found(CFileFormat ff) :
      ::std::runtime_error("Loader for type " + static_cast<std::string>(ff) + " not found!")
    {}
  };

  class compatible_loader_not_found : public ::std::runtime_error {
  public:
    compatible_loader_not_found() :
      ::std::runtime_error("Compatbile loader has not been found!")
    {}
  };

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
#ifdef _HAS_PNG
    CLoaderPNG m_png;
#endif // _HAS_PNG

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