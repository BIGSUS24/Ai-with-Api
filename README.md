# Gemini API Chatbot

This is a simple chatbot implemented in C++ that communicates with the Gemini API to generate responses to user input. The chatbot sends HTTP POST requests to the API and processes the JSON responses to display meaningful results.

## Features
- Uses **cURL** for HTTP communication.
- Processes JSON responses with the **nlohmann/json** library.
- Modular structure with API request logic separated for reusability.

## Requirements
- **C++17** or later.
- **cURL** library.
- **nlohmann/json** library.

## Installation

1. Install the required dependencies:
   - [cURL](https://curl.se/)
   - [nlohmann/json](https://github.com/nlohmann/json)

2. Clone this repository and navigate to the project directory:
   ```bash
   git clone https://github.com/your-repo-name/gemini-api-chatbot.git
   cd gemini-api-chatbot
