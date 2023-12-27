// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <types/Type.h>

struct FunctionSignature
{
    const Type* returnType;
    vector<const Type*> parameters;
    
    FunctionSignature(const Type* returnType, vector<const Type*> parameters) :
        returnType(returnType), parameters(std::move(parameters)) {}
};