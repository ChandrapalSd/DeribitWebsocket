#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <string>
#include <ctype.h>
#include <expected>
#include <memory>
#include <cstdlib>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/strand.hpp>
#include "test_root_certificates.hpp"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
