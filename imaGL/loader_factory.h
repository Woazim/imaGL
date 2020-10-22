#pragma once
#include "loader.h"
#include "loader_png.h"
#include <map>
#include <set>

#define IMAGL_MAKE_SIG(typeSig) \
  (*reinterpret_cast<const uint32_t*>(typeSig))

namespace ImaGL {

  uint32_t MakeSig(const char typeSig[5]) {
    return *reinterpret_cast<const uint32_t*>(typeSig);
  }

  class loader_not_found : public ::std::runtime_error {
  public:
    loader_not_found(uint32_t typeSig) :
      ::std::runtime_error("Loader for type " + std::string(reinterpret_cast<const char*>(&typeSig)) + " not found!")
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
#ifdef _HAS_LIBPNG
    CLoaderPNG m_png;
#endif // _HAS_LIBPNG

    //associative map between typeSig and loaders
    ::std::map<uint32_t, ILoader*> m_mapLoaders;
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
    static ILoader& getLoader(uint32_t typeSig);
  };


}