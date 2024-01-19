// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Primitive.h>
#include <types/Type.h>
#include <types/Value.h>

namespace Bool
{
    const FunctionSignature binarySignature(&Primitive::BOOL, {&Primitive::BOOL, &Primitive::BOOL});
    const FunctionSignature unarySignature(&Primitive::BOOL, {&Primitive::BOOL});
    
    const FunctionSignature binarySignatureStr(&Primitive::STR, {&Primitive::BOOL, &Primitive::STR});
    
    Value compare(const Value& left, const Value& right)
    {
        bool leftBool = left.getValue<bool>();
        bool rightBool = right.getValue<bool>();
        bool result = leftBool > rightBool;
        return {Primitive::BOOL, result};
    }
    
    Value isEqual(const Value& left, const Value& right)
    {
        bool leftBool = left.getValue<bool>();
        bool rightBool = right.getValue<bool>();
        bool result = leftBool == rightBool;
        return {Primitive::BOOL, result};
    }
    
    Value negate(const Value& value)
    {
        bool boolValue = value.getValue<bool>();
        bool result = !boolValue;
        return {Primitive::BOOL, result};
    }
    
    Value addStr(const Value& left, const Value& right)
    {
        bool leftBool = left.getValue<bool>();
        string rightStr = right.getValue<string>();
        string result = leftBool ? "true" : "false";
        result += rightStr;
        return {Primitive::STR, result};
    }
}

const Type Primitive::BOOL = Type
(
    {},
    {Bool::binarySignature, Bool::compare},
    {Bool::binarySignature, Bool::isEqual},
    {
        {Operation::Binary::PLUS, {
                {Bool::binarySignatureStr, Bool::addStr}
        }}
    },
    {
            {Operation::Unary::BANG, {Bool::unarySignature, Bool::negate}}
    },
    {},
    {}
);

