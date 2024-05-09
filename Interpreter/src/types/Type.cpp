// Copyright (c) 2023 Krypton. All rights reserved.
#include <types/Type.h>
#include <common/Logger.h>
#include <types/Value.h>
#include <types/Primitive.h>

#define INVALID_SIGNATURE { Logger::error("Invalid Signature"); exit(1); }

Type::Type(string name, Constructors constructors, ComparisonMethod compareMethod, ComparisonMethod isEqualMethod, BinaryMethods binaryMethods, UnaryMethods unaryMethods, Methods methods, Fields fields)
    : _name(std::move(name)),
    _constructors(std::move(constructors)),
    _compareMethod(std::move(compareMethod)),
    _isEqualMethod(std::move(isEqualMethod)),
    _binaryMethods(std::move(binaryMethods)),
    _unaryMethods(std::move(unaryMethods)),
    _methods(std::move(methods)),
    _fields(std::move(fields))
{
    // TODO - Add proper error handling
    
    // Validate Constructor Signatures
    for (auto& constructor : _constructors)
    {
        auto signature = constructor.first;
        if (!isConstructorSignature(signature)) INVALID_SIGNATURE
    }
    
    // Validate Comparison Method Signatures
    if (!isComparisonMethodSignature(_compareMethod.first)) INVALID_SIGNATURE
    if (!isComparisonMethodSignature(_isEqualMethod.first)) INVALID_SIGNATURE
    
    // Validate Binary Method Signatures
    for (auto& binaryMethod : _binaryMethods)
    {
        for (auto& method : binaryMethod.second)
        {
            auto signature = method.first;
            if (!isBinaryMethodSignature(signature)) INVALID_SIGNATURE
        }
    }
    
    // Validate Unary Method Signatures
    for (auto& unaryMethod : _unaryMethods)
    {
        auto signature = unaryMethod.second.first;
        if (!isUnaryMethodSignature(signature)) INVALID_SIGNATURE
    }
}

Value Type::construct(vector<Value> args) const
{
    for (auto& constructor : _constructors)
    {
        auto [signature, function] = constructor;
        if (!isSignatureMatching(signature, args)) continue;
        return function(args);
    }
    
    // TODO - Handle errors properly
    Logger::error("No matching constructor found");
    exit(1);
}

bool Type::isSignatureMatching(const FunctionSignature& signature, const vector<Value>& otherSignature)
{
    if (signature.parameters.size() != otherSignature.size()) return false;
    
    for (int i = 0; i < signature.parameters.size(); i++)
    {
        if (signature.parameters[i] != &(otherSignature[i].getType())) return false;
    }
    
    return true;
}

bool Type::isConstructorSignature(const FunctionSignature& signature)
{
    return signature.returnType == this;
}

bool Type::isComparisonMethodSignature(const FunctionSignature& signature)
{
    bool returnType = signature.returnType == &Primitive::BOOL;
    bool parameters = signature.parameters.size() == 2;
    bool firstParameter = signature.parameters[0] == this;
    bool secondParameter = signature.parameters[1] == this;
    return returnType && parameters && firstParameter && secondParameter;
}

bool Type::isBinaryMethodSignature(const FunctionSignature& signature)
{
    bool parameters = signature.parameters.size() == 2;
    bool parameter = signature.parameters[0] == this;
    return parameters && parameter;
}

bool Type::isUnaryMethodSignature(const FunctionSignature& signature)
{
    bool returnType = signature.returnType == this;
    bool parameters = signature.parameters.size() == 1;
    bool parameter = signature.parameters[0] == this;
    return returnType && parameters && parameter;
}

Value Type::compare(const Value& left, const Value& right) const
{
    return _compareMethod.second(left, right);
}

Value Type::isEqual(const Value& left, const Value& right) const
{
    return _isEqualMethod.second(left, right);
}

Value Type::binaryOperation(Operation::Binary operation, const Value& left, const Value& right) const
{
    for (auto& method : _binaryMethods.at(operation))
    {
        auto [signature, function] = method;
        if (signature.parameters[1] == &right.getType()) return function(left, right);
    }
    
    // TODO - Handle errors properly
    Logger::error("No matching binary method found");
    exit(1);
}

Value Type::unaryOperation(Operation::Unary operation, const Value& value) const
{
    if (!_unaryMethods.contains(operation))
    {
        // TODO - Handle errors properly
        Logger::error("No matching unary method found");
        exit(1);
    }
    return _unaryMethods.at(operation).second(value);
}

string Type::getName() const
{
    return _name;
}
