#ifndef LEXEMES_H
#define LEXEMES_H

// Types
#include "lexicon/type/int.h"
#include "lexicon/type/real.h"
#include "lexicon/type/bool.h"
#include "lexicon/type/string.h"
#include "lexicon/type/void.h"
#include "lexicon/type/attribute.h"
#include "lexicon/type/object.h"

// Values
#include "lexicon/type/int_value.h"
#include "lexicon/type/real_value.h"
#include "lexicon/type/bool_value.h"
#include "lexicon/type/string_value.h"

// Operators
#include "lexicon/operator/add.h"
#include "lexicon/operator/sub.h"
#include "lexicon/operator/mul.h"
#include "lexicon/operator/div.h"
#include "lexicon/operator/mod.h"

// Unary Operations
#include "lexicon/operator/unary_add.h"
#include "lexicon/operator/unary_sub.h"

// Assign Operators
#include "lexicon/operator/assign.h"
#include "lexicon/operator/add_assign.h"
#include "lexicon/operator/sub_assign.h"
#include "lexicon/operator/div_assign.h"
#include "lexicon/operator/mul_assign.h"


#include "lexicon/operator/not.h"
#include "lexicon/operator/equal.h"
#include "lexicon/operator/nequal.h"
#include "lexicon/operator/less.h"
#include "lexicon/operator/greater.h"
#include "lexicon/operator/lequal.h"
#include "lexicon/operator/gequal.h"

// Logical Operators
#include "lexicon/operator/logical_or.h"
#include "lexicon/operator/logical_and.h"

// Keywords
//#include "lexicon/keyword/true.h"
//#include "lexicon/keyword/false.h"
#include "lexicon/keyword/if.h"
#include "lexicon/keyword/elif.h"
#include "lexicon/keyword/else.h"
#include "lexicon/keyword/for.h"
#include "lexicon/keyword/while.h"
#include "lexicon/keyword/do.h"
#include "lexicon/keyword/break.h"
#include "lexicon/keyword/continue.h"
#include "lexicon/keyword/loop.h"
#include "lexicon/keyword/return.h"
#include "lexicon/keyword/until.h"
#include "lexicon/keyword/is.h"
#include "lexicon/keyword/equal_kwd.h"
#include "lexicon/keyword/not_kwd.h"
#include "lexicon/keyword/define.h"
#include "lexicon/keyword/call.h"

// Misc
#include "lexicon/misc/oparen.h"
#include "lexicon/misc/osparen.h"
#include "lexicon/misc/ocurl.h"
#include "lexicon/misc/cparen.h"
#include "lexicon/misc/csparen.h"
#include "lexicon/misc/ccurl.h"
#include "lexicon/misc/identifier.h"
#include "lexicon/misc/error.h"
#include "lexicon/misc/eof.h"
#include "lexicon/misc/semicolon.h"
#include "lexicon/misc/colon.h"
#include "lexicon/misc/comma.h"
#include "lexicon/misc/newline.h"
#include "lexicon/misc/is.h"
#include "lexicon/misc/right_arrow.h"

// Instruct token
#include "lexicon/misc/instruct.h"

#endif