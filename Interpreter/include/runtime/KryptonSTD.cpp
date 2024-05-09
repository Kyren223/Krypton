// Copyright (c) 2023 Krypton. All rights reserved.
#include <runtime/KryptonSTD.h>
#include <types/Primitive.h>
#include <iostream>

namespace StandardLibrary {

    string fromValue(const Value& value)
    {
        if (&value.getType() == &Primitive::INT)
        {
            return std::to_string(value.getValue<int>());
        }
        else if (&value.getType() == &Primitive::DEC)
        {
            return std::to_string(value.getValue<double>());
        }
        else if (&value.getType() == &Primitive::BOOL)
        {
            return value.getValue<bool>() ? "true" : "false";
        }
        else if (&value.getType() == &Primitive::CHAR)
        {
            return string(1, value.getValue<unsigned char>());
        }
        else if (&value.getType() == &Primitive::STR)
        {
            return value.getValue<string>();
        }
        else return "unknown";
    }

    void print(Environment* env)
    {
        auto& value = *env->get("value");
        string s = fromValue(value);
        Logger::print(LogMode::NONE, s, Color::WHITE);
    }

    void toString(Environment* env)
    {
        auto& value = *env->get("value");
        string s = fromValue(value);
        env->setReturnValue(optional<Value>({Primitive::STR, s}));
    }

    void input(Environment* env)
    {
        string input;
        std::getline(std::cin, input);
        env->setReturnValue(optional<Value>({Primitive::STR, input}));
    }

    void typeofValue(Environment* env) {
        auto value = env->get("value");
        if (value == nullptr)
        {
            env->setReturnValue(optional<Value>({Primitive::STR, "void"}));
            return;
        }
        env->setReturnValue(optional<Value>({Primitive::STR, value->getType().getName()}));
    }
}

using namespace StandardLibrary;

void KryptonSTD::load() {
    // parameter of std::nullopt - Any type (var)
    // Return of std::nullopt - No type (void)
    // No return specified - Any type (var)
    addFunction
    ("print", print,
     {},
     {{"value", std::nullopt}}
     );
    addFunction
    ("toString", toString,
     {&Primitive::STR},
     {{"value", std::nullopt}}
     );
    addFunction
    ("input", input,
     {&Primitive::STR},
    {}
    );
    addFunction
    ("typeof", typeofValue,
   {&Primitive::STR},
   {{"value", std::nullopt}}
    );
}

void KryptonSTD::addFunction(const string &name, const std::function<void(Environment *)>& nativeFunction, optional<const Type*> returnType,
                             const vector<pair<string, optional<const Type*>>>& parameters) {
    auto value = Value(Primitive::FUNC, new LambdaExpression(returnType, parameters, nativeFunction));
    _env.define(&Primitive::FUNC, name, value);
}

void KryptonSTD::addFunction(const string &name, const function<void(Environment *)> &nativeFunction,
                             const vector<pair<string, optional<const Type *>>> &parameters) {
    auto value = Value(Primitive::FUNC, new LambdaExpression(parameters, nativeFunction));
    _env.define(&Primitive::FUNC, name, value);
}

void KryptonSTD::load(Environment &env) {
    KryptonSTD kryptonSTD(env);
    kryptonSTD.load();
}
