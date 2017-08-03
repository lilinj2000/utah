// Copyright (c) 2010
// All rights reserved.

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

#include "Config.hh"
#include "Log.hh"
#include "ufo/Service.hh"

namespace utah {

Options::Options():
    config_options_("UtahConfigOptions") {
  namespace po = boost::program_options;

  config_options_.add_options()
      ("utah.instrument_id", po::value<std::string>(&instrument_id),
       "instrument id")
      ("utah.price", po::value<double>(&price),
       "price")
      ("utah.volume", po::value<int>(&volume),
       "volume")
      ("utah.is_buy", po::value<bool>(&is_buy),
       "is buy")
      ("utah.order_counter", po::value<int>(&order_counter),
       "order counter")
      ("utah.order_interval", po::value<int>(&order_interval),
       "order interval")
      ("utah.log_cfg", po::value<std::string>(&log_cfg),
       "log config file")

      ("utah.timestamp_file", po::value<std::string>(&timestamp_file),
       "timestamp file");

  return;
}

Options::~Options() {
}

po::options_description* Options::configOptions() {
  return &config_options_;
}

Config::Config(int argc, char* argv[]) {
  options_.reset(new Options());
  ufo_options_.reset(
      ufo::Service::createOptions());

  std::unique_ptr<soil::Config> config(soil::Config::create());
  config->registerOptions(options_.get());
  config->registerOptions(ufo_options_.get());

  config->configFile() = "utah.cfg";
  config->loadConfig(argc, argv);

  // init the log
  UTAH_LOG_INIT(options_->log_cfg);

  return;
}

Config::~Config() {
}

}  // namespace utah
