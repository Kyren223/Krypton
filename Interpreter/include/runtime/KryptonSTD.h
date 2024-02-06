// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <runtime/Environment.h>

class KryptonSTD {
    Environment _env;
    bool _loaded = false;

    void load();
    void addFunction(const string& name, std::function<void(Environment*)>, const Type* returnType, vector<pair<string, const Type*>> parameters);
public:
    static const KryptonSTD& getInstance() {
        static KryptonSTD instance;
        if (!instance._loaded)
        {
            instance.load();
            instance._loaded = true;
        }
        return instance;
    }

    const Environment& getEnvironment() const {
        return _env;
    }

};
