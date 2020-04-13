#ifndef LUX_RESOURCES_H
#define LUX_RESOURCES_H

#include "LuxStorage.h"
#include "LuxAsset.h"

#define Texture2D 0x6a // String_GetHashCode8("Texture2D")

void Resources_Init(void);
#ifdef _DEBUG
void Resources_Finalize(void);
#endif
void Resources_AddStorage(Storage *storage);
Asset *Resources_Reference(word id);
void Resources_Unreference(word id);
void Resources_Optimize(void);

#endif
