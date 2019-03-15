#include <napi.h>
#include <iostream>
#include <sstream>
#include "src/worker/worker.h"
#include "../../include/json/single_include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

Napi::Promise ExtractTld(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();
  Napi::Function callback = info[1].As<Napi::Function>();
  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);
  Worker* worker = new Worker(callback, buffer.Data());
  worker->Queue();

  deferred.Resolve(Napi::String::New(info.Env(), "OK"));
  return deferred.Promise();
}

Napi::Object init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "extractTld"), Napi::Function::New(env, ExtractTld));
    return exports;
};

NODE_API_MODULE(tld, init);
