#ifndef AST_H
#define AST_H

#include "ast/program.h"

// Expressions
#include "ast/expr/expr.h"
#include "ast/expr/binary_expr.h"
#include "ast/expr/pre_unary_expr.h"
#include "ast/expr/post_unary_expr.h"
#include "ast/expr/int_expr.h"
#include "ast/expr/real_expr.h"
#include "ast/expr/bool_expr.h"
#include "ast/expr/string_expr.h"
#include "ast/expr/variable_expr.h"
#include "ast/expr/function_call_expr.h"
#include "ast/expr/assign_expr.h"
#include "ast/expr/var_decl_expr.h"
#include "ast/expr/empty_expr.h"
#include "ast/expr/error_expr.h"

// Statements
#include "ast/stmt/stmt.h"
#include "ast/stmt/compound_stmt.h"
#include "ast/stmt/elif_stmt.h"
#include "ast/stmt/empty_stmt.h"
#include "ast/stmt/expr_stmt.h"
#include "ast/stmt/if_stmt.h"
#include "ast/stmt/break_stmt.h"
#include "ast/stmt/continue_stmt.h"
#include "ast/stmt/return_stmt.h"
#include "ast/stmt/loop_for_stmt.h"
#include "ast/stmt/loop_while_stmt.h"
#include "ast/stmt/loop_do_while_stmt.h"
#include "ast/stmt/error_stmt.h"
#include "ast/stmt/instruct_stmt.h"
#include "ast/stmt/decl_stmt.h"

// Literals
#include "ast/literal/literal.h"
#include "ast/literal/int_literal.h"
#include "ast/literal/real_literal.h"
#include "ast/literal/string_literal.h"
#include "ast/literal/bool_literal.h"

// Types
#include "ast/type/type.h"
#include "ast/type/int_type.h"
#include "ast/type/real_type.h"
#include "ast/type/string_type.h"
#include "ast/type/bool_type.h"
#include "ast/type/void_type.h"
#include "ast/type/error_type.h"
#include "ast/type/object_type.h"
#include "ast/type/attribute_type.h"

// Decl
#include "ast/decl/decl.h"
#include "ast/decl/var_decl.h"
#include "ast/decl/func_decl.h"
#include "ast/decl/param.h"

// Operators
#include "ast/op/operator.h"
#include "ast/op/assign_op.h"
#include "ast/op/add_op.h"
#include "ast/op/sub_op.h"
#include "ast/op/div_op.h"
#include "ast/op/mul_op.h"
#include "ast/op/mod_op.h"
#include "ast/op/post_unary_add_op.h"
#include "ast/op/post_unary_sub_op.h"
#include "ast/op/pre_unary_add_op.h"
#include "ast/op/post_unary_sub_op.h"

//Terminals
#include "ast/terminal.h"

// Identifier
#include "ast/identifier.h"

// Variable
#include "ast/var/Variable.h"

// Lists
#include "ast/list/list.h"
#include "ast/list/elif_list.h"
#include "ast/list/empty_elif_list.h"
#include "ast/list/arg_list.h"
#include "ast/list/arg.h"
#include "ast/list/empty_arg_list.h"
#include "ast/list/param_list.h"
#include "ast/list/empty_param_list.h"
#include "ast/list/block_item_list.h"
#include "ast/list/empty_block_list.h"
#include "ast/list/block.h"
#include "ast/list/stmt_block.h"
#include "ast/list/var_decl_block.h"
#include "ast/list/var_decl_list.h"
#include "ast/list/empty_var_decl_list.h"
#include "ast/list/func_decl_list.h"
#include "ast/list/empty_func_decl_list.h"
        
#endif