#include <napi.h>
#include <iostream>
#include "worker.h"
#include <libtld/tld.h>
#include "../../include/json/single_include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

void Worker::Execute() {
  std::string ret(buffer);
  auto j = json::parse(ret);
  for (unsigned int i = 0; i < j.size(); i++)
  {
    auto obj = j.at(i);
    json::value_type domain = obj["value"];

    if (!domain.is_null())
    {
      char *uri_lowercase = tld_domain_to_lowercase(domain.get<std::string>().c_str());
      struct tld_info tldinfo;
      enum tld_result r;
      r = tld(uri_lowercase, &tldinfo);
      // tldinfo.f_tld will give us the tld, ex: .net
      if(r == TLD_RESULT_SUCCESS) {
        // this loop resolves the domain, basically iterates over the string until
        // it gets the position of the next dot(from the end of the string to the
        // begin)
        const char *s = uri_lowercase + tldinfo.f_offset - 1;
        while(s > uri_lowercase)
        {
            if(*s == '.')
            {
                ++s;
                break;
            }
            --s;
        }
        // domain.tld = tldinfo.f_tld;
        // printf("Sub-domain(s): \"%.*s\"\n", (int)(s - uri_lowercase), uri_lowercase);
        // printf("Domain: \"%.*s\"\n", (int)(tldinfo.f_tld - s), s);
        // printf("TLD: \"%s\"\n", tldinfo.f_tld);
      }
    }
  }
}

void Worker::OnOK() {
  Napi::HandleScope scope(Env());
  Callback().Call({ Env().Undefined() });
}

