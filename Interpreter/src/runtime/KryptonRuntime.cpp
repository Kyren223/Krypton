// Copyright (c) 2023 Krypton. All rights reserved.
#include <runtime/KryptonRuntime.h>

#include <common/Logger.h>
#include <lexer/Token.h>
#include <nodes/Statements.h>
#include <types/Primitive.h>
#include <iostream>

KryptonRuntime::KryptonRuntime(unique_ptr<ASTNode> ast, Environment& environment) :
    _ast(std::move(ast)),
    _environment(&environment),
    _handler(ErrorHandler::getInstance()) {}

void KryptonRuntime::run()
{
    try
    {
        if (auto node = dynamic_cast<const Statement*>(_ast.get()))
        {
            execute(*node);
        }
    }
    catch (const std::exception& e)
    {
        Logger::error("KryptonRuntime::run - ");
        Logger::error(e.what());
    }
}

Value KryptonRuntime::evaluate(const Expression& expression)
{
    if (auto pBinary = dynamic_cast<const BinaryExpression*>(&expression))
    {
        return evaluate(*pBinary);
    }
    else if (auto pUnary = dynamic_cast<const UnaryExpression*>(&expression))
    {
        return evaluate(*pUnary);
    }
    else if (auto pLiteral = dynamic_cast<const LiteralExpression*>(&expression))
    {
        return evaluate(*pLiteral);
    }
    else if (dynamic_cast<const InputExpression*>(&expression))
    {
        return evaluateInput();
    }
    else if (const auto* pLambda = dynamic_cast<const LambdaExpression*>(&expression))
    {
        return {Primitive::FUNC, pLambda};
    }
    else if (const auto* pCall = dynamic_cast<const CallExpression*>(&expression))
    {
        return evaluate(*pCall);
    }
    else
    {
        // TODO: Add better error handling
        Logger::error("KryptonRuntime::evaluate - unknown expression type");
        exit(1);
    }
}

Value KryptonRuntime::evaluate(const BinaryExpression& expression)
{
    Value left = evaluate(*expression.left);
    Value right = evaluate(*expression.right);
    
    // Comparison operators
    switch (expression.op.getType())
    {
        case TokenTypes::EQUAL_EQUAL:
        {
            return left.getType().isEqual(left, right);
        }
        
        case TokenTypes::BANG_EQUAL:
        {
            bool isNotEqual = !left.getType().isEqual(left, right).getValue<bool>();
            return {Primitive::BOOL, isNotEqual};
        }
        
        case TokenTypes::GREATER:
        {
            return left.getType().compare(left, right);
        }
        
        case TokenTypes::GREATER_EQUAL:
        {
            Value isEqual = left.getType().isEqual(left, right);
            Value isGreater = left.getType().compare(left, right);
            bool isGreaterEqual = isEqual.getValue<bool>() || isGreater.getValue<bool>();
            return {Primitive::BOOL, isGreaterEqual};
        }
        
        case TokenTypes::LESS:
        {
            Value isEqual = left.getType().isEqual(left, right);
            Value isGreater = left.getType().compare(left, right);
            bool isLess = !(isEqual.getValue<bool>() || isGreater.getValue<bool>());
            return {Primitive::BOOL, isLess};
        }
        
        case TokenTypes::LESS_EQUAL:
        {
            Value isGreater = left.getType().isEqual(left, right);
            bool isLessEqual = !isGreater.getValue<bool>();
            return {Primitive::BOOL, isLessEqual};
        }
        
        default:
        {
            Operation::Binary operation = Operation::getBinaryOperation(expression.op.getType());
            return left.getType().binaryOperation(operation, left, right);
        }
    }
}

Value KryptonRuntime::evaluate(const UnaryExpression& expression)
{
    Value value = evaluate(*expression.expression);
    Operation::Unary operation = Operation::getUnaryOperation(expression.op.getType());
    return value.getType().unaryOperation(operation, value);
}

Value KryptonRuntime::evaluate(const LiteralExpression& expression)
{
    switch (expression.literal.getType())
    {
        case TokenTypes::INT_LITERAL:
        {
            int value = std::stoi(expression.literal.getLexeme().value());
            return {Primitive::INT, value};
        }
        case TokenTypes::DEC_LITERAL:
        {
            double value = std::stod(expression.literal.getLexeme().value());
            return {Primitive::DEC, value};
        }
        case TokenTypes::CHAR_LITERAL:
        {
            unsigned char value = expression.literal.getLexeme().value()[0];
            return {Primitive::CHAR, value};
        }
        case TokenTypes::TRUE:
        {
            return {Primitive::BOOL, true};
        }
        case TokenTypes::FALSE:
        {
            return {Primitive::BOOL, false};
        }
        case TokenTypes::STRING_LITERAL:
        {
            string value = expression.literal.getLexeme().value();
            return {Primitive::STR, value};
        }
        case TokenTypes::IDENTIFIER:
        {
            string identifier = expression.literal.getLexeme().value();
            const Value* value = _environment->get(identifier);
            if (value != nullptr) return *value;
            _handler.nullReference(identifier);
            _handler.terminateIfErrors();
        }
        default: break;
    }
    // TODO: Add better error handling
    Logger::error("KryptonRuntime::evaluate - unknown literal type");
    exit(1);
}

