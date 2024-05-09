// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Type.h>
#include <types/Value.h>
#include <types/Primitive.h>

namespace Func
{
    const FunctionSignature comparisonSignature(&Primitive::BOOL, {&Primitive::FUNC, &Primitive::FUNC});
    
    Value compare(const Value& left, const Value& right)
    {
        return {Primitive::BOOL, false};
    }
    
    Value isEqual(const Value& left, const Value& right)
    {
        return {Primitive::BOOL, false};
    }
}

const Type Primitive::FUNC = Type
(
        "func",
        {},
        {Func::comparisonSignature, Func::compare},
        {Func::comparisonSignature, Func::isEqual},
        {},
        {},
        {},
        {}
);
