#include "Models.hpp"

using json = nlohmann::json;

namespace dw::model {
	/*
    void to_json(json& j, const AuthReq& req) {
		j = json{ 
				{"method", req.method}, 
				{"jsonrpc", req.jsonrpc}, 
				{"id", req.id}, 
				{"params", {
					{"grant_type", req.params.grant_type},
					{"client_id", req.params.client_id},
					{"client_secret", req.params.client_secret},
					{"scope", req.params.scope},
				}}
		};
    }

    void from_json(const json& j, AuthRes& res) {
        j.at("enabled_features").get_to(res.enabled_features);
		j.at("access_token").get_to(res.access_token);
		j.at("expires_in").get_to(res.expires_in);
		j.at("refresh_token").get_to(res.refresh_token);
		j.at("scope").get_to(res.scope);
		j.at("token_type").get_to(res.token_type);
    }

*/
	void test() {
        std::string jsonStr = R"({
    "jsonrpc": "2.0",
    "id": 11,
    "result": {
        "enabled_features": ["feature1", "feature2"],
        "access_token": "sample_access_token",
        "expires_in": 31536000,
        "refresh_token": "sample_refresh_token",
        "scope": "scope_value",
        "token_type": "bearer"
    },
    "usIn": 1733756581167566,
    "usOut": 1733756581167815,
    "usDiff": 249,
    "testnet": true
})";

        nlohmann::json jsonParsed = nlohmann::json::parse(jsonStr);

        dw::model::AuthRes res = jsonParsed.get<dw::model::AuthRes>();

	}
}
