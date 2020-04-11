#ifndef LUX_RESOURCES_H
#define LUX_RESOURCES_H

#include "LuxStorage.h"

void Resources_AddStorage(Storage *storage);
void *Resources_Load(word id);
void Resources_Optimize(void);

#endif
