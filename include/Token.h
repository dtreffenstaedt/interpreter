#ifndef TOKEN_H
#define TOKEN_H

#include <string>

struct Position
{
    int row = 1;
    int col = 1;
};

static const std::wstring TokenTypeStr[] =
{
    L"KeywordIf",
    L"KeywordElse",
    L"KeywordFor",
    L"KeywordWhile",
    L"KeywordDo",
    L"KeywordQuantity",
    L"KeywordReal",
    L"KeywordInteger",
    L"KeywordBool",
    L"KeywordString",
    L"KeywordList",
    L"KeywordChar",
    L"KeywordVoid",
    L"KeywordTrue",
    L"KeywordFalse",
    L"KeywordImport",
    L"KeywordExport",
    L"KeywordReturn",
    L"KeywordPrint",
    L"OperatorAnd", // AND
    L"OperatorOr", // OR
    L"OperatorNot", // NOT
    L"String",  // alphanumerical text
    L"Character",
    L"Identifier",
    L"OperatorPlus", // +
    L"OperatorMinus", // -
    L"OperatorMult", // *
    L"OperatorDiv", // /
    L"OperatorExp", // ^
    L"LParen", // (
    L"RParen", // )
    L"LBrace", // {
    L"RBrace", // }
    L"LBracket", // [
    L"RBracket", // ]
    L"Semicolon", // ;
    L"Colon", // :
    L"Comma", // ,
    L"Period", // .
    L"OperatorScopeResolution", // ::
    L"OperatorModulo", // %
    L"OperatorAssign", // =
    L"OperatorAddAssign", // +=
    L"OperatorSubAssign", // -=
    L"OperatorMultAssign", // *=
    L"OperatorDivAssign", // /=
    L"OperatorNotEqual", // !=
    L"OperatorEqual", // ==
    L"OperatorGreaterThan", // >
    L"OperatorLessThan", // <
    L"OperatorGreaterEqual", // >=
    L"OperatorLessEqual", // <=
    L"OperatorIncrement", // ++
    L"OperatorDecrement", // --
    L"Comment", // //
    L"Real", // numeric value
    L"Integer", // numeric value
    L"Unknown",
    L"UnexpectedEnd",
    L"Unexpected",
    L"End" // End of Input
};

static constexpr uint8_t KeywordStrLen = 22;

static const std::wstring KeywordStr[] =
{
    L"if",
    L"else",
    L"for",
    L"while",
    L"do",
    L"quantity",
    L"real",
    L"int",
    L"bool",
    L"String",
    L"List",
    L"char",
    L"void",
    L"true",
    L"false",
    L"import",
    L"export",
    L"return",
    L"print",
    L"AND",
    L"OR",
    L"NOT"
};
static const std::wstring KeywordStrAlt[] =
{
    L"if",
    L"else",
    L"for",
    L"while",
    L"do",
    L"quantity",
    L"ℝ",
    L"ℤ",
    L"bool",
    L"String",
    L"List",
    L"char",
    L"void",
    L"true",
    L"false",
    L"import",
    L"export",
    L"return",
    L"print",
    L"AND",
    L"OR",
    L"NOT"
};

class Token
{   
public:
    enum class Type
    {
    KeywordIf,
    KeywordElse,
    KeywordFor,
    KeywordWhile,
    KeywordDo,
    KeywordQuantity,
    KeywordReal,
    KeywordInteger,
    KeywordBool,
    KeywordString,
    KeywordList,
    KeywordChar,
    KeywordVoid,
    KeywordTrue,
    KeywordFalse,
    KeywordImport,
    KeywordExport,
    KeywordReturn,
    KeywordPrint,
    OperatorAnd, // AND
    OperatorOr, // OR
    OperatorNot, // NOT
    String,  // alphanumerical text
    Character,
    Identifier,
    OperatorPlus, // +
    OperatorMinus, // -
    OperatorMult, // *
    OperatorDiv, // /
    OperatorExp, // ^
    LParen, // (
    RParen, // )
    LBrace, // {
    RBrace, // }
    LBracket, // [
    RBracket, // ]
    Semicolon, // ;
    Colon, // :
    Comma, // ,
    Period, // .
    OperatorScopeResolution, // ::
    OperatorModulo, // %
    OperatorAssign, // =
    OperatorAddAssign, // +=
    OperatorSubAssign, // -=
    OperatorMultAssign, // *=
    OperatorDivAssign, // /=
    OperatorNotEqual, // !=
    OperatorEqual, // ==
    OperatorGreaterThan, // >
    OperatorLessThan, // <
    OperatorGreaterEqual, // >=
    OperatorLessEqual, // <=
    OperatorIncrement, // ++
    OperatorDecrement, // --
    Comment, // //
    Real, // numeric value
    Integer, // numeric value
    Unknown,
    UnexpectedEnd,
    Unexpected,
    End // End of Input
    };

private:
    Type m_type;
    std::wstring m_value;
    Position m_pos;

public:
    Token(Position pos, Type t, std::wstring value);

    explicit Token(Position pos = {1,1}, Type t = Token::Type::End);

    Type type() const;

    std::wstring value() const;

    double toReal() const;

    int64_t toInt() const;

    char toCharacter() const;
    
    bool toBoolean() const;

    std::wstring name() const;

    Position pos() const;

    bool operator==(const Token& other) const;

    bool operator!=(const Token& other) const;

    bool operator==(const Type& t) const;

    bool operator>=(const Type& t) const;
    bool operator<=(const Type& t) const;
    bool operator>(const Type& t) const;
    bool operator<(const Type& t) const;

    bool operator!=(const Type& t) const;
};

#endif //TOKEN_H
