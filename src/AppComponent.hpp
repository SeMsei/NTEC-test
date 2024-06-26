﻿#ifndef APPCOMPONENT_HPP
#define APPCOMPONENT_HPP

#include "SwaggerComponent.hpp"
#include "DatabaseComponent.hpp"
#include "ErrorHandler.hpp"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"

class AppComponent {
public:
  
    SwaggerComponent swagger_component;
    DatabaseComponent database_component;

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, api_object_mapper)([] {
        auto object_mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
        object_mapper->getDeserializer()->getConfig()->allowUnknownFields = false;
        return object_mapper;
    }());
  
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, server_connection_provider)([] {
        return oatpp::network::tcp::server::ConnectionProvider::createShared({"0.0.0.0", 8000, oatpp::network::Address::IP_4});
    }());
  
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, http_router)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());
  
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, server_connection_handler)([] {

    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, object_mapper);

    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
    connectionHandler->setErrorHandler(std::make_shared<ErrorHandler>(object_mapper));
    return connectionHandler;

  }());

};

#endif
