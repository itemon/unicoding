#include <iostream>
#include <node.h>
#include <cstdlib>

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

  // calculate code point
  inline Local<String> translateCodePoint(Local<String> str);

  // print binary reprent
  template<typename T>
  void print_binary(uint8_t t);

  template<typename T>
  void print_binary(/*uint8_t*/T t) {
    size_t binary_count = 8 * sizeof(t);
    char* binary_represent = (char*)malloc(binary_count + 1);
    memset(binary_represent, '0', binary_count);

    uint8_t mask = 1;
    size_t i = 1;
    while (i <= binary_count) {
      if ((mask & t) != 0) {
        binary_represent[binary_count - i] = '1';
      }
      mask = mask << 1;
      ++i;
    }

    std::cout << binary_represent << std::endl;
    free(binary_represent);
  }

  Local<String> translateCodePoint(Local<String> str) {
    uint8_t buf[str->Utf8Length()];
    str->WriteOneByte(buf);

    for (int i = 0; i < str->Utf8Length(); ++i) {
      std::cout << (int)buf[i] << std::endl;
    }
    return Local<String>{};
  }

  void calculateUTFInfo(const FunctionCallbackInfo<Value>& args) {
    print_binary<int>(15);

    Local<Map> result = Map::New(args.GetIsolate());
    if (args.Length() > 0) {
      Local<String> param = Local<String>::Cast(args[0]);
      std::cout << "bytes:" << param->Utf8Length() << "; utf16 code units:" << param->Length() << std::endl;

      translateCodePoint(param);

      Local<Context> ctx = args.GetIsolate()->GetCurrentContext();//Context::New(args.GetIsolate());
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

  void Initialize(Local<Object> exports, Local<Value> module, void* priv) {
    NODE_SET_METHOD(exports, "calculateUTFInfo", calculateUTFInfo);
  }

  NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
}
