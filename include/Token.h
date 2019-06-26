#ifndef TOKEN_H
#define TOKEN_H

#include <string>

static const std::wstring TokenTypeStr[] =
{
    L"KeywordIf",
    L"KeywordElse",
    L"KeywordFor",
    L"KeywordWhile",
    L"KeywordDo",
    L"KeywordInteger",
    L"KeywordFloat",
    L"KeywordBoolean",
    L"KeywordString",
    L"KeywordCharacter",
    L"KeywordTrue",
    L"KeywordFalse",
    L"KeywordImport",
    L"KeywordExport",
    L"KeywordVoid",
    L"KeywordReturn",
    L"String",  // alphanumerical text
    L"Character",
    L"Literal",
    L"OperatorPlus", // +
    L"OperatorMinus", // -
    L"OperatorMul", // *
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
    L"OperatorAnd", // &&
    L"OperatorOr", // ||
    L"OperatorNot", // !
    L"OperatorBitAND", // &
    L"OperatorBitOR", // |
    L"OperatorBitXOR", // ^
    L"OperatorAssignOR", // |
    L"OperatorAssignXOR", // ^=
    L"OperatorAssignAND", // &=
    L"OperatorBitNOT", // ~
    L"OperatorLShift", // <<
    L"OperatorRShift", // >>
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
    L"Number", // integer
    L"Float", // floating point number
    L"Unknown",
    L"UnexpectedEnd",
    L"Unexpected",
    L"End" // End of Input
};

static constexpr uint8_t KeywordStrLen = 16;

static const std::wstring KeywordStr[] =
{
    L"if",
    L"else",
    L"for",
    L"while",
    L"do",
    L"int",
    L"float",
    L"bool",
    L"String",
    L"char",
    L"true",
    L"false",
    L"import",
    L"export",
    L"void",
    L"return"
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
        KeywordInteger,
        KeywordFloat,
        KeywordBoolean,
        KeywordString,
        KeywordCharacter,
        KeywordTrue,
        KeywordFalse,
        KeywordImport,
        KeywordExport,
        KeywordVoid,
        KeywordReturn,
        String,  // alphanumerical text
        Character,
        Literal,
        OperatorPlus, // +
        OperatorMinus, // -
        OperatorMul, // *
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
        OperatorAnd, // &&
        OperatorOr, // ||
        OperatorNot, // !
        OperatorBitAND, // &
        OperatorBitOR, // |
        OperatorBitXOR, // ^
        OperatorAssignOR, // |
        OperatorAssignXOR, // ^=
        OperatorAssignAND, // &=
        OperatorBitNOT, // ~
        OperatorLShift, // <<
        OperatorRShift, // >>
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
        Number, // integer
        Float, // floating point number
        Unknown,
        UnexpectedEnd,
        Unexpected,
        End // End of Input
    };

private:
    Type m_type;
    std::wstring m_value;

public:
    Token(Type t, std::wstring value);

    Token(Type t);

    Type type() const;

    std::wstring value() const;

    int toInt() const;

    float toFloat() const;

    std::wstring name() const;

    bool operator==(Token &other) const;

    bool operator!=(Token &other) const;

    bool operator==(Type t) const;

    bool operator!=(Type t) const;
};

#endif //TOKEN_H
