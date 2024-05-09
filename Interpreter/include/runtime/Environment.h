// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <unordered_map>
#include <string>
#include <types/Value.h>
#include <common/ErrorHandler.h>

using std::unordered_map, std::string;

struct Variable
{
    optional<const Type*> type;
    const Value* value{};
};

class Environment
{
    unordered_map<string, Variable> _values;
    ErrorHandler& _handler;
    Environment* _parent;
    
public:
    Environment();
    Environment(Environment& parent);
    ~Environment();
    
    void define(optional<const Type*> type, const string& name);
    void define(optional<const Type*> type, const string& name, const Value& value);
    void assign(const string& name, const Value& value);
    const Value* get(const string& name) const;

    void setReturnValue(optional<Value> value);
    optional<optional<Value>> getReturnValue(bool remove);
};
