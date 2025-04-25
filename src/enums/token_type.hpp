#pragma once

namespace enums
{
  enum token_type
  {
    /// // or /* */
    TCOMMENT,
    /// [
    TBRACKETS_OPEN,
    /// ]
    TBRACKETS_CLOSE,
    /// {
    TBRACES_OPEN,
    /// }
    TBRACES_CLOSE,
    /// (
    TPARENTHESIS_OPEN,
    /// )
    TPARENTHESIS_CLOSE,
    /// statement
    NSTAT,
    /// ,
    TCOMMA,
    /// :
    TCOLON,
    /// .
    TDOT,
    /// ;
    TSEMICOLON,
    /// value
    NVAL,
    /// (value, ...)
    NTUPLE_VAL,
    /// [value, ...]
    NARRAY_VAL,
    /// [key:value, ...]
    NMAP_VAL,
    /// value as an id
    NVAL_AS_ID,
    /// value as an id
    NVAL_AS_BOOLEAN,
    /// value as int
    NVAL_AS_INT_NUM,
    /// value as double
    NVAL_AS_DOUBLE_NUM,
    /// value as char array
    NVAL_AS_CHAR_ARRAY,
    /// value as flow parameter val
    NVAL_AS_PARAM_FROM_FLOW_VAL,
    /// #x
    NVAL_AS_SIZEOF,
    /// single value
    NSINGLE_VAL,
    /// single val without pre/pos increment/decrement
    NSINGLE_VAL_PREDICATE,
    /// suffixed value
    NSUFIXED_VAL,
    /// used for OR
    NSEVENTH_PRIORITY_RHS_VAL,
    /// used for AND
    NSIXTH_PRIORITY_RHS_VAL,
    /// used for == and !=
    NFIFTH_PRIORITY_RHS_VAL,
    /// used for <, <=, >=, >
    NFOURTH_PRIORITY_RHS_VAL,
    /// used for -
    NTHIRD_PRIORITY_RHS_VAL,
    /// used for +
    NSECOND_PRIORITY_RHS_VAL,
    /// used for *, / and %
    NFIRST_PRIORITY_RHS_VAL,
    /// symbol id
    TID,
    /// id:prop:prop....
    NID,
    /// id || id<type> | string | number | undefined | null
    NTYPE,
    /// signature (...) for function declaration
    NSUFFIX_ID_SIGNATURE,
    /// index or name property
    NSUFFIX_PROPERTY,
    /// function call
    NSUFFIX_FUNCTION_CALL,
    /// ID : TYPE = VAL
    NSUFFIX_VAR_CONST_DEFINITION,
    NSUFFIX_VAL_NTERNARY,
    NIMPORT_STAT,
    NEXPORT_STAT,
    /// integer number
    TINT_NUM,
    /// double number
    TDOUBLE_NUM,
    /// text
    TCHAR_ARRAY,
    /// boolean value
    NBOOLEAN,
    /// xml
    NXML,
    /// +
    TPLUS,
    /// ++
    TPLUS_PLUS,
    /// +=
    TPLUS_EQU,
    /// -
    TMINUS,
    /// --
    TMINUS_MINUS,
    /// -=
    TMINUS_EQU,
    /// *
    TTIMES,
    /// *=
    TTIMES_EQU,
    /// /
    TSLASH,
    /// /=
    TSLASH_EQU,
    /// %
    TMODULO,
    /// !
    TNOT,
    /// ||
    TOR,
    /// &&
    TAND,
    /// %=
    TMODULO_EQU,

    /// >
    TGREATER,
    /// >=
    TGREATER_OR_EQUAL,
    /// <
    TLOWER,
    /// <=
    TLOWER_OR_EQUAL,
    /// ==
    TEQUAL,
    /// !=
    TNOT_EQUAL,
    /// Conjugation by single val
    NCONJUGATION_BY_SINGLE_VAL,
    /// + value
    NPLUS_VAL,
    /// - value
    NMINUS_VAL,
    /// * value
    NTIMES_VAL,
    /// / value
    NSLASH_VAL,
    /// % value
    NMODULO_VAL,
    /// > value
    NGREATER_VAL,
    /// >= value
    NGREATER_OR_EQUAL_VAL,
    /// < value
    NLOWER_VAL,
    /// <= value
    NLOWER_OR_EQUAL_VAL,
    /// == value
    NEQUAL_VAL,
    /// != value
    NNOT_EQUAL_VAL,
    /// ! value
    NNOT_VAL,
    /// and value
    NAND_VAL,
    /// or value
    NOR_VAL,

    /// -> value
    NFLOW_VAL,

    /// match(x)[x,y,z]
    NMATCH,
    /// val ? val : val
    NTERNARY,

    /// ?
    TQUESTION,
    /// $
    TDOLLAR,

    /// namespace name { stat } or namespace name
    NNAMESPACE,
    /// struct name { stat } or struct name
    NSTRUCT,

    /// =
    TEQU,
    /// for
    TKEYWORD_FOR,
    /// while
    TKEYWORD_WHILE,
    /// if
    TKEYWORD_IF,
    /// else
    TKEYWORD_ELSE,
    /// fun
    TKEYWORD_FUNCTION,
    /// type
    TKEYWORD_TYPE,
    /// mutable
    TKEYWORD_MUTABLE,
    /// yield
    TKEYWORD_YIELD,
    /// when
    TKEYWORD_WHEN,
    /// init
    TKEYWORD_INIT,
    /// this
    TKEYWORD_THIS,
    /// true
    TKEYWORD_TRUE,
    /// false
    TKEYWORD_FALSE,
    // break
    TKEYWORD_BREAK,
    // continue
    TKEYWORD_CONTINUE,
    // return,
    TKEYWORD_RETURN,
    // as
    TKEYWORD_AS,
    // any
    TKEYWORD_ANY,
    // switch
    TKEYWORD_SWITCH,
    // case
    TKEYWORD_CASE,
    // number
    TKEYWORD_NUMBER,
    // string
    TKEYWORD_STRING,
    // typeof
    TKEYWORD_TYPEOF,
    TKEYWORD_UNDEFINED,
    TKEYWORD_NULL,
    TKEYWORD_VAR,
    TKEYWORD_CONST,
    TKEYWORD_IMPORT,
    TKEYWORD_EXPORT,
    NVARIABLE_DEFINITION,
    NCONST_DEFINITION,
    NRETURN,
    NYIELD,
    // NTHROW,
    ///  =|+=|-=|*=|/=|%= VAL
    NSUFFIX_ASGN,
    /// ???
    TERROR
  };
}
