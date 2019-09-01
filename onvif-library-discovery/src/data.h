#ifndef DATA_H
#define DATA_H

#include <atomic>
#include <string>
#include <vector>

class Data
{
public:
    std::atomic_bool ready{false};

    std::string endpoint;
    std::vector<std::string> types;
    std::vector<std::string> scopes;
    std::vector<std::string> addresses;

    void finish();
    const char *getEndpoint() const { return _endpoint.c_str(); }
    const char *getTypes() const { return _types.c_str(); }
    const char *getScopes() const { return _scopes.c_str(); }
    const char *getAddresses() const { return _addresses.c_str(); }

    const char *getUrlProtocol() const { return url_protocol.c_str(); }
    const char *getUrlAddress() const { return url_address.c_str(); }
    int getUrlPort() const { return url_port; }
    const char *getUrl() const { return url.c_str(); }

private:
    std::string _endpoint;
    std::string _types;
    std::string _scopes;
    std::string _addresses;

    const std::string url_protocol = "soap.udp://";
    const std::string url_address = "239.255.255.250";
    const int url_port = 3702;
    const std::string url = url_protocol + url_address + ":" + std::to_string(url_port);

    void prepareStringFromVector(const std::vector<std::string> &in, std::string &out);
};

#endif // DATA_H
