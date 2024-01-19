// Copyright (c) 2023 Krypton. All rights reserved.
#include <runtime/Environment.h>

Environment::Environment() : _handler(ErrorHandler::getInstance()) {}

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

void Environment::define(const Type& type, const string& name, Value value)
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
    try { return _values.at(name).value; }
    catch (const std::out_of_range& e)
    {
        _handler.undefinedVariable(name);
        _handler.terminateIfErrors();
        throw e;
    }
}

void Environment::assign(const string& name, Value value)
{
    if (!_values.contains(name))
    {
        _handler.undefinedVariable(name);
        _handler.terminateIfErrors();
    }
    Variable& variable = _values.at(name);
    if (&variable.type != &value.getType())
    {
        _handler.typeMismatch(name, variable.type, value.getType());
        _handler.terminateIfErrors();
    }
    delete variable.value;
    variable.value = new Value(value);
}
