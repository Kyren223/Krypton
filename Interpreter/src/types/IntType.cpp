// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Primitive.h>
#include <types/Type.h>
#include <types/Value.h>

const FunctionSignature INT_boolConstructorSignature(&Primitive::INT, {&Primitive::BOOL});
const FunctionSignature INT_decConstructorSignature(&Primitive::INT, {&Primitive::BOOL});
const FunctionSignature INT_charConstructorSignature(&Primitive::INT, {&Primitive::CHAR});

const FunctionSignature INT_comparisonSignature(&Primitive::BOOL, {&Primitive::INT, &Primitive::INT});
const FunctionSignature INT_binarySignature(&Primitive::INT, {&Primitive::INT, &Primitive::INT});
const FunctionSignature INT_unarySignature(&Primitive::INT, {&Primitive::INT});

const FunctionSignature INT_binarySignatureDec(&Primitive::DEC, {&Primitive::INT, &Primitive::DEC});
const FunctionSignature INT_binarySignatureChar(&Primitive::INT, {&Primitive::INT, &Primitive::CHAR});

Value INT_constructFromBool(const vector<Value>& parameters)
{
    int value = parameters[0].getValue<bool>();
    return {Primitive::INT, value};
}

Value INT_constructFromDec(const vector<Value>& parameters)
{
    int value = (int) parameters[0].getValue<double>();
    return {Primitive::INT, value};
}

Value INT_constructFromChar(const vector<Value>& parameters)
{
    int value = parameters[0].getValue<unsigned char>();
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

Value INT_addDec(const Value& left, const Value& right)
{
    Value leftDec = right.getType().construct({left});
    Value result = right.getType().binaryOperation(
            Operation::Binary::PLUS,
            leftDec, right);
    return result;
}

Value INT_subtractDec(const Value& left, const Value& right)
{
    Value leftDec = right.getType().construct({left});
    Value result = right.getType().binaryOperation(
            Operation::Binary::MINUS,
            leftDec, right);
    return result;
}

Value INT_multiplyDec(const Value& left, const Value& right)
{
    Value leftDec = right.getType().construct({left});
    Value result = right.getType().binaryOperation(
            Operation::Binary::ASTERISK,
            leftDec, right);
    return result;
}

Value INT_divideDec(const Value& left, const Value& right)
{
    Value leftDec = right.getType().construct({left});
    Value result = right.getType().binaryOperation(
            Operation::Binary::SLASH,
            leftDec, right);
    return result;
}

Value INT_addChar(const Value& left, const Value& right)
{
    int leftInt = left.getValue<int>();
    unsigned char rightChar = right.getValue<unsigned char>();
    int result = leftInt + rightChar;
    return {Primitive::INT, result};
}

Value INT_subtractChar(const Value& left, const Value& right)
{
    int leftInt = left.getValue<int>();
    unsigned char rightChar = right.getValue<unsigned char>();
    int result = leftInt - rightChar;
    return {Primitive::INT, result};
}

Value INT_multiplyChar(const Value& left, const Value& right)
{
    int leftInt = left.getValue<int>();
    unsigned char rightChar = right.getValue<unsigned char>();
    int result = leftInt * rightChar;
    return {Primitive::INT, result};
}

Value INT_divideChar(const Value& left, const Value& right)
{
    int leftInt = left.getValue<int>();
    unsigned char rightChar = right.getValue<unsigned char>();
    int result = leftInt / rightChar;
    return {Primitive::INT, result};
}

const Type Primitive::INT = Type
(
    {
        {INT_boolConstructorSignature, INT_constructFromBool},
        {INT_decConstructorSignature, INT_constructFromDec},
        {INT_charConstructorSignature, INT_constructFromChar}
    },
    {INT_comparisonSignature, INT_compare},
    {INT_comparisonSignature, INT_isEqual},
    {
            {Operation::Binary::PLUS, {
                {INT_binarySignature, INT_add},
                {INT_binarySignatureDec, INT_addDec},
                {INT_binarySignatureChar, INT_addChar}
            }},
            {Operation::Binary::MINUS, {
                {INT_binarySignature, INT_subtract},
                {INT_binarySignatureDec, INT_subtractDec},
                {INT_binarySignatureChar, INT_subtractChar}
            }},
            {Operation::Binary::ASTERISK, {
                {INT_binarySignature, INT_multiply},
                {INT_binarySignatureDec, INT_multiplyDec},
                {INT_binarySignatureChar, INT_multiplyChar}
            }},
            {Operation::Binary::SLASH, {
                {INT_binarySignature, INT_divide},
                {INT_binarySignatureDec, INT_divideDec},
                {INT_binarySignatureChar, INT_divideChar}
            }}
        },
    {
            {Operation::Unary::MINUS, {INT_unarySignature, INT_negate}}
    },
    {},
    {}
);


