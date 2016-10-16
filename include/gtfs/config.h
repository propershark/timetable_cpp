#include "modern_sqlite.h"

#include "gtfs/decls.h"


namespace GTFS {
  sqlite::database* db;

  void use_db(std::string db_name) {
    db = new sqlite::database(db_name);
  }

  void close_db() {
    delete db;
  }


  inline sqlite::database& current_db() { return *db; }
}
