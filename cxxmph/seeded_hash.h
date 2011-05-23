#ifndef __CXXMPH_SEEDED_HASH_H__
#define __CXXMPH_SEEDED_HASH_H__

#include <stdint.h>  // for uint32_t and friends

#include <cstdlib>
#include <unordered_map>  // for std::hash

#include "MurmurHash2.h"
#include "stringpiece.h"

namespace cxxmph {

template <class HashFcn>
struct seeded_hash_function {
  template <class Key>
  uint32_t operator()(const Key& k, uint32_t seed) const {
    return HashFcn()(k) ^ seed;
  }
};

struct Murmur2 {
  template<class Key>
  uint32_t operator()(const Key& k) const {
    return MurmurHash2(k, sizeof(Key), 1 /* seed */);
  }
};
struct Murmur2StringPiece {
  template <class Key>
  uint32_t operator()(const Key& k) const {
    StringPiece s(k);
    return MurmurHash2(s.data(), s.length(), 1 /* seed */);
  }
};

template <>
struct seeded_hash_function<Murmur2> {
  template <class Key>
  uint32_t operator()(const Key& k, uint32_t seed) const {
    return MurmurHash2(reinterpret_cast<const void*>(&k), sizeof(Key), seed);
  }
};

template <>
struct seeded_hash_function<Murmur2StringPiece> {
  template <class Key>
  uint32_t operator()(const Key& k, uint32_t seed) const {
    StringPiece s(k);
    return MurmurHash2(s.data(), s.length(), seed);
  }
};

template <class HashFcn> struct seeded_hash
{ typedef seeded_hash_function<HashFcn> hash_function; };
// Use Murmur2 instead for all types defined in std::hash, plus
// std::string which is commonly extended.
template <> struct seeded_hash<std::hash<char*> >
{ typedef seeded_hash_function<Murmur2StringPiece> hash_function; };
template <> struct seeded_hash<std::hash<const char*> >
{ typedef seeded_hash_function<Murmur2StringPiece> hash_function; };
template <> struct seeded_hash<std::hash<std::string> >
{ typedef seeded_hash_function<Murmur2StringPiece> hash_function; };

template <> struct seeded_hash<std::hash<char> >
{ typedef seeded_hash_function<Murmur2> hash_function; };
template <> struct seeded_hash<std::hash<unsigned char> >
{ typedef seeded_hash_function<Murmur2> hash_function; };
template <> struct seeded_hash<std::hash<short> >
{ typedef seeded_hash_function<Murmur2> hash_function; };
template <> struct seeded_hash<std::hash<unsigned short> >
{ typedef seeded_hash_function<Murmur2> hash_function; };
template <> struct seeded_hash<std::hash<int> >
{ typedef seeded_hash_function<Murmur2> hash_function; };
template <> struct seeded_hash<std::hash<unsigned int> >
{ typedef seeded_hash_function<Murmur2> hash_function; };
template <> struct seeded_hash<std::hash<long> >
{ typedef seeded_hash_function<Murmur2> hash_function; };
template <> struct seeded_hash<std::hash<unsigned long> >
{ typedef seeded_hash_function<Murmur2> hash_function; };
template <> struct seeded_hash<std::hash<long long> >
{ typedef seeded_hash_function<Murmur2> hash_function; };
template <> struct seeded_hash<std::hash<unsigned long long> >
{ typedef seeded_hash_function<Murmur2> hash_function; };

}  // namespace cxxmph

#endif  // __CXXMPH_SEEDED_HASH_H__