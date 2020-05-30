
#include <iostream>
#include <node.h>

namespace unicoding {
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::NewStringType;
  using v8::Object;
  using v8::String;
  using v8::Value;
  using v8::Map;
  using v8::Context;
  using v8::Number;

  // interface interact with node
  void Initialize(Local<Object> exports);

  void calculateUTFInfo(const FunctionCallbackInfo<Value>& args) {
    Local<Map> result = Map::New(args.GetIsolate());
    if (args.Length() > 0) {
      Local<String> param = Local<String>::Cast(args[0]);
      std::cout << "bytes:" << param->Utf8Length() << "; utf16 code units:" << param->Length() << std::endl;

      Local<Context> ctx = Context::New(args.GetIsolate());
      result->Set(ctx,
          String::NewFromUtf8(args.GetIsolate(), "bytes", NewStringType::kNormal).ToLocalChecked(),
          Number::New(args.GetIsolate(), param->Utf8Length())
          );
      result->Set(ctx,
          String::NewFromUtf8(args.GetIsolate(), "codeUnits", NewStringType::kNormal).ToLocalChecked(),
          Number::New(args.GetIsolate(), param->Length())
          );
    }
    args.GetReturnValue().Set(result);
  }

  void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "calculateUTFInfo", calculateUTFInfo);
  }

  NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
}
