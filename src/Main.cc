// Copyright (c) 2010
// All rights reserved.

#include <memory>
#include "Config.hh"
#include "Server.hh"

int main(int argc, char* argv[]) {
  std::unique_ptr<utah::Config> config;
  config.reset(new utah::Config(argc, argv));

  utah::Options* options = config->options();

  std::unique_ptr<utah::Server> server;
  server.reset(new utah::Server(options, config->ufoOptions()));

  server->run();

  return 0;
}
