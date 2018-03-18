#ifndef AQUA_SERIALIZABLE
#define AQUA_SERIALIZABLE

#include <iostream>
#include <vector>
#include <map>
#include <string>

namespace aqua {

struct Serializable {
  virtual void Serialize(std::ostream& os) const {}
  virtual void Unserialize(std::istream& is) {}
};

}  // namespace aqua

inline std::istream& operator >> (std::istream& is, aqua::Serializable& value) {
  std::string trash;
  is >> trash;            // "{"
  value.Unserialize(is);
  is >> trash;            // "}"
  return is;
}

template <class T>
inline std::istream& operator >> (std::istream& is, std::vector<T>& list) {
  std::string trash;
  is >> trash;      // "["
  int number = 0;
  T value;
  is >> number;
  for (int i = 0; i < number; ++i) {
    is >> value;
    list.push_back(value);
  }
  is >> trash;      // "]"
  return is;
}

template <class K, class T>
inline std::istream& operator >> (std::istream& is, std::map<K, T>& map) {
  std::string trash;
  is >> trash;      // "<"
  int number = 0;
  K key;
  T value;
  is >> number;
  for (int i = 0; i < number; ++i) {
    is >> key;
    is >> value;
    map[key] = value;
  }
  is >> trash;      // ">"
  return is;
}

inline std::ostream& operator << (std::ostream& os,
			   const aqua::Serializable& value) {
  os << " { ";
  value.Serialize(os);
  os << " } ";
  return os;
}

template <class T>
inline std::ostream& operator << (std::ostream& os, const std::vector<T>& list) {
  os << " [ ";
  os << list.size() << " ";
  for (auto item : list) os << item << " ";
  os << " ] ";
  return os;
}

template <class K, class T>
inline std::ostream& operator << (std::ostream& os, const std::map<K, T>& map) {
  os << " < ";
  os << map.size() << " ";
  for (auto pair : map) os << pair.first << " " << pair.second << " ";
  os << " > ";
  return os;
}

#endif // AQUA_SERIALIZABLE
