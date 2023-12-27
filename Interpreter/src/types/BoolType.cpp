// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Primitive.h>
#include <types/Type.h>
#include <types/Value.h>

namespace BoolType
{
    Value compare(const Value& left, const Value& right)
    {
        bool result = true;
        return {Primitive::BOOL, result};
    }
}

const Type Primitive::BOOL = Type
(
    {},
    {FunctionSignature(&Primitive::BOOL, {&Primitive::BOOL, &Primitive::BOOL}), BoolType::compare},
    {FunctionSignature(&Primitive::BOOL, {&Primitive::BOOL, &Primitive::BOOL}), BoolType::compare},
    {},
    {},
    {},
    {}
);


