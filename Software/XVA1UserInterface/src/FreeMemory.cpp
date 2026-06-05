//
// Created by André Mathlener on 16/04/2021.
//

#include "FreeMemory.h"

#include <Esp.h>

uint32_t freeMemory() {
    return ESP.getFreeHeap();
}