#pragma once
#include <httplib.h>
#include <expected>
#include <string>
#include "Models.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>

namespace dw {

	namespace beast = boost::beast;         // from <boost/beast.hpp>
	namespace http = beast::http;           // from <boost/beast/http.hpp>
	namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
	namespace net = boost::asio;            // from <boost/asio.hpp>
	using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
	namespace ssl = boost::asio::ssl; // from <boost/asio/ssl.hpp>
	using WS = websocket::stream<ssl::stream<tcp::socket>>;

	class App
	{
	public:
		App();
		~App() = default;
		bool run();
		int testws();
	private:
		bool connect();
		bool getCurrencies();
#pragma region post
		template <typename Req, typename Res>
		std::expected<Res, std::string> post(httplib::Headers headers, Req& req)
		{
			std::string path = basePath + req.method;
			nlohmann::json jsonBody = req;
			std::string body = jsonBody.dump();

			httplib::Result result = cli.Post(path, headers, body.c_str(), body.length(), "application/json");
			if (!result) {
				return std::unexpected(to_string(result.error()));
			}

			const httplib::Response res = result.value();
			nlohmann::json resBody = nlohmann::json::parse(res.body);
			return resBody.get<Res>();
		}
#pragma endregion post

	private:
		bool started = false;
		httplib::SSLClient cli;
		model::AuthRes authRes;
		model::CurrenciesRes currencies;
	};

}