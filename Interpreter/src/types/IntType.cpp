// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Primitive.h>
#include <types/Type.h>
#include <types/Value.h>

const FunctionSignature INT_boolConstructorSignature(&Primitive::INT, {&Primitive::BOOL});
const FunctionSignature INT_comparisonSignature(&Primitive::BOOL, {&Primitive::INT, &Primitive::INT});
const FunctionSignature INT_binarySignature(&Primitive::INT, {&Primitive::INT, &Primitive::INT});
const FunctionSignature INT_unarySignature(&Primitive::INT, {&Primitive::INT});

Value INT_construct(const vector<Value>& parameters)
{
    // int(bool)
    int value = parameters[0].getValue<bool>();
    return {Primitive::INT, value};
}

Value INT_compare(const Value& left, const Value& right)
{
    int leftInt = left.getValue<int>();
    int rightInt = right.getValue<int>();
    bool result = leftInt > rightInt;
    return {Primitive::BOOL, result};
}

Value INT_isEqual(const Value& left, const Value& right)
{
    int leftInt = left.getValue<int>();
    int rightInt = right.getValue<int>();
    bool result = leftInt == rightInt;
    return {Primitive::BOOL, result};
}

Value INT_add(const Value& left, const Value& right)
{
    int leftInt = left.getValue<int>();
    int rightInt = right.getValue<int>();
    int result = leftInt + rightInt;
    return {Primitive::INT, result};
}

Value INT_subtract(const Value& left, const Value& right)
{
    int leftInt = left.getValue<int>();
    int rightInt = right.getValue<int>();
    int result = leftInt - rightInt;
    return {Primitive::INT, result};
}

Value INT_multiply(const Value& left, const Value& right)
{
    int leftInt = left.getValue<int>();
    int rightInt = right.getValue<int>();
    int result = leftInt * rightInt;
    return {Primitive::INT, result};
}

Value INT_divide(const Value& left, const Value& right)
{
    int leftInt = left.getValue<int>();
    int rightInt = right.getValue<int>();
    int result = leftInt / rightInt;
    return {Primitive::INT, result};
}

Value INT_negate(const Value& value)
{
    int result = -value.getValue<int>();
    return {Primitive::INT, result};
}

Value INT_increment(const Value& value)
{
    int result = value.getValue<int>() + 1;
    return {Primitive::INT, result};
}

Value INT_decrement(const Value& value)
{
    int result = value.getValue<int>() - 1;
    return {Primitive::INT, result};
}


const Type Primitive::INT = Type
(
    {{INT_boolConstructorSignature, INT_construct}},
    {INT_comparisonSignature, INT_compare},
    {INT_comparisonSignature, INT_isEqual},
    {
            {Operation::Binary::PLUS, {{    INT_binarySignature, INT_add}}},
            {Operation::Binary::MINUS, {{   INT_binarySignature, INT_subtract}}},
            {Operation::Binary::ASTERISK, {{INT_binarySignature, INT_multiply}}},
            {Operation::Binary::SLASH, {{   INT_binarySignature, INT_divide}}}
        },
    {
            {Operation::Unary::MINUS, {INT_unarySignature, INT_negate}},
            {Operation::Unary::PLUS_PLUS, {INT_unarySignature, INT_increment}},
            {Operation::Unary::MINUS_MINUS, {INT_unarySignature, INT_decrement}}
    },
    {},
    {}
);


