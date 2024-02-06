// Copyright (c) 2023 Krypton. All rights reserved.
#include <runtime/KryptonSTD.h>


namespace StandardLibrary {
    void print(Environment* env) {
        auto value = env->get("value");
    }
}

using namespace StandardLibrary;

void KryptonSTD::load() {
    addFunction
    ("print", print,
     nullptr,
     {{"value", nullptr}}
     );
}

void KryptonSTD::addFunction(const string &name, std::function<void(Environment *)>, const Type *returnType,
                             vector<pair<string, const Type *>> parameters) {

}