void KryptonRuntime::execute(const Statement& statement)
{
    if (auto scopeStmt = dynamic_cast<const CodeBlock*>(&statement))
    {
        execute(*scopeStmt);
    }
    else if (auto printStmt = dynamic_cast<const PrintStatement*>(&statement))
    {
        execute(*printStmt);
    }
    else if (auto ifStmt = dynamic_cast<const IfStatement*>(&statement))
    {
        execute(*ifStmt);
    }
    else if (auto varDecl = dynamic_cast<const VariableDeclaration*>(&statement))
    {
        execute(*varDecl);
    }
    else if (auto varAssign = dynamic_cast<const VariableAssignment*>(&statement))
    {
        execute(*varAssign);
    }
    else if (auto whileStmt = dynamic_cast<const WhileStatement*>(&statement))
    {
        execute(*whileStmt);
    }
    else if (auto callStmt = dynamic_cast<const CallStatement*>(&statement))
    {
        execute(*callStmt);
    }
    else if (auto returnStmt = dynamic_cast<const ReturnStatement*>(&statement))
    {
        execute(*returnStmt);
    }
    else
    {
        Logger::error("KryptonRuntime::execute - unknown statement type");
        exit(1);
    }
}

void KryptonRuntime::execute(const PrintStatement& statement)
{
    Value value = evaluate(*statement.expression);
    if (&value.getType() == &Primitive::INT)
    {
        string s = std::to_string(value.getValue<int>());
        Logger::print(LogMode::NONE, s, Color::WHITE);
    }
    else if (&value.getType() == &Primitive::DEC)
    {
        string s = std::to_string(value.getValue<double>());
        Logger::print(LogMode::NONE, s, Color::WHITE);
    }
    else if (&value.getType() == &Primitive::BOOL)
    {
        string s = value.getValue<bool>() ? "true" : "false";
        Logger::print(LogMode::NONE, s, Color::WHITE);
    }
    else if (&value.getType() == &Primitive::CHAR)
    {
        string s(1, value.getValue<unsigned char>());
        Logger::print(LogMode::NONE, s, Color::WHITE);
    }
    else if (&value.getType() == &Primitive::STR)
    {
        string s = value.getValue<string>();
        Logger::print(LogMode::NONE, s, Color::WHITE);
    }
    else
    {
        Logger::error("KryptonRuntime::execute - unknown value type");
        exit(1);
    }
}

void KryptonRuntime::execute(const CodeBlock& statement)
{
    if (!statement.hasScope)
    {
        for (const auto& stmt : statement.statements)
        {
            execute(*stmt);
        }
        return;
    }
    
    Environment* parent = _environment;
    _environment = new Environment(*parent);
    for (const auto& stmt : statement.statements)
    {
        Statement* stmtPtr = stmt.get();
        execute(*stmtPtr);
    }
    delete _environment;
    _environment = parent;
}

void KryptonRuntime::execute(const IfStatement& statement)
{
    Value condition = evaluate(*statement.condition);
    if (&condition.getType() != &Primitive::BOOL)
    {
        Logger::error("KryptonRuntime::execute - if statement condition must be a boolean");
        exit(1);
    }
    if (condition.getValue<bool>())
    {
        Statement* stmt = statement.thenBranch.get();
        execute(*stmt);
    }
    else if (statement.elseBranch.has_value())
    {
        execute(*statement.elseBranch.value());
    }
}

void KryptonRuntime::execute(const VariableDeclaration& statement)
{
    if (statement.initializer.has_value())
    {
        Value value = evaluate(*statement.initializer.value());
        _environment->define(statement.type, statement.identifier, value);
    }
    else
    {
        _environment->define(statement.type, statement.identifier);
    }
}

void KryptonRuntime::execute(const VariableAssignment& statement)
{
    Value value = evaluate(*statement.value);
    _environment->assign(statement.identifier, value);
}

void KryptonRuntime::execute(const WhileStatement& statement)
{
    while (true)
    {
        Value condition = evaluate(*statement.condition);
        if (&condition.getType() != &Primitive::BOOL)
        {
            Logger::error("KryptonRuntime::execute - while statement condition must be a boolean");
            exit(1);
        }
        
        if (!condition.getValue<bool>()) break;
        execute(*statement.body);
    }
}

Value KryptonRuntime::evaluateInput()
{
    string input;
    std::getline(std::cin, input);
    return {Primitive::STR, input};
}

