// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Primitive.h>
#include <types/Type.h>
#include <types/Value.h>

namespace IntType
{
    Value compare(const Value& left, const Value& right)
    {
        bool result = true;
        return {Primitive::BOOL, result};
    }
}

const Type Primitive::INT = Type
(
    {},
    {FunctionSignature(&Primitive::BOOL, {&Primitive::INT, &Primitive::INT}), IntType::compare},
    {FunctionSignature(&Primitive::BOOL, {&Primitive::INT, &Primitive::INT}), IntType::compare},
    {},
    {},
    {},
    {}
);


