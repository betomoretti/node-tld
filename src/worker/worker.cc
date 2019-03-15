#include <napi.h>
#include <iostream>
#include <sstream>
#include "worker.h"
#include <libtld/tld.h>
#include "../../include/json/single_include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

void print_domain(const char *s, char *uri_lowercase, tld_info tldinfo)
{
  while (s > uri_lowercase)
  {
    if (*s == '.')
    {
      ++s;
      break;
    }
    --s;
  }
  printf("Domain: \"%.*s\"\n", (int)(tldinfo.f_tld - s), s);
  // printf("Sub-domain(s): \"%.*s\"\n", (int)(s - uri_lowercase), uri_lowercase);
  // printf("TLD: \"%s\"\n", tldinfo.f_tld);
}

void Worker::Execute()
{
  cout << "-------- NEW WORKER -----------------" << endl;
  std::stringstream ss;
  ss << buffer;
  json j;
  struct tld_info tldinfo;
  enum tld_result r;

  while (ss >> j && !j.is_null())
  {
    json::value_type domain = j["value"];
    if (!domain.is_null())
    {
      // cout << domain << endl;
      char *uri_lowercase = tld_domain_to_lowercase(domain.get<std::string>().c_str());
      r = tld(uri_lowercase, &tldinfo);
      // tldinfo.f_tld will give us the tld, ex: .net
      if (r == TLD_RESULT_SUCCESS)
      {
        // this loop resolves the domain, basically iterates over the string until
        // it gets the position of the next dot(from the end of the string to the
        // begin)
       const char *s = uri_lowercase + tldinfo.f_offset - 1;
        print_domain(s, uri_lowercase, tldinfo);
        // domain.tld = tldinfo.f_tld;
      }
    }
  }
}

void Worker::OnOK()
{
  Napi::HandleScope scope(Env());
  Callback().Call({Env().Undefined()});
}
