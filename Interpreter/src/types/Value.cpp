// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Value.h>
#include <common/Logger.h>

Value::Value(const Type& type, PrimitiveValue value)
    : _type(type)
{
    Logger::debug("Value::Value - primitive value");
    _primitiveValue = value;
}

Value::Value(const Type& type, unordered_map<string, Value> value)
    : _type(type)
{
    Logger::debug("Value::Value - field value");
    _fieldValue = std::move(value);
}

Value::~Value()
{
    Logger::debug("Value::~Value");
}

const Type& Value::getType() const
{
    return _type;
}

Value Value::getField(const string& name) const
{
    Logger::debug("Value::getField");
    return _fieldValue.at(name);
}


template<typename T>
optional<T> Value::getValue() const
{
    Logger::debug("Value::getValue");
    return std::holds_alternative<T>() ? std::get<T>(_primitiveValue) : std::nullopt;
}

