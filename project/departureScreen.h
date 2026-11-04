#pragma once

#include <vector>
#include <memory>
#include <lvgl.h>
#include <cstdio>

#include "Transport/transport.h"

// Create the departure screen UI
void create_departure_screen(lv_obj_t* departureTile);

// Update the departure table
void update_departure_screen(
    const std::vector<std::shared_ptr<Transport>>& transports
);