Value KryptonRuntime::evaluate(const CallExpression& expression)
{
    Value callee = evaluate(*expression.callee);
    if (&callee.getType() != &Primitive::FUNC)
    {
        // TODO: Add better error handling
        Logger::error("KryptonRuntime::evaluate - callee must be a function");
        exit(1);
    }
    
    const auto* lambda = callee.getValue<const LambdaExpression*>();
    
    if (!lambda->returnType.has_value())
    {
        _handler.usingValueFromVoidFunction("Anonymous Lambda");
    }
    
    Environment* _parent = _environment;
    _environment = new Environment(*_parent);
    
    // Bind arguments to parameters
    if (lambda->parameters.size() != expression.arguments.size())
    {
        // TODO: Add better error handling
        _handler.argumentLengthMismatch("Anonymous Lambda", lambda->parameters.size(), expression.arguments.size());
        _handler.terminateIfErrors();
    }
    for (size_t i = 0; i < lambda->parameters.size(); i++)
    {
        Value value = evaluate(*expression.arguments[i]);
        pair<string, optional<const Type*>> parameter = lambda->parameters[i];
        
        if (parameter.second.has_value() && parameter.second.value() != &value.getType())
        {
            _handler.typeMismatch(parameter.first, parameter.second.value(), value.getType());
        }
        
        _environment->define(parameter.second, parameter.first,value);
    }
    
    // Execute lambda body

    if (lambda->isNative)
    {
        lambda->nativeFunction(_environment);
        if (!_environment->getReturnValue(false).has_value())
        {
            _handler.noReturnStatementFound("Anonymous Lambda");
            _handler.terminateIfErrors();
        }
        optional<Value> value = _environment->getReturnValue(true).value();

        delete _environment;
        _environment = _parent;

        if (!value.has_value())
        {
            _handler.expectedTypeXgotVoid("Anonymous Lambda", lambda->returnType.value());
            _handler.terminateIfErrors();
            throw std::runtime_error("KryptonRuntime::evaluate - expected return value");
        }

        if (lambda->returnType.value().has_value() && lambda->returnType.value().value() != &value->getType())
        {
            _handler.typeMismatch("Anonymous Lambda", lambda->returnType.value(), value->getType());
            _handler.terminateIfErrors();
            throw std::runtime_error("KryptonRuntime::evaluate - expected return value");
        }

        return *value;
    }

    for (auto& stmt : (*lambda->body).statements)
    {
        Statement* stmtPtr = stmt.get();
        execute(*stmtPtr);
        if (!_environment->getReturnValue(false).has_value()) continue;
        optional<Value> value = _environment->getReturnValue(true).value();

        delete _environment;
        _environment = _parent;

        if (!value.has_value())
        {
            _handler.expectedTypeXgotVoid("Anonymous Lambda", lambda->returnType.value());
            _handler.terminateIfErrors();
            throw std::runtime_error("KryptonRuntime::evaluate - expected return value");
        }

        if (lambda->returnType.value().has_value() && lambda->returnType.value().value() != &value->getType())
        {
            _handler.typeMismatch("Anonymous Lambda", lambda->returnType.value(), value->getType());
        }

        return *value;
    }

    delete _environment;
    _environment = _parent;

    // Error if no return statement
    _handler.noReturnStatementFound("Anonymous Lambda");
}

void KryptonRuntime::execute(const CallStatement& statement)
{
    Value callee = evaluate(*statement.call->callee);
    if (&callee.getType() != &Primitive::FUNC)
    {
        // TODO: Add better error handling
        Logger::error("KryptonRuntime::evaluate - callee must be a function");
        exit(1);
    }
    
    const auto* lambda = callee.getValue<const LambdaExpression*>();
    
    Environment* _parent = _environment;
    _environment = new Environment(*_parent);
    
    // Bind arguments to parameters
    if (lambda->parameters.size() != statement.call->arguments.size())
    {
        // TODO: Add better error handling
        _handler.argumentLengthMismatch("Anonymous Lambda", lambda->parameters.size(), statement.call->arguments.size());
        _handler.terminateIfErrors();
    }
    
    for (size_t i = 0; i < lambda->parameters.size(); i++)
    {
        Value value = evaluate(*statement.call->arguments[i]);
        pair<string, optional<const Type*>> parameter = lambda->parameters[i];
        
        if (parameter.second != &value.getType())
        {
            _handler.typeMismatch(parameter.first, parameter.second, value.getType());
        }
        
        _environment->define(parameter.second, parameter.first, value);
    }
    
    // Execute lambda body

    if (lambda->isNative)
    {
        lambda->nativeFunction(_environment);
        delete _environment;
        _environment = _parent;
    }

    for (const auto& stmt : (*lambda->body).statements)
    {
        execute(*stmt);
        if (!_environment->getReturnValue(false).has_value()) continue;
        optional<Value> value = _environment->getReturnValue(true).value();

        if (value.has_value())
        {
            if (lambda->returnType.value().has_value() && lambda->returnType.value().value() != &value->getType())
            {
                _handler.typeMismatch("Anonymous Lambda", lambda->returnType.value(), value->getType());
            }
        }
        // If a value is returned, it is ignored but evaluated

        delete _environment;
        _environment = _parent;
        return;
    }

    delete _environment;
    _environment = _parent;
}

void KryptonRuntime::execute(const ReturnStatement& statement) {
    if (statement.value.has_value())
    {
        Value value = evaluate(*statement.value.value());
        _environment->setReturnValue(value);
    }
    else _environment->setReturnValue({});
}
