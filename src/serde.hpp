#ifndef SERDE_HPP
#define SERDE_HPP

#include <string>
#include <cstdio>
#include <stdint.h>

class Serializer{
public:
    FILE* file;

    Serializer();
    void open(const char* file_name);
    void close();
    int write(uint8_t x);
#define serialize_primitive(type) void serialize(type t);
    serialize_primitive(char)
    serialize_primitive(int8_t)
    serialize_primitive(uint8_t)
    serialize_primitive(int16_t)
    serialize_primitive(uint16_t)
    serialize_primitive(int32_t)
    serialize_primitive(uint32_t)
    serialize_primitive(int64_t)
    serialize_primitive(uint64_t)
#undef serialize_primitive
    void serialize(std::string s);
    void serialize(timeval t);
};

class Deserializer{
public:
    FILE *file;
    Deserializer();
    void open(const char* file_name);
    void close();
    uint8_t read();
#define deserialize_primitive(type) void deserialize(type &t);
    deserialize_primitive(char)
    deserialize_primitive(int8_t)
    deserialize_primitive(uint8_t)
    deserialize_primitive(int16_t)
    deserialize_primitive(uint16_t)
    deserialize_primitive(int32_t)
    deserialize_primitive(uint32_t)
    deserialize_primitive(int64_t)
    deserialize_primitive(uint64_t)
#undef deserialize_primitive
    void deserialize(std::string &s);
    void deserialize(timeval &t);
};

#endif /* SERDE_HPP */
