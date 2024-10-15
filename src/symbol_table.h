#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "ast/decl/decl.h"
#include <unordered_map>
#include <vector>
#include <string>

class SymbolTable
{
    public: 
    inline void OpenScope()
    {
        level++;
        scope.push_back({level});
    }

    inline void CloseScope()
    {
        level--;
        scope.pop_back();
    }

    inline bool Insert(std::string ident, ASTs::Decl *decl)
    {
        return scope[level].Insert(ident, decl);
    }

    inline ASTs::Decl *Lookup(std::string ident)
    {
        ASTs::Decl *decl = nullptr;

        for(auto iter = scope.rbegin(); iter != scope.rend(); iter++)
        {
            decl = iter->Lookup(ident);

            if(decl) break;
        }

        return decl;
    }

    private:
    std::vector<PageScope> scope;
    int level = -1;
    

};

class PageScope
{
    public:
    PageScope(int level) : level{level}
    {

    }

    int level;

    
    /**
     * Insert a Decl. Return false if an identifier exists.
     */
    inline bool Insert(std::string ident, ASTs::Decl *decl)
    {
        if(table.find(ident) != table.end())
        {
            return false;
        }

        table[ident] = decl;
        return true;
    }

    inline ASTs::Decl *Lookup(std::string ident)
    {
        if(table.find(ident) != table.end())
        {
            return nullptr;
        }

        return table[ident];
    }

    private:
    std::unordered_map<std::string, ASTs::Decl*> table; 

};

#endif