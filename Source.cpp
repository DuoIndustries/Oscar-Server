#include <iostream>
#include <nlohmann/json.hpp>
#include <uwebsockets/App.h>

using json = nlohmann::json;

using namespace std;

int main() {
    struct PerSocketData {
        /* Fill with user data */
    };

    uWS::App().ws<PerSocketData>("/*", {
            .idleTimeout = 1000,
            .maxBackpressure = 100 * 1024 * 1024,
            .closeOnBackpressureLimit = false,
            .resetIdleTimeoutOnSend = false,
            .sendPingsAutomatically = true,
            .open = [](auto*/*ws*/) {
                cout << "open\n";
            },
            .message = [](auto* ws, std::string_view message, uWS::OpCode opCode) {
                cout << message;
            },
            .close = [](auto*/*ws*/, int /*code*/, std::string_view /*message*/) {
                cout << "close\n";
            }
            }).listen(8080, [](auto* listen_socket) {
                if (listen_socket) {
                    std::cout << "Listening on port " << 8080 << std::endl;
                }
    }).run();
}