// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <types/Type.h>
#include <variant>

using std::variant;

class LambdaExpression; // Forward declaration

using PrimitiveValue = variant<int, double, bool, unsigned char, string, const LambdaExpression*>;

class Value
{
    const Type& _type;
    PrimitiveValue _primitiveValue;
    unordered_map<string, Value> _fieldValue;
    
public:
    Value(const Type&  type, PrimitiveValue value);
    ~Value();
    
    [[nodiscard]] const Type& getType() const;
    [[nodiscard]] Value getField(const string& name) const;
    template<typename T>
    [[nodiscard]] T getValue() const
    {
        return std::get<T>(_primitiveValue);
    }
};
