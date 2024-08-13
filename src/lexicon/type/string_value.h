// #ifndef LEX_STRING_H
// #define LEX_STRING_H

// #include "../lexicon.h"

// namespace Lexicons
// {
//     class String : public Lexicon
//     {
//         public:
//         std::string const value;
//         String(std::string const value, int lineNo, int charNo) : Lexicon{Lexicon::STRING, lineNo, charNo}, value{value}
//         {

//         }

//         std::string const ToString() const override
//         {
//             char str[1024 + value.size()];
//             snprintf(str, 1024 + sizeof(value), "< STRING, %s >", value.c_str());
//             return str;
//         }

//     };

// }

// #endif