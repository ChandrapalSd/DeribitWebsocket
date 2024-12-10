#pragma once
#include <httplib.h>
#include <expected>
#include <string>
#include "Models.hpp"

namespace dw {

	class App
	{
	public:
		App();
		~App() = default;
		bool run();

	private:
		bool connect();
		bool getCurrencies();
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
	private:
		bool started = false;
		httplib::SSLClient cli;
		model::AuthRes authRes;
		model::CurrenciesRes currencies;
	};

}