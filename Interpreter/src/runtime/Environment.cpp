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
        if (name == "return") continue;
        delete variable.value;
    }
    if (_parent == nullptr) return;
    if (getReturnValue(false).has_value()) _parent->setReturnValue(getReturnValue(true).value());
}

void Environment::define(optional<const Type*> type, const string& name)
{
    if (_values.contains(name))
    {
        _handler.redefinedVariable(name);
        _handler.terminateIfErrors();
    }
    _values.emplace(name, Variable{type, nullptr});
}

void Environment::define(optional<const Type*> type, const string& name, const Value& value)
{
    if (_values.contains(name))
    {
        _handler.redefinedVariable(name);
        _handler.terminateIfErrors();
    }
    if (type.has_value() && type.value() != &value.getType())
    {
        _handler.typeMismatch(name, type, value.getType());
        _handler.terminateIfErrors();
    }
    _values.emplace(name, Variable{type, new Value(value)});
}

const Value* Environment::get(const string& name) const
{
    auto var = _values.find(name);
    
    // Variable exists in this environment
    if (var != _values.end()) return var->second.value;
    
    // Try to find variable in parent environment
    if (_parent != nullptr) return _parent->get(name);
    
    _handler.undefinedVariable(name);
    _handler.terminateIfErrors();
}

void Environment::assign(const string& name, const Value& value)
{
    auto var = _values.find(name);
    
    // Variable exists in this environment
    if (var != _values.end())
    {
        Variable& variable = var->second;
        if (variable.type.has_value() && variable.type.value() != &value.getType())
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

void Environment::setReturnValue(optional<Value> value) {
    _values["return"] = Variable{nullptr, value.has_value() ? new Value(value.value()) : nullptr};
}

optional<optional<Value>> Environment::getReturnValue(bool remove) {
    if (_values.contains("return"))
    {
        const Value* value = _values.at("return").value;
        optional<Value> returnValue = value != nullptr ? optional<Value>(*value) : std::nullopt;
        if (remove)
        {
            _values.erase("return");
            delete value;
        }
        return returnValue;
    }
    return {};
}

