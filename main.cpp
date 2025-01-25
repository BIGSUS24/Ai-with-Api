#include <iostream>
#include <string>
#include "api.h"

int main() {
    std::cout << "🤖 Welcome to  Chatbot! Type 'exit' to quit. 🤖" << std::endl;

    // Your API key and URL
    const std::string api_key = "Your Api Key"; // paste your api key here
    const std::string api_url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent";

    while (true) {
        std::cout << "You: ";
        std::string user_input;
        std::getline(std::cin, user_input);

        if (user_input == "exit") {
            break;
        }

        // Call the API
        std::string response = make_post_request(api_url, api_key, user_input);
        std::cout << "Bot: " << response << std::endl;
    }

    return 0;
}
