#include "config_loader.hpp"

using namespace sdk::config;

static std::string extension(const std::string& path) {
  auto pos = path.rfind('.');
  return pos==std::string::npos ? "" : path.substr(pos+1);
}

ConfigMap ConfigLoader::load(const std::string& path) {
  std::ifstream in{path};
  if(!in.is_open()) throw std::runtime_error("Cannot open config file: "+path);

  ConfigMap out;
  auto ext = extension(path);
  if(ext == "json") {
      nlohmann::json j;
      try {
          in >> j;
      } catch(const std::exception& e) {
          throw std::runtime_error(std::string("JSON parse error: ") + e.what());
      }
      if(!j.is_object()) throw std::runtime_error("JSON root not an object");
      for(auto& [k,v] : j.items()) {
          if(v.is_number_integer())    out[k] = v.get<int>();
          else if(v.is_boolean())      out[k] = v.get<bool>();
          else if(v.is_string())       out[k] = v.get<std::string>();
          else                         throw std::runtime_error("Unsupported JSON value type for key "+k);
      }
  }
  return out;
}
  }
  else if(ext == "yaml" || ext == "yml") {
    YAML::Node doc = YAML::Load(in);
    if(!doc.IsMap()) throw std::runtime_error("YAML root not a map");
    for(auto it : doc) {
      const auto& key = it.first.as<std::string>();
      auto node = it.second;
      if(node.IsScalar()) {
        // try int, bool, then string
        try {
          out[key] = node.as<int>();
        } catch(...) {
          std::string s = node.as<std::string>();
          if(s == "true" || s == "false")
            out[key] = (s=="true");
          else
            out[key] = s;
        }
      }
      else {
        throw std::runtime_error("Unsupported YAML value for key "+key);
      }
    }
  }
  else {
    throw std::runtime_error("Unknown config file extension: "+ext);
  }

  return out;
}
