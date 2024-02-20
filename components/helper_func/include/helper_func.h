#ifndef __HELPER_FUNC_H__
#define __HELPER_FUNC_H__
#include "stdint-gcc.h"

// const char *signedCharToString(signed char value);

#ifdef __cplusplus
extern "C"
{
#endif
    char *u8cpy(uint8_t *dst, const uint8_t *src);
    unsigned char *convertToUnsignedCharBuffer(const char *charArray, size_t size);
    const char *unsignedCharToString(unsigned char value);
    const char *signedCharToString(signed char value);
    const char *intToString(int value);
    const char *unsignedShortToString(unsigned short value);
    const char *charArrayToString(char *array, int size);
    uint32_t toLittleEndian(uint32_t value);
    int charArrayToInt(const char array[]);
    unsigned char convertStringToUnsignedChar(const char *str);
#ifdef __cplusplus
}
#endif
#endif
