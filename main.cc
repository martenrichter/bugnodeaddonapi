
#include <napi.h>

using namespace Napi;

napi_status NAPI_CDECL test(napi_env env,
                                          double value,
                                          napi_value* result) {
    printf("test %lg\n", value);

}

Napi::Value initLib(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  double timedelay = 200000;
  napi_value dummy;
  test(env,timedelay,&dummy);
  auto val = Napi::Value::From(env, timedelay);
  printf("val %lg %lg\n", val.ToNumber().DoubleValue(), timedelay);
  if (val.ToNumber().DoubleValue() != timedelay) {
    Napi::Error::New(env, "Val does not match! " +
                              std::to_string(val.ToNumber().DoubleValue()))
        .ThrowAsJavaScriptException();
    return Napi::Value();
  }
  return Napi::Boolean::New(env, true);
}


Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    Napi::Function initna = Function::New<initLib>(env);
    exports.Set("initLib", initna);

    // env.SetInstanceData<Http3Constructors>(constr);
    return exports;
}

NODE_API_MODULE(webtransport, Init)
