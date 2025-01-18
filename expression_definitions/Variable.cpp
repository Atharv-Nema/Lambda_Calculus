#include "./../LambdaExpr.h"

Variable::Variable(Binding *binder): binder(binder){}

Variable::~Variable(){}

LambdaExpr* Variable::reduce() const{
    return this->clone();
}

LambdaExpr* Variable::reduce(){
    return this;
}

LambdaExpr* Variable::performSubstitution(const Binding *binder, const LambdaExpr *toSubstitute){
    if(this->binder == binder){
        return toSubstitute->clone();
    }
    else{
        return this;
    }
}



Variable* Variable::clone() const{
    return new Variable(this->binder);
}

Variable* Variable::clone(std::unordered_map<const LambdaExpr*, LambdaExpr*> &clonedExpressionMapping) const{
    if(clonedExpressionMapping.find(this->binder) != clonedExpressionMapping.end()){
        // TODO: Make types stronger here and remove the dynamic_cast
        return new Variable(dynamic_cast<Binding*>(clonedExpressionMapping[this->binder]));
    }
    else{
        return new Variable(this->binder);
    }
}