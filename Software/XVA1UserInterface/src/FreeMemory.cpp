//
// Created by André Mathlener on 16/04/2021.
//

#include <Esp.h>
#include "FreeMemory.h"

uint32_t freeMemory() {
    return ESP.getFreeHeap();
}