#ifndef ONVIFDISCOVERY_H
#define ONVIFDISCOVERY_H

#include <string>
#include <vector>
#include <atomic>
#include <thread>

class Data;

class OnvifDiscovery
{
public:
    OnvifDiscovery();
    ~OnvifDiscovery();

    /// ID must be unique for each camera and should not change during the lifetime of the camera.
    void setCameraIdentifier(const std::string &id);
    /// It can be generated (once) by calling soap_wsa_rand_uuid(soap)
    void generateCameraIdentifier();

    /// Types implemented by the camera
    void addType(const std::string &type);

    /// Addresses for device services
    void addAddress(const std::string &address);

    /// Scope parameters (profiles, location, hardware, name)
    void addProfile(const std::string &profile);
    void addHardware(const std::string &hardware);
    void setLocationCountry(const std::string &country);
    void setLocationCity(const std::string &city);
    void setCameraName(const std::string &name);

    /// Start discovery
    int start();
    /// Finish discovery
    int finish();

private:
    std::string id;
    std::vector<std::string> types;
    std::vector<std::string> addresses;
    std::vector<std::string> profiles;
    std::vector<std::string> hardware;
    std::string country;
    std::string city;
    std::string name;

    Data *data;
    struct soap *soap;
    std::thread thread;

    void prepareData();
    int startProbeThread();
    int finishProbeThread();
    int sendHello();
    int sendBye();

    std::atomic_bool run;
};

#endif // ONVIFDISCOVERY_H
