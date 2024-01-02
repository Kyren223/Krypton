// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Primitive.h>
#include <types/Type.h>
#include <types/Value.h>

const FunctionSignature BOOL_binarySignature(&Primitive::BOOL, {&Primitive::BOOL, &Primitive::BOOL});
const FunctionSignature BOOL_unarySignature(&Primitive::BOOL, {&Primitive::BOOL});

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

Value BOOL_not(const Value& value)
{
    bool boolValue = value.getValue<bool>();
    bool result = !boolValue;
    return {Primitive::BOOL, result};
}

const Type Primitive::BOOL = Type
(
    {},
    {BOOL_binarySignature, BOOL_compare},
    {BOOL_binarySignature, BOOL_isEqual},
    {},
    {
            {Operation::Unary::BANG, {BOOL_unarySignature, BOOL_not}}
    },
    {},
    {}
);


