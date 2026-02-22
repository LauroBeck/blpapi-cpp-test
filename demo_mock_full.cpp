#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>

// Mock session class
class MockSession {
public:
    MockSession(const std::string& host, int port)
        : host_(host), port_(port), started_(false) {}

    bool start() {
        started_ = true;
        std::cout << "Mock session started to " << host_ << ":" << port_ << std::endl;
        return started_;
    }

    void stop() {
        if (started_) {
            std::cout << "Mock session stopped" << std::endl;
            started_ = false;
        }
    }

    void sendRequest(const std::vector<std::string>& securities,
                     const std::vector<std::string>& fields) 
    {
        std::cout << "Sending mock request for securities:\n";
        for (auto& s : securities)
            std::cout << " - " << s << std::endl;

        std::cout << "Fields: ";
        for (auto& f : fields)
            std::cout << f << " ";
        std::cout << "\n\nReceiving mock response...\n";

        // Simulate historical data for last 5 days
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);

        for (auto& s : securities) {
            std::cout << "=== " << s << " ===\n";
            std::cout << std::setw(12) << "Date";
            for (auto& f : fields)
                std::cout << std::setw(12) << f;
            std::cout << std::endl;

            for (int i = 5; i > 0; --i) {
                tm.tm_mday -= i;
                std::mktime(&tm); // normalize date
                std::cout << std::setw(12)
                          << std::put_time(&tm, "%Y-%m-%d");

                for (auto& f : fields) {
                    // Generate mock value
                    double value = 100 + (std::rand() % 5000) / 100.0;
                    std::cout << std::setw(12) << value;
                }
                std::cout << std::endl;
                tm.tm_mday += i; // reset day
            }
            std::cout << std::endl;
        }
    }

private:
    std::string host_;
    int port_;
    bool started_;
};

int main() {
    std::vector<std::string> securities = {"IBM US Equity", "MSFT US Equity", "AAPL US Equity"};
    std::vector<std::string> fields = {"PX_LAST", "OPEN", "HIGH", "LOW"};

    MockSession session("localhost", 8194);

    if (!session.start()) {
        std::cerr << "Failed to start mock session!" << std::endl;
        return 1;
    }

    session.sendRequest(securities, fields);
    session.stop();

    return 0;
}
