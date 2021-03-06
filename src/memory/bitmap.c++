#include "bitmap.h"
#include "../zft_memory.h"



#define BYTE_BITS_COUNT 8



Bitmap::Bitmap(size_t size) {
    if (size == 0) {
        map = nullptr;
    }
    if (size % BYTE_BITS_COUNT != 0) {
        bitmapLength = size / BYTE_BITS_COUNT;
    }
    else {
        bitmapLength = size / BYTE_BITS_COUNT + 1;
    }
    map = new byte_t[bitmapLength];
    memzero((void*) map, bitmapLength);
}



bool Bitmap::get(size_t pos) {
    return (bool) (map[pos / BYTE_BITS_COUNT] & (0x1 << (pos % BYTE_BITS_COUNT)));
}



void Bitmap::set(size_t pos) {
    map[pos / BYTE_BITS_COUNT] |= (0x1 << (pos % BYTE_BITS_COUNT));
}



void Bitmap::reset(size_t pos) {
    if (get(pos)) {
        map[pos / BYTE_BITS_COUNT] ^= (0x1 << (pos % BYTE_BITS_COUNT));
    }
}



void Bitmap::setval(size_t pos, bool value) {
    if (value) {
        set(pos);
    }
    else {
        bool exValue = get(pos);
        if (exValue) {
            map[pos / BYTE_BITS_COUNT] ^= (0x1 << (pos % BYTE_BITS_COUNT));
        }
    }
}



Bitmap::~Bitmap() {
    if (map) {
        delete map;
    }
}



uint32_t Bitmap::firstZero() {
    byte_ptr_t tempMap = map;
    for (size_t i = 0; i < bitmapLength; ++i) {
        if (*tempMap != 0xFF) {
            for (size_t j = 0; j < BYTE_BITS_COUNT; ++j) {
                byte_t testbit = (byte_t) (0x1 << j);
                if (!(*tempMap & testbit)) {
                    return (uint32_t) (i * 8 + j);
                }
            }
        }
        tempMap++;
    }
    return (uint32_t)-1;
}
