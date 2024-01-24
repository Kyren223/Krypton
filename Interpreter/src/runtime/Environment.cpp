// Copyright (c) 2023 Krypton. All rights reserved.
#include <runtime/Environment.h>

Environment::Environment()
    : _handler(ErrorHandler::getInstance())
    , _parent(nullptr) {}

Environment::Environment(Environment& parent)
    : _handler(ErrorHandler::getInstance())
    , _parent(&parent) {}

Environment::~Environment()
{
    for (auto& [name, variable] : _values)
    {
        delete variable.value;
    }
}

void Environment::define(const Type& type, const string& name)
{
    if (_values.contains(name))
    {
        _handler.redefinedVariable(name);
        _handler.terminateIfErrors();
    }
    _values.emplace(name, Variable{type, nullptr});
}

void Environment::define(const Type& type, const string& name, const Value& value)
{
    if (_values.contains(name))
    {
        _handler.redefinedVariable(name);
        _handler.terminateIfErrors();
    }
    _values.emplace(name, Variable{type, new Value(value)});
}

Value* Environment::get(const string& name) const
{
    auto var = _values.find(name);
    
    // Variable exists in this environment
    if (var != _values.end()) return var->second.value;
    
    // Try to find variable in parent environment
    if (_parent != nullptr) return _parent->get(name);
    
    _handler.undefinedVariable(name);
    _handler.terminateIfErrors();
}

void Environment::assign(const string& name, Value value)
{
    auto var = _values.find(name);
    
    // Variable exists in this environment
    if (var != _values.end())
    {
        Variable& variable = var->second;
        if (&variable.type != &value.getType())
        {
            _handler.typeMismatch(name, variable.type, value.getType());
            _handler.terminateIfErrors();
        }
        delete variable.value;
        variable.value = new Value(value);
        return;
    }
    
    // Try to find variable in parent environment
    if (_parent != nullptr)
    {
        _parent->assign(name, value);
        return;
    }
    
    _handler.undefinedVariable(name);
    _handler.terminateIfErrors();
}
