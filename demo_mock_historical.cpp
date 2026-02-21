#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <ctime>

// --- Mock classes to simulate Bloomberg API ---
class Element {
public:
    std::string name;
    std::map<std::string, std::vector<double>> fieldData;

    Element(const std::string& n) : name(n) {}

    void setFieldData(const std::string& field, const std::vector<double>& values) {
        fieldData[field] = values;
    }

    // Mark print() as const so it works with const references
    void print() const {
        std::cout << name << "\n";
        std::cout << std::setw(12) << "Date";
        for (auto& f : fieldData)
            std::cout << std::setw(12) << f.first;
        std::cout << "\n";

        int months = fieldData.begin()->second.size();
        for (int i = 0; i < months; ++i) {
            std::cout << std::setw(12) << ("2026-0" + std::to_string(i+1));
            for (auto& f : fieldData) {
                std::cout << std::setw(12) << f.second[i];
            }
            std::cout << "\n";
        }
    }
};

class Message {
public:
    Element securityData;
    Message(const std::string& security) : securityData(security) {}
};

class Session {
    std::string host;
public:
    Session(const std::string& h) : host(h) {}
    bool start() { 
        std::cout << "Mock session started to " << host << "\n"; 
        return true; 
    }
    void stop() { std::cout << "Mock session stopped\n"; }

    void sendRequest(const std::vector<std::string>& securities,
                     const std::vector<std::string>& fields) {
        for (auto& sec : securities) {
            Message msg(sec);
            // Fill mock data
            for (auto& f : fields) {
                std::vector<double> values;
                for (int i=0; i<12; ++i) values.push_back(100.0 + rand()%20);
                msg.securityData.setFieldData(f, values);
            }
            std::cout << "Sending mock request for security: " << sec << "\n";
            std::cout << "Fields: ";
            for (auto& f : fields) std::cout << f << " ";
            std::cout << "\nReceiving mock response...\n";
            msg.securityData.print();
            std::cout << "\n";
        }
    }
};

// --- Main program ---
int main() {
    std::vector<std::string> d_securities = {"IBM US Equity", "GOOG US Equity"};
    std::vector<std::string> d_fields = {"PX_LAST", "PX_BID"};

    Session session("localhost:8194");

    if (!session.start()) {
        std::cout << "Failed to start mock session\n";
        return 1;
    }

    session.sendRequest(d_securities, d_fields);
    session.stop();
    return 0;
}
