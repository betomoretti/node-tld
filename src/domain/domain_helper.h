#include <napi.h>
#ifndef DOMAIN_HELPER_H
#define DOMAIN_HELPER_H
#include "domain.h"

Domain unpack_domain(Napi::Env env, Napi::Object domain);

#endif