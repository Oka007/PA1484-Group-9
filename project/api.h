#pragma once

#include <vector>
#include "Transport/transport.h"
#include <string>
#include <cstdio>

JsonDocument getApiData(std::string loc_id);
Time parseTime(const char* timestamp);

using TransportList = std::vector<std::shared_ptr<Transport>>;

TransportList readDepartures(const JsonDocument& json);

JsonDocument getJourneys(String fromId, String toId);
