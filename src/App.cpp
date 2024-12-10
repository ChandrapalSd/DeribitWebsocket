#include "App.hpp"
#include "config.hpp"
#include "models.hpp"

namespace dw {

	App::App()
		:cli(api_url)
	{
		cli.enable_server_certificate_verification(true);
	}

	bool App::run()
	{
		connect();
		getCurrencies();
		return true;
	}

	/*
	bool App::connect()
	{
		httplib::Headers headers;
		//headers.insert("Content-Type", "application/json");

		model::AuthReq request;
		nlohmann::json jsonBody = request;
		std::string body = jsonBody.dump();
		std::string path = authPath;


		httplib::Result result = cli.Post(path, headers, body.c_str(), body.length(), "application/json");
		if (!result) {
			std::cerr << "Error authenticating \n";
			std::cerr << result.error();
			return false;
		}

		const httplib::Response res = result.value();
		nlohmann::json resBody = nlohmann::json::parse(res.body);
		authRes = resBody.get<dw::model::AuthRes>();
		std::cout << "Successfully authenticated !\n";
		return true;
	}
	*/

	bool App::connect()
	{
		httplib::Headers headers;
		model::AuthReq request;

		auto response = post<model::AuthReq, model::AuthRes>(headers, request);
		if (response) {
			authRes = response.value();
			std::cout << "Successfully authenticated !\n";
			return true;
		}

		std::cerr << "Error authenticating \n";
		std::cerr << response.error();
		return false;
	}

	bool App::getCurrencies()
	{
		httplib::Headers headers;
		model::CurrenciesReq request;

		auto response = post<model::CurrenciesReq, model::CurrenciesRes>(headers, request);
		if (response) {
			currencies = response.value();
		}
		else {
			std::cerr << response.error();
		}

		return response.has_value();
	}
}