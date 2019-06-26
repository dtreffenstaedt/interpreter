#ifndef TOKEN_H
#define TOKEN_H

#include <string>

static const std::wstring TokenTypeStr[] =
{
    "KeywordIf",
    "KeywordElse",
    "KeywordFor",
    "KeywordWhile",
    "KeywordDo",
    "KeywordInteger",
    "KeywordFloat",
    "KeywordBoolean",
    "KeywordString",
    "KeywordCharacter",
    "KeywordTrue",
    "KeywordFalse",
    "KeywordImport",
    "KeywordExport",
    "KeywordVoid",
    "KeywordReturn",
    "String",  // alphanumerical text
    "Character",
    "Literal",
    "OperatorPlus", // +
    "OperatorMinus", // -
    "OperatorMul", // *
    "OperatorDiv", // /
    "OperatorExp", // ^
    "LParen", // (
    "RParen", // )
    "LBrace", // {
    "RBrace", // }
    "LBracket", // [
    "RBracket", // ]
    "Semicolon", // ;
    "Colon", // :
    "Comma", // ,
    "Period", // .
    "OperatorScopeResolution", // ::
    "OperatorAnd", // &&
    "OperatorOr", // ||
    "OperatorNot", // !
    "OperatorBitAND", // &
    "OperatorBitOR", // |
    "OperatorBitXOR", // ^
    "OperatorAssignOR", // |
    "OperatorAssignXOR", // ^=
    "OperatorAssignAND", // &=
    "OperatorBitNOT", // ~
    "OperatorLShift", // <<
    "OperatorRShift", // >>
    "OperatorModulo", // %
    "OperatorAssign", // =
    "OperatorAddAssign", // +=
    "OperatorSubAssign", // -=
    "OperatorMultAssign", // *=
    "OperatorDivAssign", // /=
    "OperatorNotEqual", // !=
    "OperatorEqual", // ==
    "OperatorGreaterThan", // >
    "OperatorLessThan", // <
    "OperatorGreaterEqual", // >=
    "OperatorLessEqual", // <=
    "OperatorIncrement", // ++
    "OperatorDecrement", // --
    "Comment", // //
    "Number", // integer
    "Float", // floating point number
    "Unknown",
    "UnexpectedEnd",
    "Unexpected",
    "End" // End of Input
};

static constexpr uint8_t KeywordStrLen = 16;

static const std::string KeywordStr[] =
{
    "if",
    "else",
    "for",
    "while",
    "do",
    "int",
    "float",
    "bool",
    "String",
    "char",
    "true",
    "false",
    "import",
    "export",
    "void",
    "return"
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
