cmake_minimum_required(VERSION 3.25.0)
project(DeribitWebsocket VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(include)
	
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.hpp)

set(BUILD_SHARED_LIBS OFF)

if (MSVC)
  add_compile_options(/bigobj)
else ()
  add_compile_options(-Wa,-mbig-obj)
endif ()

#define target
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})

#pch
target_precompile_headers(${PROJECT_NAME} PRIVATE include/pch.hpp)

#dependencies
find_package(nlohmann_json CONFIG REQUIRED)
find_package(httplib CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(boost_beast REQUIRED CONFIG)
find_package(wxWidgets REQUIRED COMPONENTS net core base)

set(HTTPLIB_IS_USING_OPENSSL TRUE)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    nlohmann_json::nlohmann_json 
    httplib::httplib 
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::SSL>
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::Crypto>
    Boost::beast
    ${wxWidgets_LIBRARIES}
)							   

target_compile_definitions(${PROJECT_NAME} PUBLIC
        $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:CPPHTTPLIB_OPENSSL_SUPPORT>
        )

 if (MSVC)
     target_compile_definitions(${PROJECT_NAME} PUBLIC UNICODE _UNICODE)
 endif()

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
