// Copyright (c) 2023 Krypton. All rights reserved.
#pragma once

#include <vector>
#include <functional>
#include <types/Operations.h>
#include <unordered_map>
#include <string>
#include <variant>

using std::vector, std::function, std::unordered_map, std::pair, std::string, std::variant;

class Value;
class Type;

struct FunctionSignature
{
    const Type* returnType;
    vector<const Type*> parameters;
    
    FunctionSignature(const Type* returnType, vector<const Type*> parameters) :
            returnType(returnType), parameters(std::move(parameters)) {}
};

using Method = function<Value(vector<Value>)>;
using BinaryMethod = function<Value(Value, Value)>;
using UnaryMethod = function<Value(Value)>;

using Constructors = vector<pair<FunctionSignature, Method>>;
using Methods = unordered_map<string, vector<pair<FunctionSignature, Method>>>;
using ComparisonMethod = pair<FunctionSignature, BinaryMethod>;
using BinaryMethods = unordered_map<BinaryOperation, vector<pair<FunctionSignature, BinaryMethod>>>;
using UnaryMethods = unordered_map<UnaryOperation, pair<FunctionSignature, UnaryMethod>>;
using Fields = unordered_map<string, const Type&>;

class Type
{
    Constructors _constructors;
    Methods _methods;
    ComparisonMethod _compareMethod;
    ComparisonMethod _isEqualMethod;
    BinaryMethods _binaryMethods;
    UnaryMethods _unaryMethods;
    Fields _fields;
    
public:
    Type(Constructors constructors,
         ComparisonMethod compareMethod,
         ComparisonMethod isEqualMethod,
         BinaryMethods binaryMethods,
         UnaryMethods unaryMethods,
         Methods methods,
         Fields fields);
    
    Value construct(vector<Value> args) const;
    Value compare(Value left, Value right) const;
    Value isEqual(Value left, Value right) const;
    Value binaryOperation(BinaryOperation operation, Value left, Value right) const;
    Value unaryOperation(UnaryOperation operation, Value left, Value right);
    
private:
    static bool isSignatureMatching(const FunctionSignature& signature, const vector<Value>& otherSignature) ;
    bool isConstructorSignature(const FunctionSignature& signature);
    bool isComparisonMethodSignature(const FunctionSignature& signature);
    bool isBinaryMethodSignature(const FunctionSignature& signature);
    bool isUnaryMethodSignature(const FunctionSignature& signature);
};
