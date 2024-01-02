// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Primitive.h>
#include <types/Type.h>
#include <types/Value.h>

const FunctionSignature DEC_boolConstructorSignature(&Primitive::DEC, {&Primitive::BOOL});
const FunctionSignature DEC_intConstructorSignature(&Primitive::DEC, {&Primitive::INT});
const FunctionSignature DEC_charConstructorSignature(&Primitive::DEC, {&Primitive::CHAR});

const FunctionSignature DEC_comparisonSignature(&Primitive::BOOL, {&Primitive::DEC, &Primitive::DEC});
const FunctionSignature DEC_binarySignature(&Primitive::DEC, {&Primitive::DEC, &Primitive::DEC});
const FunctionSignature DEC_unarySignature(&Primitive::DEC, {&Primitive::DEC});

const FunctionSignature DEC_binarySignatureInt(&Primitive::DEC, {&Primitive::DEC, &Primitive::INT});
const FunctionSignature DEC_binarySignatureChar(&Primitive::DEC, {&Primitive::DEC, &Primitive::CHAR});

Value DEC_constructFromBool(const vector<Value>& parameters)
{
    double value = parameters[0].getValue<bool>();
    return {Primitive::DEC, value};
}

Value DEC_constructFromInt(const vector<Value>& parameters)
{
    double value = parameters[0].getValue<int>();
    return {Primitive::DEC, value};
}

Value DEC_constructFromChar(const vector<Value>& parameters)
{
    double value = parameters[0].getValue<unsigned char>();
    return {Primitive::DEC, value};
}

Value DEC_compare(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    double rightDec = right.getValue<double>();
    bool result = leftDec > rightDec;
    return {Primitive::BOOL, result};
}

Value DEC_isEqual(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    double rightDec = right.getValue<double>();
    bool result = leftDec == rightDec;
    return {Primitive::BOOL, result};
}

Value DEC_add(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    double rightDec = right.getValue<double>();
    double result = leftDec + rightDec;
    return {Primitive::DEC, result};
}

Value DEC_subtract(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    double rightDec = right.getValue<double>();
    double result = leftDec - rightDec;
    return {Primitive::DEC, result};
}

Value DEC_multiply(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    double rightDec = right.getValue<double>();
    double result = leftDec * rightDec;
    return {Primitive::DEC, result};
}

Value DEC_divide(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    double rightDec = right.getValue<double>();
    double result = leftDec / rightDec;
    return {Primitive::DEC, result};
}

Value DEC_negate(const Value& value)
{
    double result = -value.getValue<double>();
    return {Primitive::DEC, result};
}

Value DEC_addInt(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    int rightInt = right.getValue<int>();
    double result = leftDec + rightInt;
    return {Primitive::DEC, result};
}

Value DEC_subtractInt(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    int rightInt = right.getValue<int>();
    double result = leftDec - rightInt;
    return {Primitive::DEC, result};
}

Value DEC_multiplyInt(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    int rightInt = right.getValue<int>();
    double result = leftDec * rightInt;
    return {Primitive::DEC, result};
}

Value DEC_divideInt(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    int rightInt = right.getValue<int>();
    double result = leftDec / rightInt;
    return {Primitive::DEC, result};
}

Value DEC_addChar(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    unsigned char rightChar = right.getValue<unsigned char>();
    double result = leftDec + rightChar;
    return {Primitive::DEC, result};
}

Value DEC_subtractChar(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    unsigned char rightChar = right.getValue<unsigned char>();
    double result = leftDec - rightChar;
    return {Primitive::DEC, result};
}

Value DEC_multiplyChar(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    unsigned char rightChar = right.getValue<unsigned char>();
    double result = leftDec * rightChar;
    return {Primitive::DEC, result};
}

Value DEC_divideChar(const Value& left, const Value& right)
{
    double leftDec = left.getValue<double>();
    unsigned char rightChar = right.getValue<unsigned char>();
    double result = leftDec / rightChar;
    return {Primitive::DEC, result};
}

const Type Primitive::DEC = Type
(
    {
        {DEC_boolConstructorSignature, DEC_constructFromBool},
        {DEC_intConstructorSignature, DEC_constructFromInt},
        {DEC_charConstructorSignature, DEC_constructFromChar}
    },
    {DEC_comparisonSignature, DEC_compare},
    {DEC_comparisonSignature, DEC_isEqual},
    {
            {Operation::Binary::PLUS, {
                {DEC_binarySignature, DEC_add},
                {DEC_binarySignatureInt, DEC_addInt},
                {DEC_binarySignatureChar, DEC_addChar}
            }},
            {Operation::Binary::MINUS, {
                {DEC_binarySignature, DEC_subtract},
                {DEC_binarySignatureInt, DEC_subtractInt},
                {DEC_binarySignatureChar, DEC_subtractChar}
            }},
            {Operation::Binary::ASTERISK, {
                {DEC_binarySignature, DEC_multiply},
                {DEC_binarySignatureInt, DEC_multiplyInt},
                {DEC_binarySignatureChar, DEC_multiplyChar}
            }},
            {Operation::Binary::SLASH, {
                {DEC_binarySignature, DEC_divide},
                {DEC_binarySignatureInt, DEC_divideInt},
                {DEC_binarySignatureChar, DEC_divideChar}
            }}
    },
    {
            {Operation::Unary::MINUS, {DEC_unarySignature, DEC_negate}}
    },
    {},
    {}
);


