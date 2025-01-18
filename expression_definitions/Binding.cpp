#include "./../LambdaExpr.h"

Binding::Binding(LambdaExpr *boundExpression): boundExpression(boundExpression){}

Binding::~Binding(){
    delete boundExpression;
}

Binding* Binding::reduce() const{
    return this->clone();
}

Binding* Binding::reduce(){
    return this;
}


Binding* Binding::performSubstitution(const Binding *binder, const LambdaExpr *toSubstitute){
    LambdaExpr* newBoundExpression = (this->boundExpression)->performSubstitution(binder, toSubstitute);
    if(newBoundExpression != this->boundExpression){
        delete this->boundExpression;
    }
    (this->boundExpression) = newBoundExpression;
    return this;
}

Binding* Binding::clone() const{
    std::unordered_map<const LambdaExpr*, LambdaExpr*> clonedExpressionMapping;
    return this->clone(clonedExpressionMapping);
}

Binding* Binding::clone(std::unordered_map<const LambdaExpr*, LambdaExpr*> &clonedExpressionMapping) const{
    Binding* clone = new Binding(nullptr);
    clonedExpressionMapping[this] = clone;
    clone->boundExpression = (this->boundExpression)->clone(clonedExpressionMapping);
    return clone;
}

LambdaExpr* Binding::application(LambdaExpr *variable) const{
    LambdaExpr* body = (this->boundExpression)->clone();
    body->performSubstitution(this, variable);
    return body;
}

