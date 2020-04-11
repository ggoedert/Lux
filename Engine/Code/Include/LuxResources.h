#ifndef LUX_RESOURCES_H
#define LUX_RESOURCES_H

#include "LuxStorage.h"
#include "LuxSprite.h"

void Resources_Init(void);
#ifdef _DEBUG
void Resources_Finalize(void);
#endif
void Resources_AddStorage(Storage *storage);
void *Resources_Load(word id);
void Resources_Optimize(void);

#endif
