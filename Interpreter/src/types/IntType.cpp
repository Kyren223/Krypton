// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Primitive.h>
#include <types/Type.h>
#include <types/Value.h>

namespace Int
{
    const FunctionSignature boolConstructorSignature(&Primitive::INT, {&Primitive::BOOL});
    const FunctionSignature decConstructorSignature(&Primitive::INT, {&Primitive::DEC});
    const FunctionSignature charConstructorSignature(&Primitive::INT, {&Primitive::CHAR});
    
    const FunctionSignature comparisonSignature(&Primitive::BOOL, {&Primitive::INT, &Primitive::INT});
    const FunctionSignature binarySignature(&Primitive::INT, {&Primitive::INT, &Primitive::INT});
    const FunctionSignature unarySignature(&Primitive::INT, {&Primitive::INT});
    
    const FunctionSignature binarySignatureDec(&Primitive::DEC, {&Primitive::INT, &Primitive::DEC});
    const FunctionSignature binarySignatureChar(&Primitive::INT, {&Primitive::INT, &Primitive::CHAR});
    const FunctionSignature binarySignatureStr(&Primitive::STR, {&Primitive::INT, &Primitive::STR});
    
    Value constructFromBool(const vector<Value>& parameters)
    {
        int value = parameters[0].getValue<bool>();
        return {Primitive::INT, value};
    }
    
    Value constructFromDec(const vector<Value>& parameters)
    {
        int value = (int) parameters[0].getValue<double>();
        return {Primitive::INT, value};
    }
    
    Value constructFromChar(const vector<Value>& parameters)
    {
        int value = parameters[0].getValue<unsigned char>();
        return {Primitive::INT, value};
    }
    
    Value compare(const Value& left, const Value& right)
    {
        int leftInt = left.getValue<int>();
        int rightInt = right.getValue<int>();
        bool result = leftInt > rightInt;
        return {Primitive::BOOL, result};
    }
    
    Value isEqual(const Value& left, const Value& right)
    {
        int leftInt = left.getValue<int>();
        int rightInt = right.getValue<int>();
        bool result = leftInt == rightInt;
        return {Primitive::BOOL, result};
    }
    
    Value add(const Value& left, const Value& right)
    {
        int leftInt = left.getValue<int>();
        int rightInt = right.getValue<int>();
        int result = leftInt + rightInt;
        return {Primitive::INT, result};
    }
    
    Value subtract(const Value& left, const Value& right)
    {
        int leftInt = left.getValue<int>();
        int rightInt = right.getValue<int>();
        int result = leftInt - rightInt;
        return {Primitive::INT, result};
    }
    
    Value multiply(const Value& left, const Value& right)
    {
        int leftInt = left.getValue<int>();
        int rightInt = right.getValue<int>();
        int result = leftInt * rightInt;
        return {Primitive::INT, result};
    }
    
    Value divide(const Value& left, const Value& right)
    {
        int leftInt = left.getValue<int>();
        int rightInt = right.getValue<int>();
        int result = leftInt / rightInt;
        return {Primitive::INT, result};
    }
    
    Value negate(const Value& value)
    {
        int result = -value.getValue<int>();
        return {Primitive::INT, result};
    }
    
    Value addDec(const Value& left, const Value& right)
    {
        Value leftDec = right.getType().construct({left});
        Value result = right.getType().binaryOperation(
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
    
    Value addChar(const Value& left, const Value& right)
    {
        int leftInt = left.getValue<int>();
        unsigned char rightChar = right.getValue<unsigned char>();
        int result = leftInt + rightChar;
        return {Primitive::INT, result};
    }
    
    Value subtractChar(const Value& left, const Value& right)
    {
        int leftInt = left.getValue<int>();
        unsigned char rightChar = right.getValue<unsigned char>();
        int result = leftInt - rightChar;
        return {Primitive::INT, result};
    }
    
    Value multiplyChar(const Value& left, const Value& right)
    {
        int leftInt = left.getValue<int>();
        unsigned char rightChar = right.getValue<unsigned char>();
        int result = leftInt * rightChar;
        return {Primitive::INT, result};
    }
    
    Value divideChar(const Value& left, const Value& right)
    {
        int leftInt = left.getValue<int>();
        unsigned char rightChar = right.getValue<unsigned char>();
        int result = leftInt / rightChar;
        return {Primitive::INT, result};
    }
    
    Value addStr(const Value& left, const Value& right)
    {
        int leftInt = left.getValue<int>();
        string rightStr = right.getValue<string>();
        string result = std::to_string(leftInt) + rightStr;
        return {Primitive::STR, result};
    }
    
    Value multiplyStr(const Value& left, const Value& right)
    {
        int leftInt = left.getValue<int>();
        string rightStr = right.getValue<string>();
        string result;
        for (int i = 0; i < leftInt; i++)
        {
            result += rightStr;
        }
        return {Primitive::STR, result};
    }
}

const Type Primitive::INT = Type
(
    {
        {Int::boolConstructorSignature, Int::constructFromBool},
        {Int::decConstructorSignature, Int::constructFromDec},
        {Int::charConstructorSignature, Int::constructFromChar}
    },
    {Int::comparisonSignature, Int::compare},
    {Int::comparisonSignature, Int::isEqual},
    {
            {Operation::Binary::PLUS, {
                {Int::binarySignature, Int::add},
                {Int::binarySignatureDec, Int::addDec},
                {Int::binarySignatureChar, Int::addChar},
                {Int::binarySignatureStr, Int::addStr}
            }},
            {Operation::Binary::MINUS, {
                {Int::binarySignature, Int::subtract},
                {Int::binarySignatureDec, Int::subtractDec},
                {Int::binarySignatureChar, Int::subtractChar}
            }},
            {Operation::Binary::ASTERISK, {
                {Int::binarySignature, Int::multiply},
                {Int::binarySignatureDec, Int::multiplyDec},
                {Int::binarySignatureChar, Int::multiplyChar},
                {Int::binarySignatureStr, Int::multiplyStr}
            }},
            {Operation::Binary::SLASH, {
                {Int::binarySignature, Int::divide},
                {Int::binarySignatureDec, Int::divideDec},
                {Int::binarySignatureChar, Int::divideChar}
            }}
        },
    {
            {Operation::Unary::MINUS, {Int::unarySignature, Int::negate}}
    },
    {},
    {}
);


