#include "libonvif/onvifdiscovery.h"

#include "stdsoap2.h"
#include "soapH.h"
#include "wsddapi.h"
#include "wsdd.nsmap"

#include "data.h"

OnvifDiscovery::OnvifDiscovery()
{
    soap = soap_new1(SOAP_IO_UDP);
    soap_register_plugin(soap, soap_wsa);
    data = new Data;
}

OnvifDiscovery::~OnvifDiscovery()
{
    soap_end(soap);
    soap_done(soap);
    delete data;
}

void OnvifDiscovery::setCameraIdentifier(const std::string &id)
{
    this->id = id;
}

void OnvifDiscovery::generateCameraIdentifier()
{
    id = soap_wsa_rand_uuid(soap);
}

void OnvifDiscovery::addType(const std::string &type)
{
    types.push_back(type);
}

void OnvifDiscovery::addAddress(const std::string &address)
{
    addresses.push_back(address);
}

void OnvifDiscovery::addProfile(const std::string &profile)
{
    profiles.push_back(profile);
}

void OnvifDiscovery::addHardware(const std::string &hardware)
{
    this->hardware.push_back(hardware);
}

void OnvifDiscovery::setLocationCountry(const std::string &country)
{
    this->country = country;
}

void OnvifDiscovery::setLocationCity(const std::string &city)
{
    this->city = city;
}

void OnvifDiscovery::setCameraName(const std::string &name)
{
    this->name = name;
}

int OnvifDiscovery::start()
{
    prepareData();
    soap->user = reinterpret_cast<void *>(data);

    if (startProbeThread() != 0) {
        std::cerr << __PRETTY_FUNCTION__ << ": startProbeThread" << std::endl;
        return -1;
    }

    if (sendHello() != 0) {
        std::cerr << __PRETTY_FUNCTION__ << ": sendHello" << std::endl;
        return -1;
    }

    return 0;
}

int OnvifDiscovery::finish()
{
    if (finishProbeThread() != 0) {
        std::cerr << __PRETTY_FUNCTION__ << ": finishProbeThread" << std::endl;
        return -1;
    }

    if (sendBye() != 0) {
        std::cerr << __PRETTY_FUNCTION__ << ": sendBye" << std::endl;
        return -1;
    }

    return 0;
}

void OnvifDiscovery::prepareData()
{
    data->endpoint = id;

    data->types.clear();
    for (const std::string &type : types) {
        data->types.push_back("tdn:" + type);
    }

    data->addresses.clear();
    data->addresses = addresses;

    data->scopes.clear();
    for (const std::string &profile : profiles) {
        data->scopes.push_back("onvif://www.onvif.org/profile/" + profile);
    }
    for (const std::string &hw : hardware) {
        data->scopes.push_back("onvif://www.onvif.org/hardware/" + hw);
    }
    data->scopes.push_back("onvif://www.onvif.org/name/" + name);
    data->scopes.push_back("onvif://www.onvif.org/location/country/" + country);
    data->scopes.push_back("onvif://www.onvif.org/location/city/" + city);

    data->finish();
}

int OnvifDiscovery::startProbeThread()
{
    soap->bind_flags = SO_REUSEADDR;
    if (!soap_valid_socket(soap_bind(soap, NULL, data->getUrlPort(), 1000))) {
        std::cerr << __PRETTY_FUNCTION__ << ": bind" << std::endl;
        soap_print_fault(soap, stderr);
        return -1;
    }

    ip_mreq multicast;
    multicast.imr_multiaddr.s_addr = inet_addr(data->getUrlAddress());
    multicast.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(soap->master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&multicast, sizeof(multicast)) != 0) {
        std::cerr << __PRETTY_FUNCTION__ << ": group membership: " << strerror(errno) << std::endl;
        return -1;
    }

    run = true;
    thread = std::thread([&](){
        while (run) {
            soap_wsdd_listen(soap, -100000); // 100 ms
        }
    });

    return 0;
}

int OnvifDiscovery::finishProbeThread()
{
    run = false;
    thread.join();

    ip_mreq multicast;
    multicast.imr_multiaddr.s_addr = inet_addr(data->getUrlAddress());
    multicast.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(soap->master, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&multicast, sizeof(multicast)) < 0) {
        std::cerr << __PRETTY_FUNCTION__ << ": group membership: " << strerror(errno) << std::endl;
        return -1;
    }

    return 0;
}

int OnvifDiscovery::sendHello()
{
    struct soap *soap_hello = soap_new1(SOAP_IO_UDP);
    int flags = soap_hello->connect_flags;
    flags = soap_hello->connect_flags;
    soap_hello->connect_flags |= SO_BROADCAST;
    for (int i = 0; i < 3; ++i) {
        int res = soap_wsdd_Hello(soap_hello, SOAP_WSDD_ADHOC, data->getUrl(), soap_wsa_rand_uuid(soap_hello), NULL, data->getEndpoint(), data->getTypes(), data->getScopes(), NULL, data->getAddresses(), 1);
        if (res != SOAP_OK) {
            soap_print_fault(soap_hello, stderr);
            return -1;
        }
    }
    soap_hello->connect_flags = flags;
    soap_end(soap_hello);
    soap_done(soap_hello);

    return 0;
}

int OnvifDiscovery::sendBye()
{
    struct soap *soap_bye = soap_new1(SOAP_IO_UDP);
    int flags = soap_bye->connect_flags;
    soap_bye->connect_flags |= SO_BROADCAST;
    for(int i = 0; i < 3; i++) {
        int res = soap_wsdd_Bye(soap_bye, SOAP_WSDD_ADHOC, data->getUrl(), soap_wsa_rand_uuid(soap_bye), data->getEndpoint(), data->getTypes(), data->getScopes(), NULL, data->getAddresses(), 1);
        if (res != SOAP_OK) {
            soap_print_fault(soap_bye, stderr);
            return -1;
        }
    }
    soap_bye->connect_flags = flags;
    soap_end(soap_bye);
    soap_done(soap_bye);

    return 0;
}
