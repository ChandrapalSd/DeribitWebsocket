#include "App.hpp"
#include "config.hpp"
#include "models.hpp"

#include "test_root_certificates.hpp"

namespace dw {

	App::App()
		:cli(api_url)
	{
		cli.enable_server_certificate_verification(true);
	}

	bool App::run()
	{
		/*connect();
		getCurrencies();*/
		//testws();
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


	/*
	std::expected<WS, std::string> App::openWSConnection()
	{
		try
		{

			std::string host = "test.deribit.com";
			auto const  port = "443";


			// The io_context is required for all I/O
			net::io_context ioc;

			// The SSL context is required, and holds certificates
			ssl::context ctx{ ssl::context::tlsv12_client };

			// This holds the root certificate used for verification
			load_root_certificates(ctx);

			// These objects perform our I/O
			tcp::resolver resolver{ ioc };
			WS ws{ ioc, ctx };

			// Look up the domain name
			auto const results = resolver.resolve(host, port);

			// Make the connection on the IP address we get from a lookup
			auto ep = net::connect(beast::get_lowest_layer(ws), results);

			// Set SNI Hostname (many hosts need this to handshake successfully)
			if (!SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str()))
				throw beast::system_error(
					beast::error_code(
						static_cast<int>(::ERR_get_error()),
						net::error::get_ssl_category()),
					"Failed to set SNI Hostname");

			// Update the host_ string. This will provide the value of the
			// Host HTTP header during the WebSocket handshake.
			// See https://tools.ietf.org/html/rfc7230#section-5.4
			host += ':' + std::to_string(ep.port());

			// Perform the SSL handshake
			ws.next_layer().handshake(ssl::stream_base::client);

			// Set a decorator to change the User-Agent of the handshake
			ws.set_option(websocket::stream_base::decorator(
				[](websocket::request_type& req)
				{
					req.set(http::field::user_agent,
					std::string(BOOST_BEAST_VERSION_STRING) +
					" websocket-client-coro");
				}));

			// Perform the websocket handshake
			ws.handshake(host, "/ws/api/v2");
			return (ws);
		}
		catch (std::exception const& e)
		{
			return std::unexpected(e.what());
		}
	}




	int App::test() {
		auto wse = openWSConnection();
		if (!wse) {
			std::cout << "ERROR: " << wse.error() << std::endl;
			return 0;
		}

		auto ws = std::move(wse.value());

		auto const  text =
			R"({
  "method": "public/subscribe",
  "params": {
    "channels": [
      "deribit_price_index.ada_usd"
    ]
  },
  "jsonrpc": "2.0",
  "id": 0
})";
		// Send the message
		ws->write(net::buffer(std::string(text)));
		// This buffer will hold the incoming message
		beast::flat_buffer buffer;

		while (true) {
			// Read a message into our buffer
			ws->read(buffer);
			// The make_printable() function helps print a ConstBufferSequence
			std::cout << beast::make_printable(buffer.data()) << "\n\n\n\n" << std::endl;
			buffer.clear();
		}

		
		// Close the WebSocket connection
		ws->close(websocket::close_code::normal);

		// If we get here then the connection is closed gracefully
		

		return 1;
	}
	*/



}