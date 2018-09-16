#include <string>
#ifndef DOMAIN_H
#define DOMAIN_H

using namespace std;

class Domain {
  public:
    Domain(string uri, string ip);
    string uri;
    string ip;
    string subdomain;
    string domain;
    string tld;
};

#endif