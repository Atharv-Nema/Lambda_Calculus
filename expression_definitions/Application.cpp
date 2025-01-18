#include "./../LambdaExpr.h"

Application::Application(LambdaExpr* function, LambdaExpr* value): function(function), value(value){}

Application::~Application(){
    delete this->function;
    delete this->value;
}

LambdaExpr* Application::reduce() const{
    Application *copy = this->clone();
    LambdaExpr* reducedCopy = copy->reduce();
    if(reducedCopy != copy){
        delete copy;
    }
    return reducedCopy;
}

LambdaExpr* Application::reduce(){
    LambdaExpr* newFunction = (this->function)->reduce(); // The non const one
    if(newFunction != this->function){
        delete this->function;
    }
    LambdaExpr* newValue = (this->value)->reduce();
    if(newValue != this->value){
        delete this->value;
    }
    this->function = newFunction;
    this->value = newValue;
    if(dynamic_cast<Binding*>(this->function)){
        // Note: Even after the substitution, this is still valid
        LambdaExpr* answer = dynamic_cast<Binding*>(this->function)->application(this->value);
        LambdaExpr* reducedAnswer = answer->reduce();
        if(reducedAnswer != answer){
            delete answer;
        }
        return answer;
    }
    else{
        return this;
    }

}

Application* Application::performSubstitution(const Binding *binder, const LambdaExpr *toSubstitute){
    LambdaExpr* newFunction = (this->function)->performSubstitution(binder, toSubstitute);
    if(newFunction != this->function){
        delete this->function;
    }
    LambdaExpr* newValue = (this->value)->performSubstitution(binder, toSubstitute);
    if(newValue != this->value){
        delete this->value;
    }
    this->function = newFunction;
    this->value = newValue;
    return this;
}

Application* Application::clone() const{
    std::unordered_map<const LambdaExpr*, LambdaExpr*> clonedExpressionMapping;
    return this->clone(clonedExpressionMapping);
}

Application* Application::clone(std::unordered_map<const LambdaExpr*, LambdaExpr*> &clonedExpressionMapping) const{
    Application* clone = new Application(nullptr, nullptr);
    clonedExpressionMapping[this] = clone;
    clone->function = (this->function)->clone(clonedExpressionMapping);
    clone->value = (this->value)->clone(clonedExpressionMapping);
    return clone;
}