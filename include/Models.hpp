#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <ctype.h>
#include "config.hpp"

namespace dw::model {

	const std::string jsonRpcV = "2.0";

	class AuthReq
	{
	public:
		std::string method = "public/auth";
		std::string jsonrpc = jsonRpcV;
		uint32_t id = 1;

		class Params
		{
		public:
			std::string grant_type = "client_credentials";
			std::string client_id = ::clientId;
			std::string client_secret = ::clientSecret;
			std::string scope = "connection";

			NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Params, grant_type, client_id, client_secret, scope);
		} params;
			
		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(AuthReq, method, jsonrpc, id, params);
	};

	class AuthRes
	{
	public:
		class Result
		{
		public:
			std::vector<std::string> enabled_features;
			std::string access_token;
			int32_t expires_in;
			std::string refresh_token;
			std::string scope;
			std::string token_type;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Result, enabled_features, access_token, expires_in, refresh_token, scope, token_type);
		};

		std::string jsonrpc;
		int32_t id;
		Result result;
		int64_t usIn;
		int64_t usOut;
		int32_t usDiff;
		bool testnet;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(AuthRes, jsonrpc, id, result, usIn, usOut, usDiff, testnet);
	};

	///Currencies Start 

	struct CurrenciesReq {
		std::string method = "public/get_currencies";
		std::string jsonrpc = jsonRpcV;
		int32_t id = 1;

		//struct Params {
		//	// Empty for this request
		//	NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Params) // No fields
		//} params;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(CurrenciesReq, method, jsonrpc, id)
	};



	// Withdrawal priority structure
	struct WithdrawalPriority {
		std::string name;
		double value;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(WithdrawalPriority, name, value)
	};

	// Currency result structure
	struct Currency {
		std::string currency;
		double withdrawal_fee;
		double min_withdrawal_fee;
		int fee_precision;
		std::vector<WithdrawalPriority> withdrawal_priorities;
		std::string coin_type;
		int min_confirmations;
		std::string currency_long;
		bool in_cross_collateral_pool;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(
			Currency,
			currency,
			withdrawal_fee,
			min_withdrawal_fee,
			fee_precision,
			withdrawal_priorities,
			coin_type,
			min_confirmations,
			currency_long,
			in_cross_collateral_pool)
	};

	// Main response structure
	struct CurrenciesRes {
		std::string jsonrpc;
		int id;
		std::vector<Currency> result;
		int64_t usIn;
		int64_t usOut;
		int32_t usDiff;
		bool testnet;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(
			CurrenciesRes,
			jsonrpc,
			id,
			result,
			usIn,
			usOut,
			usDiff,
			testnet)
	};

	/// Currencies End


}