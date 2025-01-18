#include <unordered_map>
// The idea is that at any point of time, the AST must be valid and equivalent to the original thing(even temporaries).
// This is why application is const.
// Also, reduce must be constant(and the only thing visible to the user ideally)
class Binding;
class LambdaExpr{
public:
    virtual LambdaExpr* reduce() const = 0;
    virtual LambdaExpr* reduce() = 0;
    virtual ~LambdaExpr() = default;
    virtual LambdaExpr* performSubstitution(const Binding*, const LambdaExpr*) = 0;
    virtual LambdaExpr* clone() const = 0;
    virtual LambdaExpr* clone(std::unordered_map<const LambdaExpr*, LambdaExpr*>&) const = 0;
};

class Application: public LambdaExpr{
private:
    LambdaExpr *function;
    LambdaExpr *value;
public:
    Application(LambdaExpr*, LambdaExpr*);
    virtual LambdaExpr* reduce() const override;
    virtual LambdaExpr* reduce() override;
    virtual ~Application() override;
    virtual Application* performSubstitution(const Binding*, const LambdaExpr*) override;
    virtual Application* clone() const override;
    virtual Application* clone(std::unordered_map<const LambdaExpr*, LambdaExpr*>&) const override;
};

class Binding: public LambdaExpr{
private:
    LambdaExpr *boundExpression;
public:
    Binding(LambdaExpr*);
    virtual Binding* reduce() const override;
    virtual Binding* reduce() override;
    virtual ~Binding() override;
    virtual Binding* performSubstitution(const Binding*, const LambdaExpr*) override;
    virtual Binding* clone() const override;
    virtual Binding* clone(std::unordered_map<const LambdaExpr*, LambdaExpr*>&) const override;
    virtual LambdaExpr* application(LambdaExpr*) const;
};

class Variable: public LambdaExpr{
private:
    Binding *binder;
public:
    Variable(Binding*);
    virtual LambdaExpr* reduce() const override;
    virtual LambdaExpr* reduce() override;
    virtual ~Variable() override;
    virtual LambdaExpr* performSubstitution(const Binding*, const LambdaExpr*) override;
    virtual Variable * clone() const override;
    virtual Variable* clone(std::unordered_map<const LambdaExpr*, LambdaExpr*>&) const override;
};