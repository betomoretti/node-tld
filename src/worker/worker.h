#include <napi.h>
#include "../domain/domain.h"

#ifndef WORKER_H
#define WORKER_H

class Worker : public Napi::AsyncWorker {
  public:
    Worker(Napi::Function& callback, char* buffer)
      : Napi::AsyncWorker(callback), buffer(buffer) {}

    void Execute ();
  protected:
    void OnOK();
  private:
    char* buffer;
};

#endif