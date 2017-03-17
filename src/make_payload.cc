#include "timetable.h"

MsgPack make_payload(std::vector<Visit> visits) {
  MsgPack payload;
  payload.pack_array(visits.size());
  for(auto v : visits) { payload.pack(v); }
  return payload;
}
