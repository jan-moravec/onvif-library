#include <iostream>
#include "libonvif/onvifdiscovery.h"

int main()
{
    OnvifDiscovery discovery;

    discovery.generateCameraIdentifier();
    discovery.addType("NetworkVideoTransmitter");
    discovery.addAddress("http://10.0.0.30:8004");
    discovery.addProfile("Streaming");
    discovery.addHardware("NetworkVideoTransmitter");
    discovery.setCameraName("Workswell");
    discovery.setLocationCountry("Czechia");
    discovery.setLocationCity("Prague");

    discovery.start();
    std::this_thread::sleep_for(std::chrono::seconds(30));
    discovery.finish();
    return 0;
}
