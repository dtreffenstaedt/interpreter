#ifndef TOKEN_H
#define TOKEN_H

#include <string>

static const std::wstring TokenTypeStr[] =
{
    U"KeywordIf",
    U"KeywordElse",
    U"KeywordFor",
    U"KeywordWhile",
    U"KeywordDo",
    U"KeywordInteger",
    U"KeywordFloat",
    U"KeywordBoolean",
    U"KeywordString",
    U"KeywordCharacter",
    U"KeywordTrue",
    U"KeywordFalse",
    U"KeywordImport",
    U"KeywordExport",
    U"KeywordVoid",
    U"KeywordReturn",
    U"String",  // alphanumerical text
    U"Character",
    U"Literal",
    U"OperatorPlus", // +
    U"OperatorMinus", // -
    U"OperatorMul", // *
    U"OperatorDiv", // /
    U"OperatorExp", // ^
    U"LParen", // (
    U"RParen", // )
    U"LBrace", // {
    U"RBrace", // }
    U"LBracket", // [
    U"RBracket", // ]
    U"Semicolon", // ;
    U"Colon", // :
    U"Comma", // ,
    U"Period", // .
    U"OperatorScopeResolution", // ::
    U"OperatorAnd", // &&
    U"OperatorOr", // ||
    U"OperatorNot", // !
    U"OperatorBitAND", // &
    U"OperatorBitOR", // |
    U"OperatorBitXOR", // ^
    U"OperatorAssignOR", // |
    U"OperatorAssignXOR", // ^=
    U"OperatorAssignAND", // &=
    U"OperatorBitNOT", // ~
    U"OperatorLShift", // <<
    U"OperatorRShift", // >>
    U"OperatorModulo", // %
    U"OperatorAssign", // =
    U"OperatorAddAssign", // +=
    U"OperatorSubAssign", // -=
    U"OperatorMultAssign", // *=
    U"OperatorDivAssign", // /=
    U"OperatorNotEqual", // !=
    U"OperatorEqual", // ==
    U"OperatorGreaterThan", // >
    U"OperatorLessThan", // <
    U"OperatorGreaterEqual", // >=
    U"OperatorLessEqual", // <=
    U"OperatorIncrement", // ++
    U"OperatorDecrement", // --
    U"Comment", // //
    U"Number", // integer
    U"Float", // floating point number
    U"Unknown",
    U"UnexpectedEnd",
    U"Unexpected",
    U"End" // End of Input
};

static constexpr uint8_t KeywordStrLen = 16;

static const std::wstring KeywordStr[] =
{
    U"if",
    U"else",
    U"for",
    U"while",
    U"do",
    U"int",
    U"float",
    U"bool",
    U"String",
    U"char",
    U"true",
    U"false",
    U"import",
    U"export",
    U"void",
    U"return"
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
