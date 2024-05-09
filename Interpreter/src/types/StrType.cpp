// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Primitive.h>
#include <types/Type.h>
#include <types/Value.h>

namespace Str
{
    const FunctionSignature boolConstructorSignature(&Primitive::STR, {&Primitive::BOOL});
    const FunctionSignature decConstructorSignature(&Primitive::STR, {&Primitive::DEC});
    const FunctionSignature intConstructorSignature(&Primitive::STR, {&Primitive::INT});
    const FunctionSignature charConstructorSignature(&Primitive::STR, {&Primitive::CHAR});
    
    const FunctionSignature comparisonSignature(&Primitive::BOOL, {&Primitive::STR, &Primitive::STR});
    const FunctionSignature binarySignature(&Primitive::STR, {&Primitive::STR, &Primitive::STR});
    
    const FunctionSignature binarySignatureBool(&Primitive::STR, {&Primitive::STR, &Primitive::BOOL});
    const FunctionSignature binarySignatureDec(&Primitive::STR, {&Primitive::STR, &Primitive::DEC});
    const FunctionSignature binarySignatureInt(&Primitive::STR, {&Primitive::STR, &Primitive::INT});
    const FunctionSignature binarySignatureChar(&Primitive::STR, {&Primitive::STR, &Primitive::CHAR});
    
    const FunctionSignature indexSignature(&Primitive::CHAR, {&Primitive::STR, &Primitive::INT});
    
    Value constructFromBool(const vector<Value>& parameters)
    {
        bool value = parameters[0].getValue<bool>();
        return {Primitive::STR, value ? "true" : "false"};
    }
    
    Value constructFromInt(const vector<Value>& parameters)
    {
        int value = parameters[0].getValue<int>();
        return {Primitive::STR, std::to_string(value)};
    }
    
    Value constructFromDec(const vector<Value>& parameters)
    {
        double value = parameters[0].getValue<double>();
        return {Primitive::STR, std::to_string(value)};
    }
    
    Value constructFromChar(const vector<Value>& parameters)
    {
        unsigned char value = parameters[0].getValue<unsigned char>();
        return {Primitive::STR, std::to_string(value)};
    }
    
    Value compare(const Value& left, const Value& right)
    {
        string leftStr = left.getValue<string>();
        string rightStr = right.getValue<string>();
        bool result = leftStr > rightStr;
        return {Primitive::BOOL, result};
    }
    
    Value isEqual(const Value& left, const Value& right)
    {
        string leftStr = left.getValue<string>();
        string rightStr = right.getValue<string>();
        bool result = leftStr == rightStr;
        return {Primitive::BOOL, result};
    }
    
    Value add(const Value& left, const Value& right)
    {
        string leftStr = left.getValue<string>();
        string rightStr = right.getValue<string>();
        string result = leftStr + rightStr;
        return {Primitive::STR, result};
    }
    
    Value addInt(const Value& left, const Value& right)
    {
        string leftStr = left.getValue<string>();
        int rightInt = right.getValue<int>();
        string result = leftStr + std::to_string(rightInt);
        return {Primitive::STR, result};
    }
    
    Value addDec(const Value& left, const Value& right)
    {
        string leftStr = left.getValue<string>();
        double rightDec = right.getValue<double>();
        string result = leftStr + std::to_string(rightDec);
        return {Primitive::STR, result};
    }
    
    Value addChar(const Value& left, const Value& right)
    {
        string leftStr = left.getValue<string>();
        unsigned char rightChar = right.getValue<unsigned char>();
        string result = leftStr;
        result += rightChar;
        return {Primitive::STR, result};
    }
    
    Value addBool(const Value& left, const Value& right)
    {
        string leftStr = left.getValue<string>();
        bool rightBool = right.getValue<bool>();
        string result = leftStr + (rightBool ? "true" : "false");
        return {Primitive::STR, result};
    }
    
    Value multiply(const Value& left, const Value& right)
    {
        // Python-like string multiplication
        string leftStr = left.getValue<string>();
        int rightInt = right.getValue<int>();
        string result;
        for (int i = 0; i < rightInt; i++)
        {
            result += leftStr;
        }
        return {Primitive::STR, result};
    }
    
    Value index(const Value& left, const Value& right)
    {
        string leftStr = left.getValue<string>();
        int rightInt = right.getValue<int>();
        bool outOfBounds = rightInt < 0 || rightInt >= leftStr.size();
        unsigned char result = outOfBounds ? '\0' : leftStr[rightInt];
        return {Primitive::CHAR, result};
    }
}

const Type Primitive::STR = Type
(
    "str",
    {
        {Str::boolConstructorSignature, Str::constructFromBool},
        {Str::decConstructorSignature, Str::constructFromDec},
        {Str::intConstructorSignature, Str::constructFromInt},
        {Str::charConstructorSignature, Str::constructFromChar}
    },
    {Str::comparisonSignature, Str::compare},
    {Str::comparisonSignature, Str::isEqual},
    {
        {Operation::Binary::PLUS, {
          {Str::binarySignature, Str::add},
          {Str::binarySignatureDec, Str::addDec},
          {Str::binarySignatureInt, Str::addInt},
          {Str::binarySignatureChar, Str::addChar},
            {Str::binarySignatureBool, Str::addBool}
        }},
        {Operation::Binary::SQUARE_BRACKETS,{
            {Str::indexSignature, Str::index}
        }},
        {},
        {Operation::Binary::ASTERISK, {
          {Str::binarySignatureInt, Str::multiply}
        }},
        {}
    },
    {},
    {},
    {}
);


