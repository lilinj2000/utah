// Copyright (c) 2010
// All rights reserved.

#include "Server.hh"
#include "Log.hh"
#include "soil/STimer.hh"

namespace utah {

Server::Server(Options* options,
               soil::Options* ufo_options) :
    options_(options) {
  UTAH_TRACE <<"Server::Server()";

  service_.reset(
      ufo::Service::createService(
          ufo_options,
          this));

  if (!options_->timestamp_file.empty() )
    timestamp_file_.reset(
        new air::TimeStampDataFile(
            options_->timestamp_file));
}

Server::~Server() {
  UTAH_TRACE <<"Server::~Server()";
}

void Server::onAnsOrderInsert(int64_t order_ref) {
  UTAH_TRACE <<"Server::onAnsOrderInsert()";

  UTAH_DEBUG <<"order_ref: " <<order_ref;

  updateT1(order_ref);
}

void Server::onRspOrderInsert(int64_t order_ref) {
  UTAH_TRACE <<"Server::onRspOrderInsert()";

  UTAH_DEBUG <<"order_ref is " <<order_ref;

  updateT2(order_ref);
}

void Server::onOrderRtn(int64_t order_ref) {
  UTAH_TRACE <<"Server::onOrderRtn()";

  UTAH_DEBUG <<"order_ref = " <<order_ref;
}

void Server::onTradeRtn(int64_t order_ref) {
  UTAH_TRACE <<"Server::onTradeRtn()";

  UTAH_DEBUG <<"order_ref = " <<order_ref;
}

void Server::onRspError(int64_t order_ref) {
  UTAH_TRACE <<"Server::onRspError()";

  UTAH_DEBUG <<"order_ref = " <<order_ref;

  updateT2(order_ref);
}

void Server::run() {
  UTAH_TRACE <<"Server::run()";

  int counter = 0;

  std::unique_ptr<soil::STimer> cond;
  cond.reset(soil::STimer::create());

  do {
    int64_t order_ref = -1;

    if (options_->is_buy) {
      order_ref = service_->orderOpenBuyFOK(
          options_->instrument_id,
          options_->price,
          options_->volume);
    } else {
      order_ref = service_->orderOpenSellFOK(
          options_->instrument_id,
          options_->price,
          options_->volume);
    }

    records_[order_ref] = new air::TimeStampData(order_ref);

    ++counter;

    if (options_->order_counter > 0
        && counter >= options_->order_counter)
      break;

    cond->wait(options_->order_interval);
  }while(true);

  cond->wait(1000);
}

void Server::updateT1(int64_t order_ref) {
  UTAH_TRACE <<"Server::updateT1()";

  auto it = records_.find(order_ref);
  if (it != records_.end()) {
    it->second->updateT1();
  }
}

void Server::updateT2(int64_t order_ref) {
  UTAH_TRACE <<"Server::updateT2()";

  auto it = records_.find(order_ref);
  if (it != records_.end()) {
    it->second->updateT2();

    timestamp_file_->putData(it->second);
    records_.erase(it);
  }
}

}  // namespace utah
