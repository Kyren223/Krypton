// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Primitive.h>
#include <types/Type.h>
#include <types/Value.h>

namespace Char
{
    const FunctionSignature boolConstructorSignature(&Primitive::CHAR, {&Primitive::BOOL});
    const FunctionSignature intConstructorSignature(&Primitive::CHAR, {&Primitive::INT});
    const FunctionSignature decConstructorSignature(&Primitive::CHAR, {&Primitive::DEC});
    
    const FunctionSignature comparisonSignature(&Primitive::BOOL, {&Primitive::CHAR, &Primitive::CHAR});
    const FunctionSignature binarySignature(&Primitive::CHAR, {&Primitive::CHAR, &Primitive::CHAR});
    
    const FunctionSignature binarySignatureInt(&Primitive::CHAR, {&Primitive::CHAR, &Primitive::INT});
    const FunctionSignature binarySignatureDec(&Primitive::CHAR, {&Primitive::CHAR, &Primitive::DEC});
    const FunctionSignature binarySignatureStr(&Primitive::STR, {&Primitive::CHAR, &Primitive::STR});
    
    Value constructFromBool(const vector<Value>& parameters)
    {
        unsigned char value = parameters[0].getValue<bool>();
        return {Primitive::CHAR, value};
    }
    
    Value constructFromInt(const vector<Value>& parameters)
    {
        unsigned char value = parameters[0].getValue<int>();
        return {Primitive::CHAR, value};
    }
    
    Value constructFromDec(const vector<Value>& parameters)
    {
        unsigned char value = (int) parameters[0].getValue<double>();
        return {Primitive::CHAR, value};
    }
    
    Value compare(const Value& left, const Value& right)
    {
        unsigned char leftChar = left.getValue<unsigned char>();
        unsigned char rightChar = right.getValue<unsigned char>();
        bool result = leftChar > rightChar;
        return {Primitive::BOOL, result};
    }
    
    Value isEqual(const Value& left, const Value& right)
    {
        unsigned char leftChar = left.getValue<unsigned char>();
        unsigned char rightChar = right.getValue<unsigned char>();
        bool result = leftChar == rightChar;
        return {Primitive::BOOL, result};
    }
    
    Value add(const Value& left, const Value& right)
    {
        unsigned char leftChar = left.getValue<unsigned char>();
        unsigned char rightChar = right.getValue<unsigned char>();
        unsigned char result = leftChar + rightChar;
        return {Primitive::CHAR, result};
    }
    
    Value subtract(const Value& left, const Value& right)
    {
        unsigned char leftChar = left.getValue<unsigned char>();
        unsigned char rightChar = right.getValue<unsigned char>();
        unsigned char result = leftChar - rightChar;
        return {Primitive::CHAR, result};
    }
    
    Value multiply(const Value& left, const Value& right)
    {
        unsigned char leftChar = left.getValue<unsigned char>();
        unsigned char rightChar = right.getValue<unsigned char>();
        unsigned char result = leftChar * rightChar;
        return {Primitive::CHAR, result};
    }
    
    Value divide(const Value& left, const Value& right)
    {
        unsigned char leftChar = left.getValue<unsigned char>();
        unsigned char rightChar = right.getValue<unsigned char>();
        unsigned char result = leftChar / rightChar;
        return {Primitive::CHAR, result};
    }
    
    Value addInt(const Value& left, const Value& right)
    {
        Value leftInt = left.getType().construct({left});
        Value result = left.getType().binaryOperation(
                Operation::Binary::PLUS,
                leftInt, right);
        return result;
    }
    
    Value subtractInt(const Value& left, const Value& right)
    {
        Value leftInt = right.getType().construct({left});
        Value result = right.getType().binaryOperation(
                Operation::Binary::MINUS,
                leftInt, right);
        return result;
    }
    
    Value multiplyInt(const Value& left, const Value& right)
    {
        Value leftInt = right.getType().construct({left});
        Value result = right.getType().binaryOperation(
                Operation::Binary::ASTERISK,
                leftInt, right);
        return result;
    }
    
    Value divideInt(const Value& left, const Value& right)
    {
        Value leftInt = right.getType().construct({left});
        Value result = right.getType().binaryOperation(
                Operation::Binary::SLASH,
                leftInt, right);
        return result;
    }
    
    Value addDec(const Value& left, const Value& right)
    {
        Value leftDec = left.getType().construct({left});
        Value result = left.getType().binaryOperation(
                Operation::Binary::PLUS,
                leftDec, right);
        return result;
    }
    
    Value subtractDec(const Value& left, const Value& right)
    {
        Value leftDec = right.getType().construct({left});
        Value result = right.getType().binaryOperation(
                Operation::Binary::MINUS,
                leftDec, right);
        return result;
    }
    
    Value multiplyDec(const Value& left, const Value& right)
    {
        Value leftDec = right.getType().construct({left});
        Value result = right.getType().binaryOperation(
                Operation::Binary::ASTERISK,
                leftDec, right);
        return result;
    }
    
    Value divideDec(const Value& left, const Value& right)
    {
        Value leftDec = right.getType().construct({left});
        Value result = right.getType().binaryOperation(
                Operation::Binary::SLASH,
                leftDec, right);
        return result;
    }
    
    Value addStr(const Value& left, const Value& right)
    {
        unsigned char leftChar = left.getValue<unsigned char>();
        string rightStr = right.getValue<string>();
        string result = std::to_string(leftChar) + rightStr;
        return {Primitive::STR, result};
    }
}

const Type Primitive::CHAR = Type
(
    "char",
    {
        {Char::boolConstructorSignature, Char::constructFromBool},
        {Char::intConstructorSignature, Char::constructFromInt},
        {Char::decConstructorSignature, Char::constructFromDec}
    },
    {Char::comparisonSignature, Char::compare},
    {Char::comparisonSignature, Char::isEqual},
    {
            {Operation::Binary::PLUS, {
                {Char::binarySignature, Char::add},
                {Char::binarySignatureInt, Char::addInt},
                {Char::binarySignatureDec, Char::addDec},
                {Char::binarySignatureStr, Char::addStr}
            }},
            {Operation::Binary::MINUS, {
                {Char::binarySignature, Char::subtract},
                {Char::binarySignatureInt, Char::subtractInt},
                {Char::binarySignatureDec, Char::subtractDec}
            }},
            {Operation::Binary::ASTERISK, {
                {Char::binarySignature, Char::multiply},
                {Char::binarySignatureInt, Char::multiplyInt},
                {Char::binarySignatureDec, Char::multiplyDec}
            }},
            {Operation::Binary::SLASH, {
                {Char::binarySignature, Char::divide},
                {Char::binarySignatureInt, Char::divideInt},
                {Char::binarySignatureDec, Char::divideDec}
            }}
    },
    {},
    {},
    {}
);


