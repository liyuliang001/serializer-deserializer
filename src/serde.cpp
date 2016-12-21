#include "serde.hpp"

/* Serializer */
Serializer::Serializer(){
    file = NULL;
}
    
void Serializer::open(const char* file_name){
    file = fopen(file_name, "w");
}

void Serializer::close(){
    fclose(file);
}

inline int Serializer::write(uint8_t x){
    fputc(x, file);
}

#define serialize_primitive(type) \
void Serializer::serialize(type t){ \
    for (int i = 0; i < sizeof(type); i++)\
        write(((uint8_t*)&t)[i]);\
}

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
/*
inline void Serializer::serialize(uint32_t t){
    for (int i = 0; i < sizeof(t); i++)\
        write(((uint8_t*)&t)[i]);\
}
*/

void Serializer::serialize(std::string s){
    serialize(s.size());
    for (int i = 0; i < s.size(); i++)
        write(s[i]);
}

void Serializer::serialize(timeval t){
    serialize(t.tv_sec);
    serialize(t.tv_usec);
}

/* Deserializer */
Deserializer::Deserializer(){
    file = NULL;
}

void Deserializer::open(const char* file_name){
    file = fopen(file_name, "r");
}

void Deserializer::close(){
    fclose(file);
}

inline uint8_t Deserializer::read(){
    return fgetc(file);
}

#define deserialize_primitive(type) \
void Deserializer::deserialize(type &t){ \
    for (int i = 0; i < sizeof(type); i++)\
        ((uint8_t*)&t)[i] = read();\
}

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

void Deserializer::deserialize(std::string &s){
    size_t size;
    deserialize(size);
    s.resize(size);
    for (int i = 0; i < size; i++)
        deserialize(s[i]);
}

void Deserializer::deserialize(timeval &t){
    deserialize(t.tv_sec);
    deserialize(t.tv_usec);
}
