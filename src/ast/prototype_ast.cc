#include "prototype_ast.h"

#include "src/globals/globals.h"

Function* PrototypeAST::codegen() {
    // Make the function type:  double(double,double) etc.
    vector<Type*> doubles(args_.size(), Type::getDoubleTy(*TheContext));
    FunctionType* ft =
        FunctionType::get(Type::getDoubleTy(*TheContext), doubles, false);
    Function* f =
        Function::Create(ft, Function::ExternalLinkage, name_, TheModule.get());

    unsigned index = 0;
    for (auto& arg : f->args()) {
        arg.setName(args_[index++]);
    }

    return f;
}
