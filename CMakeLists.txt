cmake_minimum_required(VERSION 3.25.0)
project(DeribitWebsocket VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(include)
	
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.hpp)

set(BUILD_SHARED_LIBS OFF)

#define target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

#pch
target_precompile_headers(${PROJECT_NAME} PRIVATE include/pch.hpp)

#dependencies
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Crow CONFIG REQUIRED)
find_package(httplib CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

set(HTTPLIB_IS_USING_OPENSSL TRUE)

target_link_libraries(${PROJECT_NAME} PUBLIC Crow::Crow nlohmann_json::nlohmann_json httplib::httplib $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::SSL>
        $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::Crypto>)
#target_link_libraries(${PROJECT_NAME} PRIVATE Crow::Crow asio::asio)								   

target_compile_definitions(${PROJECT_NAME} PUBLIC
        $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:CPPHTTPLIB_OPENSSL_SUPPORT>
        )
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
