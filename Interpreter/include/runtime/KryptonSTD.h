// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <runtime/Environment.h>

class KryptonSTD {
    Environment& _env;

    explicit KryptonSTD(Environment& env) : _env(env) {}
    void load();
    void addFunction(const string& name, const std::function<void(Environment*)>& nativeFunction, optional<const Type*> returnType, const vector<pair<string, optional<const Type*>>>& parameters);
    void addFunction(const string& name, const std::function<void(Environment*)>& nativeFunction, const vector<pair<string, optional<const Type*>>>& parameters);
public:
    static void load(Environment& env);
};
