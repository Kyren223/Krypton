// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <types/Type.h>
#include <optional>
#include <any>
#include <memory>

using std::optional, std::shared_ptr;

using PrimitiveValue = variant<int, double, bool, unsigned char>;

class Value
{
    const Type& _type;
    PrimitiveValue _primitiveValue;
    unordered_map<string, Value> _fieldValue;
    
public:
    Value(const Type&  type, PrimitiveValue value);
    Value(const Type&  type, unordered_map<string, Value> value);
    ~Value();
    
    [[nodiscard]] const Type& getType() const;
    template<typename T>
    [[nodiscard]] optional<T> getValue() const;
    [[nodiscard]] Value getField(const string& name) const;
};
