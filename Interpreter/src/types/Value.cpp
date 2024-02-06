// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Value.h>
#include <common/Logger.h>
#include <nodes/FunctionNodes.h>

Value::Value(const Type& type, PrimitiveValue value)
    : _type(type)
{
    Logger::debug("Value::Value - primitive value\n");
    _primitiveValue = value;
}

//Value::Value(const Type& type, unordered_map<string, Value> value)
//    : _type(type)
//{
//    Logger::debug("Value::Value - field value\n");
//    _fieldValue = std::move(value);
//}

Value::~Value()
{
    Logger::debug("Value::~Value\n");
}

const Type& Value::getType() const
{
    return _type;
}

Value Value::getField(const string& name) const
{
    Logger::debug("Value::getField\n");
    return _fieldValue.at(name);
}

