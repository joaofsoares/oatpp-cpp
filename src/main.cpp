#include <iostream>

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

class Health : public oatpp::web::server::HttpRequestHandler {
public:
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest> &request) override {
      return ResponseFactory::createResponse(Status::CODE_200, "OK");
    }
};

class Hello : public oatpp::web::server::HttpRequestHandler {
public:
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest> &request) override {
      return ResponseFactory::createResponse(Status::CODE_200, "Hello from Oatpp Cpp!");
    }
};

void start_server() {
  auto router{oatpp::web::server::HttpRouter::createShared()};

  router->route("GET", "/", std::make_shared<Health>());

  router->route("GET", "/hello", std::make_shared<Hello>());

  auto connectionHandler{oatpp::web::server::HttpConnectionHandler::createShared(router)};

  auto connectionProvider{
      oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8000, oatpp::network::Address::IP_4})
  };

  oatpp::network::Server server(connectionProvider, connectionHandler);

  OATPP_LOGI("OatppCpp", "Server running on port %s", connectionProvider->getProperty("port").getData());

  server.run();
}

int main() {
  oatpp::base::Environment::init();

  start_server();

  oatpp::base::Environment::destroy();

  return 0;
}
