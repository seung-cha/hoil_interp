#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "ast/decl/decl.h"
#include <unordered_map>
#include <vector>
#include <string>


class PageScope
{
    public:
    PageScope(int level) : level{level}
    {

    }

    int level;
    bool isLoopScope = false;
    bool isFunctionScope = false;

    
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
        if(table.find(ident) == table.end())
        {
            return nullptr;
        }

        return table[ident];
    }

    private:
    std::unordered_map<std::string, ASTs::Decl*> table; 

};


class SymbolTable
{
    public:

    PageScope &peek()
    {
        return scope.back();
    }

    inline void OpenScope()
    {
        level++;
        PageScope pageScope{level};
        if(!scope.empty())
        {
            pageScope.isFunctionScope = scope.back().isFunctionScope;
            pageScope.isLoopScope = scope.back().isLoopScope;
        }

        scope.push_back(pageScope);
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

    inline ASTs::Decl *LookupCurrentScope(std::string ident)
    {
        return scope[level].Lookup(ident);
    }

    int level = -1;
    private:
    std::vector<PageScope> scope;
    

};

#endif