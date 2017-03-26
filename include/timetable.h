#pragma once

#include "datetime.h"
#include "gtfs.h"
#include "timetable/visit_list.h"
#include "timetable/bounds.h"
#include "timetable/calendar.h"
#include "timetable/index.h"
#include "timetable/timetable.h"
#include "visit.h"


extern Timetable::Timetable tt;


////
// Utilities
////
MsgPack make_payload(std::vector<Visit> visits);
void    create_indices();


////
// RPC definitions
////
MsgPack visits_before (std::string stop_code, std::string end, int count);
MsgPack visits_between(std::string stop_code, std::string start, std::string end, int count);
MsgPack visits_after  (std::string stop_code, std::string start, int count);

// These are temporary implementations until the WAMP client supports optional
// parameters in RPCs.
MsgPack visits_before_from_route  (std::string stop_code, std::string end, std::string route, int count);
MsgPack visits_between_from_route (std::string stop_code, std::string start, std::string end, std::string route, int count);
MsgPack visits_after_from_route   (std::string stop_code, std::string start, std::string route, int count);
