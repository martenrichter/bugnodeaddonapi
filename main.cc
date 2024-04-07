
#include <napi.h>

using namespace Napi;

struct Http3Constructors
{
  Napi::FunctionReference ref;
};

void initLib(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  double timedelay = 200000;
  auto val = Napi::Value::From(env, timedelay);
  printf("val %lg %lg\n", val.ToNumber().DoubleValue(), timedelay);
  if (val.ToNumber().DoubleValue() != timedelay) {
    Napi::Error::New(env, "Val does not match! " +
                              std::to_string(val.ToNumber().DoubleValue()))
        .ThrowAsJavaScriptException();
    return;
  }
  return;
}


Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    Http3Constructors *constr = new Http3Constructors();
    Napi::Function initna = Function::New<initLib>(env);
    constr->ref = Napi::Persistent(initna);
    exports.Set("initLib", initna);

    // env.SetInstanceData<Http3Constructors>(constr);
    return exports;
}

NODE_API_MODULE(webtransport, Init)
