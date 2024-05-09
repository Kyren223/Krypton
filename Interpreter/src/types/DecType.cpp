// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Primitive.h>
#include <types/Type.h>
#include <types/Value.h>

namespace Dec
{
    const FunctionSignature boolConstructorSignature(&Primitive::DEC, {&Primitive::BOOL});
    const FunctionSignature intConstructorSignature(&Primitive::DEC, {&Primitive::INT});
    const FunctionSignature charConstructorSignature(&Primitive::DEC, {&Primitive::CHAR});
    
    const FunctionSignature comparisonSignature(&Primitive::BOOL, {&Primitive::DEC, &Primitive::DEC});
    const FunctionSignature binarySignature(&Primitive::DEC, {&Primitive::DEC, &Primitive::DEC});
    const FunctionSignature unarySignature(&Primitive::DEC, {&Primitive::DEC});
    
    const FunctionSignature binarySignatureInt(&Primitive::DEC, {&Primitive::DEC, &Primitive::INT});
    const FunctionSignature binarySignatureChar(&Primitive::DEC, {&Primitive::DEC, &Primitive::CHAR});
    const FunctionSignature binarySignatureStr(&Primitive::STR, {&Primitive::DEC, &Primitive::STR});
    
    Value constructFromBool(const vector<Value>& parameters)
    {
        double value = parameters[0].getValue<bool>();
        return {Primitive::DEC, value};
    }
    
    Value constructFromInt(const vector<Value>& parameters)
    {
        double value = parameters[0].getValue<int>();
        return {Primitive::DEC, value};
    }
    
    Value constructFromChar(const vector<Value>& parameters)
    {
        double value = parameters[0].getValue<unsigned char>();
        return {Primitive::DEC, value};
    }
    
    Value compare(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        double rightDec = right.getValue<double>();
        bool result = leftDec > rightDec;
        return {Primitive::BOOL, result};
    }
    
    Value isEqual(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        double rightDec = right.getValue<double>();
        bool result = leftDec == rightDec;
        return {Primitive::BOOL, result};
    }
    
    Value add(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        double rightDec = right.getValue<double>();
        double result = leftDec + rightDec;
        return {Primitive::DEC, result};
    }
    
    Value subtract(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        double rightDec = right.getValue<double>();
        double result = leftDec - rightDec;
        return {Primitive::DEC, result};
    }
    
    Value multiply(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        double rightDec = right.getValue<double>();
        double result = leftDec * rightDec;
        return {Primitive::DEC, result};
    }
    
    Value divide(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        double rightDec = right.getValue<double>();
        double result = leftDec / rightDec;
        return {Primitive::DEC, result};
    }
    
    Value negate(const Value& value)
    {
        double result = -value.getValue<double>();
        return {Primitive::DEC, result};
    }
    
    Value addInt(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        int rightInt = right.getValue<int>();
        double result = leftDec + rightInt;
        return {Primitive::DEC, result};
    }
    
    Value subtractInt(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        int rightInt = right.getValue<int>();
        double result = leftDec - rightInt;
        return {Primitive::DEC, result};
    }
    
    Value multiplyInt(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        int rightInt = right.getValue<int>();
        double result = leftDec * rightInt;
        return {Primitive::DEC, result};
    }
    
    Value divideInt(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        int rightInt = right.getValue<int>();
        double result = leftDec / rightInt;
        return {Primitive::DEC, result};
    }
    
    Value addChar(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        unsigned char rightChar = right.getValue<unsigned char>();
        double result = leftDec + rightChar;
        return {Primitive::DEC, result};
    }
    
    Value subtractChar(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        unsigned char rightChar = right.getValue<unsigned char>();
        double result = leftDec - rightChar;
        return {Primitive::DEC, result};
    }
    
    Value multiplyChar(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        unsigned char rightChar = right.getValue<unsigned char>();
        double result = leftDec * rightChar;
        return {Primitive::DEC, result};
    }
    
    Value divideChar(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        unsigned char rightChar = right.getValue<unsigned char>();
        double result = leftDec / rightChar;
        return {Primitive::DEC, result};
    }
    
    Value addStr(const Value& left, const Value& right)
    {
        double leftDec = left.getValue<double>();
        string rightStr = right.getValue<string>();
        string result = std::to_string(leftDec) + rightStr;
        return {Primitive::STR, result};
    }
}

const Type Primitive::DEC = Type
(
    "dec",
    {
        {Dec::boolConstructorSignature, Dec::constructFromBool},
        {Dec::intConstructorSignature, Dec::constructFromInt},
        {Dec::charConstructorSignature, Dec::constructFromChar}
    },
    {Dec::comparisonSignature, Dec::compare},
    {Dec::comparisonSignature, Dec::isEqual},
    {
            {Operation::Binary::PLUS, {
                {Dec::binarySignature, Dec::add},
                {Dec::binarySignatureInt, Dec::addInt},
                {Dec::binarySignatureChar, Dec::addChar}
            }},
            {Operation::Binary::MINUS, {
                {Dec::binarySignature, Dec::subtract},
                {Dec::binarySignatureInt, Dec::subtractInt},
                {Dec::binarySignatureChar, Dec::subtractChar}
            }},
            {Operation::Binary::ASTERISK, {
                {Dec::binarySignature, Dec::multiply},
                {Dec::binarySignatureInt, Dec::multiplyInt},
                {Dec::binarySignatureChar, Dec::multiplyChar}
            }},
            {Operation::Binary::SLASH, {
                {Dec::binarySignature, Dec::divide},
                {Dec::binarySignatureInt, Dec::divideInt},
                {Dec::binarySignatureChar, Dec::divideChar}
            }}
    },
    {
            {Operation::Unary::MINUS, {Dec::unarySignature, Dec::negate}}
    },
    {},
    {}
);


