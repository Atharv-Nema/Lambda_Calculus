#include "LambdaExpr.h"
#include <unordered_map>
#include <string>
#include <vector>
class Parser{
private:
    std::unordered_map<std::string, LambdaExpr*> storeASTMap;
    std::vector<std::string> tokenizer(const std::string &line);
    std::vector<std::string> reversePolish(std::vector<std::string> &tokens);
    void addAST(std::string storeName, LambdaExpr *AST);
public:
    LambdaExpr* interpretLine(const std::string &line);
    LambdaExpr* compile(const std::string &filePath);
};