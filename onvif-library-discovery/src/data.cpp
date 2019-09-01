#include "data.h"
#include <iostream>

void Data::finish()
{
    _endpoint = endpoint;
    prepareStringFromVector(types, _types);
    prepareStringFromVector(scopes, _scopes);
    prepareStringFromVector(addresses, _addresses);

    ready = true;
}

void Data::prepareStringFromVector(const std::vector<std::string> &in, std::string &out)
{
    out.clear();
    for (const std::string &i : in) {
        out += i + " ";
    }
    if (!out.empty()) {
        out.pop_back();
    }
}
