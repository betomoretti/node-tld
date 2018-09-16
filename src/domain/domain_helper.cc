#include <napi.h>
#include "domain.h"

Domain unpack_domain(Napi::Env env, Napi::Object domain) {
  Napi::String domain_key = Napi::String::New(env, "domain");
  Napi::String ip_key = Napi::String::New(env, "ip");
  Napi::Value domain_value = domain.Get(domain_key);
  Napi::Value ip_value = domain.Get(ip_key);
  Domain domain_instance(domain_value.ToString(), ip_value.ToString());

  return domain_instance;
}