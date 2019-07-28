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
    L"KeywordNumber",
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
    L"KeywordAnd", // AND
    L"KeywordOr", // OR
    L"KeywordNot", // NOT
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
    L"Number", // numeric value
    L"Unknown",
    L"UnexpectedEnd",
    L"Unexpected",
    L"End" // End of Input
};

static constexpr uint8_t KeywordStrLen = 19;

static const std::wstring KeywordStr[] =
{
    L"if",
    L"else",
    L"for",
    L"while",
    L"do",
    L"quantity",
    L"number",
    L"bool",
    L"String",
    L"char",
    L"List",
    L"true",
    L"false",
    L"import",
    L"export",
    L"void",
    L"return",
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
    KeywordNumber,
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
    KeywordAnd, // AND
    KeywordOr, // OR
    KeywordNot, // NOT
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
    Number, // numeric value
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

    double toNumber() const;

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
