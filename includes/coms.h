*//#include "api.h"
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

// Callback function to handle the API response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string make_post_request(const std::string& url, const std::string& api_key, const std::string& user_input) {
    CURL* curl;
    CURLcode res;
    std::string read_buffer;

    // Initialize cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set the URL with the API key
        std::string full_url = url + "?key=" + api_key;
        curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());

        // Set callback for handling API response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

        // Prepare the corrected JSON payload
        nlohmann::json payload = {
            {"contents", {
                {{"parts", {{"text", user_input}}}}
            }}
        };
        std::string payload_str = payload.dump();

        // Set headers and POST data
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());

        // Disable SSL verification (for testing purposes)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
            read_buffer = "Error communicating with API.";
        }

        // Cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    // Cleanup global cURL state
    curl_global_cleanup();

    return read_buffer.empty() ? "No response received from API." : read_buffer;//*
}
