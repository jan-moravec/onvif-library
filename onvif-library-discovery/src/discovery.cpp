#include "discovery.h"
#include "data.h"

void wsdd_event_Hello(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber, const char *MessageID, const char *RelatesTo, const char *EndpointReference, const char *Types, const char *Scopes, const char *MatchBy, const char *XAddrs, unsigned int MetadataVersion)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void wsdd_event_Bye(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber, const char *MessageID, const char *RelatesTo, const char *EndpointReference, const char *Types, const char *Scopes, const char *MatchBy, const char *XAddrs, unsigned int *MetadataVersion)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

soap_wsdd_mode wsdd_event_Probe(struct soap *soap, const char *MessageID, const char *ReplyTo, const char *Types, const char *Scopes, const char *MatchBy, struct wsdd__ProbeMatchesType *matches)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    const Data *data = reinterpret_cast<const Data *>(soap->user);

    soap_wsdd_init_ProbeMatches(soap, matches);
    soap_wsdd_add_ProbeMatch(soap, matches, data->getEndpoint(), data->getTypes(), data->getScopes(), NULL, data->getAddresses(), 1);
    if (soap_wsdd_ProbeMatches(soap, data->getUrlProtocol(), soap_wsa_rand_uuid(soap), MessageID, NULL, matches) != SOAP_OK) {
        soap_print_fault(soap, stderr);
    }

    return SOAP_WSDD_ADHOC;
}

void wsdd_event_ProbeMatches(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber, const char *MessageID, const char *RelatesTo, struct wsdd__ProbeMatchesType *matches)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

soap_wsdd_mode wsdd_event_Resolve(struct soap *soap, const char *MessageID, const char *ReplyTo, const char *EndpointReference, struct wsdd__ResolveMatchType *match)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return SOAP_WSDD_ADHOC;
}

void wsdd_event_ResolveMatches(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber, const char *MessageID, const char *RelatesTo, struct wsdd__ResolveMatchType *match)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

SOAP_FMAC5 int SOAP_FMAC6 SOAP_ENV__Fault(struct soap *psoap, char *faultcode, char *faultstring, char *faultactor, struct SOAP_ENV__Detail *detail, struct SOAP_ENV__Code *SOAP_ENV__Code, struct SOAP_ENV__Reason *SOAP_ENV__Reason, char *SOAP_ENV__Node, char *SOAP_ENV__Role, struct SOAP_ENV__Detail *SOAP_ENV__Detail)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tdn__Hello(struct soap *psoap, struct wsdd__HelloType tdn__Hello, struct wsdd__ResolveType *tdn__HelloResponse)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tdn__Bye(struct soap *psoap, struct wsdd__ByeType tdn__Bye, struct wsdd__ResolveType *tdn__ByeResponse)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tdn__Probe(struct soap *psoap, struct wsdd__ProbeType tdn__Probe, struct wsdd__ProbeMatchesType *tdn__ProbeResponse)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tdn__Hello(struct soap*, struct wsdd__HelloType tdn__Hello, struct wsdd__ResolveType &tdn__HelloResponse)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tdn__Bye(struct soap*, struct wsdd__ByeType tdn__Bye, struct wsdd__ResolveType &tdn__ByeResponse)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tdn__Probe(struct soap*, struct wsdd__ProbeType tdn__Probe, struct wsdd__ProbeMatchesType &tdn__ProbeResponse)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return SOAP_OK;
}
