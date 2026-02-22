#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

// Mock classes to simulate Bloomberg API
namespace BloombergLP {
namespace blpapi {

class SessionOptions {
public:
    void setServerHost(const std::string& host) {
        serverHost = host;
    }
    void setServerPort(int port) {
        serverPort = port;
    }
    std::string serverHost = "localhost";
    int serverPort = 8194;
};

class Session {
public:
    Session(const SessionOptions& opts) : options(opts) {}
    
    bool start() {
        std::cout << "Mock session started to " << options.serverHost
                  << ":" << options.serverPort << "\n";
        return true;
    }
    
    void stop() {
        std::cout << "Mock session stopped\n";
    }
    
    bool sendRequest(const std::string& security,
                     const std::vector<std::string>& fields) {
        std::cout << "Sending mock request for security: " << security << "\n";
        std::cout << "Fields: ";
        for (auto& f : fields) std::cout << f << " ";
        std::cout << "\n";
        return true;
    }
    
    void receiveResponse() {
        std::cout << "Receiving mock response...\n";
        // Simulate a small delay for realism
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "Date       PX_LAST\n";
        std::cout << "2026-02-18 140.50\n";
        std::cout << "2026-02-19 141.20\n";
        std::cout << "2026-02-20 139.95\n";
    }

private:
    SessionOptions options;
};

} // namespace blpapi
} // namespace BloombergLP

using namespace BloombergLP::blpapi;

int main() {
    try {
        SessionOptions options;
        options.setServerHost("localhost");
        options.setServerPort(8194);

        Session session(options);

        if (!session.start()) {
            std::cerr << "Failed to start session\n";
            return 1;
        }

        // Mock request
        std::string security = "IBM US Equity";
        std::vector<std::string> fields = {"PX_LAST"};
        session.sendRequest(security, fields);

        // Mock response
        session.receiveResponse();

        session.stop();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
