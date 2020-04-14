#ifndef LUX_RESOURCES_H
#define LUX_RESOURCES_H

#include "LuxStorage.h"
#include "LuxAsset.h"

void Resources_Init(void);
#ifdef _DEBUG
void Resources_Finalize(void);
#endif
void Resources_AddStorage(Storage *storage);
Asset *Resources_Reference(word id);
void Resources_Unreference(word id);
void Resources_Optimize(void);

#endif
