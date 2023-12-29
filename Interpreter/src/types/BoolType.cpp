// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Primitive.h>
#include <types/Type.h>
#include <types/Value.h>

Value BOOL_compare(const Value& left, const Value& right)
{
    bool leftBool = left.getValue<bool>();
    bool rightBool = right.getValue<bool>();
    bool result = leftBool > rightBool;
    return {Primitive::BOOL, result};
}

Value BOOL_isEqual(const Value& left, const Value& right)
{
    bool leftBool = left.getValue<bool>();
    bool rightBool = right.getValue<bool>();
    bool result = leftBool == rightBool;
    return {Primitive::BOOL, result};
}

const Type Primitive::BOOL = Type
(
    {},
    {FunctionSignature(&Primitive::BOOL, {&Primitive::BOOL, &Primitive::BOOL}), BOOL_compare},
    {FunctionSignature(&Primitive::BOOL, {&Primitive::BOOL, &Primitive::BOOL}), BOOL_isEqual},
    {},
    {},
    {},
    {}
);


