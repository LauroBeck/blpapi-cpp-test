#include <blpapi_session.h>
#include <blpapi_sessionoptions.h>
#include <iostream>

using namespace BloombergLP;

int main()
{
    blpapi::SessionOptions options;
    options.setServerHost("localhost");
    options.setServerPort(8194);

    blpapi::Session session(options);

    if (!session.start()) {
        std::cout << "Failed to start session\n";
        return 1;
    }

    std::cout << "Session started successfully\n";

    session.stop();
    return 0;
}
