// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Primitive.h>
#include <types/Type.h>
#include <types/Value.h>

const FunctionSignature CHAR_boolConstructorSignature(&Primitive::CHAR, {&Primitive::BOOL});
const FunctionSignature CHAR_intConstructorSignature(&Primitive::CHAR, {&Primitive::INT});
const FunctionSignature CHAR_decConstructorSignature(&Primitive::CHAR, {&Primitive::DEC});

const FunctionSignature CHAR_comparisonSignature(&Primitive::BOOL, {&Primitive::CHAR, &Primitive::CHAR});
const FunctionSignature CHAR_binarySignature(&Primitive::CHAR, {&Primitive::CHAR, &Primitive::CHAR});

const FunctionSignature CHAR_binarySignatureInt(&Primitive::CHAR, {&Primitive::CHAR, &Primitive::INT});
const FunctionSignature CHAR_binarySignatureDec(&Primitive::CHAR, {&Primitive::CHAR, &Primitive::DEC});

Value CHAR_constructFromBool(const vector<Value>& parameters)
{
    unsigned char value = parameters[0].getValue<bool>();
    return {Primitive::CHAR, value};
}

Value CHAR_constructFromInt(const vector<Value>& parameters)
{
    unsigned char value = parameters[0].getValue<int>();
    return {Primitive::CHAR, value};
}

Value CHAR_constructFromDec(const vector<Value>& parameters)
{
    unsigned char value = (int) parameters[0].getValue<double>();
    return {Primitive::CHAR, value};
}

Value CHAR_compare(const Value& left, const Value& right)
{
    unsigned char leftChar = left.getValue<unsigned char>();
    unsigned char rightChar = right.getValue<unsigned char>();
    bool result = leftChar > rightChar;
    return {Primitive::BOOL, result};
}

Value CHAR_isEqual(const Value& left, const Value& right)
{
    unsigned char leftChar = left.getValue<unsigned char>();
    unsigned char rightChar = right.getValue<unsigned char>();
    bool result = leftChar == rightChar;
    return {Primitive::BOOL, result};
}

Value CHAR_add(const Value& left, const Value& right)
{
    unsigned char leftChar = left.getValue<unsigned char>();
    unsigned char rightChar = right.getValue<unsigned char>();
    unsigned char result = leftChar + rightChar;
    return {Primitive::CHAR, result};
}

Value CHAR_subtract(const Value& left, const Value& right)
{
    unsigned char leftChar = left.getValue<unsigned char>();
    unsigned char rightChar = right.getValue<unsigned char>();
    unsigned char result = leftChar - rightChar;
    return {Primitive::CHAR, result};
}

Value CHAR_multiply(const Value& left, const Value& right)
{
    unsigned char leftChar = left.getValue<unsigned char>();
    unsigned char rightChar = right.getValue<unsigned char>();
    unsigned char result = leftChar * rightChar;
    return {Primitive::CHAR, result};
}

Value CHAR_divide(const Value& left, const Value& right)
{
    unsigned char leftChar = left.getValue<unsigned char>();
    unsigned char rightChar = right.getValue<unsigned char>();
    unsigned char result = leftChar / rightChar;
    return {Primitive::CHAR, result};
}

Value CHAR_addInt(const Value& left, const Value& right)
{
    Value leftInt = left.getType().construct({left});
    Value result = left.getType().binaryOperation(
            Operation::Binary::PLUS,
            leftInt, right);
    return result;
}

Value CHAR_subtractInt(const Value& left, const Value& right)
{
    Value leftInt = right.getType().construct({left});
    Value result = right.getType().binaryOperation(
            Operation::Binary::MINUS,
            leftInt, right);
    return result;
}

Value CHAR_multiplyInt(const Value& left, const Value& right)
{
    Value leftInt = right.getType().construct({left});
    Value result = right.getType().binaryOperation(
            Operation::Binary::ASTERISK,
            leftInt, right);
    return result;
}

Value CHAR_divideInt(const Value& left, const Value& right)
{
    Value leftInt = right.getType().construct({left});
    Value result = right.getType().binaryOperation(
            Operation::Binary::SLASH,
            leftInt, right);
    return result;
}

Value CHAR_addDec(const Value& left, const Value& right)
{
    Value leftDec = left.getType().construct({left});
    Value result = left.getType().binaryOperation(
            Operation::Binary::PLUS,
            leftDec, right);
    return result;
}

Value CHAR_subtractDec(const Value& left, const Value& right)
{
    Value leftDec = right.getType().construct({left});
    Value result = right.getType().binaryOperation(
            Operation::Binary::MINUS,
            leftDec, right);
    return result;
}

Value CHAR_multiplyDec(const Value& left, const Value& right)
{
    Value leftDec = right.getType().construct({left});
    Value result = right.getType().binaryOperation(
            Operation::Binary::ASTERISK,
            leftDec, right);
    return result;
}

Value CHAR_divideDec(const Value& left, const Value& right)
{
    Value leftDec = right.getType().construct({left});
    Value result = right.getType().binaryOperation(
            Operation::Binary::SLASH,
            leftDec, right);
    return result;
}

const Type Primitive::CHAR = Type
(
    {
        {CHAR_boolConstructorSignature, CHAR_constructFromBool},
        {CHAR_intConstructorSignature, CHAR_constructFromInt},
        {CHAR_decConstructorSignature, CHAR_constructFromDec}
    },
    {CHAR_comparisonSignature, CHAR_compare},
    {CHAR_comparisonSignature, CHAR_isEqual},
    {
            {Operation::Binary::PLUS, {
                {CHAR_binarySignature, CHAR_add},
                {CHAR_binarySignatureInt, CHAR_addInt},
                {CHAR_binarySignatureDec, CHAR_addDec}
            }},
            {Operation::Binary::MINUS, {
                {CHAR_binarySignature, CHAR_subtract},
                {CHAR_binarySignatureInt, CHAR_subtractInt},
                {CHAR_binarySignatureDec, CHAR_subtractDec}
            }},
            {Operation::Binary::ASTERISK, {
                {CHAR_binarySignature, CHAR_multiply},
                {CHAR_binarySignatureInt, CHAR_multiplyInt},
                {CHAR_binarySignatureDec, CHAR_multiplyDec}
            }},
            {Operation::Binary::SLASH, {
                {CHAR_binarySignature, CHAR_divide},
                {CHAR_binarySignatureInt, CHAR_divideInt},
                {CHAR_binarySignatureDec, CHAR_divideDec}
            }}
    },
    {},
    {},
    {}
);


