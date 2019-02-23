#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <ostream>

static const std::string TokenTypeStr[] =
{
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
        "OperatorAssign", // =
        "OperatorAddAssign", // +=
        "OperatorSubAssign", // -=
        "OperatorMultAssign", // *=
        "OperatorDivAssign", // /=
        "OperatorEqual", // ==
        "OperatorGreaterThan", // >
        "OperatorLessThan", // <
        "OperatorGreaterEqual", // >=
        "OperatorLessEqual", // <=
        "Comment", // //
        "Number", // integer
        "Float", // floating point number
        "Unknown",
        "UnexpectedEnd",
        "Unexpected",
        "End" // End of Input
};

class Token
{
public:
    enum class Type
    {
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
        OperatorAssign, // =
        OperatorAddAssign, // +=
        OperatorSubAssign, // -=
        OperatorMultAssign, // *=
        OperatorDivAssign, // /=
        OperatorEqual, // ==
        OperatorGreaterThan, // >
        OperatorLessThan, // <
        OperatorGreaterEqual, // >=
        OperatorLessEqual, // <=
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
    std::string m_value;

public:
    Token(Type t, std::string value);

    Token(Type t);

    Type type() const;

    std::string value() const;

    int toInt() const;

    float toFloat() const;

    std::string name() const;

    bool operator==(Token &other) const;

    bool operator!=(Token &other) const;

    bool operator==(Type t) const;

    bool operator!=(Type t) const;
};

/*
std::ostream& operator<<(std::ostream& os, Token &t)
{
    os<<t.name();
    return os;
}
*/

#endif //TOKEN_HPP
