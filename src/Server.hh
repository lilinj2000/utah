// Copyright (c) 2010
// All rights reserved.

#ifndef UTAH_SERVER_HH
#define UTAH_SERVER_HH

#include <map>
#include <string>
#include "ufo/Service.hh"
#include "Config.hh"
#include "air/TimeStampDataFile.hh"

namespace utah {

typedef std::map<int, air::TimeStampData*> TimeStampRecords;

class Server :
      public ufo::ServiceCallback {
 public:
  Server(Options* options,
         soil::Options* ufo_options);

  virtual ~Server();

  virtual void onAnsOrderInsert(int64_t order_ref);

  virtual void onRspOrderInsert(int64_t order_ref);

  virtual void onOrderRtn(int64_t order_ref);

  virtual void onTradeRtn(int64_t order_ref);

  virtual void onRspError(int64_t order_ref);

  void run();

  void updateT1(int64_t order_ref);

  void updateT2(int64_t order_ref);

 private:
  Options* options_;
  std::unique_ptr<ufo::Service> service_;
  TimeStampRecords records_;
  std::unique_ptr<air::TimeStampDataFile> timestamp_file_;
};

}  // namespace utah

#endif
