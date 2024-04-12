#ifndef SwaggerComponent_hpp
#define SwaggerComponent_hpp

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/core/macro/component.hpp"

class SwaggerComponent {
public:
  
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swagger_documentInfo)([] {
        oatpp::swagger::DocumentInfo::Builder builder;

        builder
            .setTitle("NTEC test")
            .setDescription("CRUD API NTEC test project")
            .setContactName("Denis Fomichevskiy")
            .addServer("http://localhost:8000", "server on localhost");

        return builder.build();
    }());
  
  
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swagger_resources)([] {
        return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
    }());
  
};

#endif
