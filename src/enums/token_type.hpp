#pragma once

namespace enums {

enum token_type {
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
  /// <x>
  NVAL_AS_TYPEOF,
  /// #x
  NVAL_AS_SIZEOF,
  /// single value
  NSINGLE_VAL,
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
  /// for
  TKEY_FOR,
  /// while
  TKEY_WHILE,
  /// if
  TKEY_IF,
  /// else
  TKEY_ELSE,
  /// fun
  TKEY_FUN,
  /// type
  TKEY_TYPE,
  /// mut
  TKEY_MUT,
  /// yield
  TKEY_YIELD,
  /// when
  TKEY_WHEN,
  /// init
  TKEY_INIT,
  /// this
  TKEY_THIS,
  /// object
  TKEY_OBJECT,
  /// id:prop:prop....
  NID,
  /// signature (...) for function declaration
  NSUFFIX_ID_SIGNATURE,
  /// index or name property
  NSUFFIX_PROPERTY,
  /// function call
  NSUFFIX_FUNCTION_CALL,

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
  /// not
  TKEY_NOT,
  /// and
  TKEY_AND,
  /// or
  TKEY_OR,
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
  /// val ?? val
  NBINARY,

  /// ?
  TQUESTION,
  /// ??
  TDOUBLE_QUESTION,
  /// $
  TDOLLAR,

  /// namespace name { stat } or namespace name
  NNAMESPACE,
  /// struct name { stat } or struct name
  NSTRUCT,

  /// =
  TEQU,
  /// true
  TKEY_TRUE,
  /// false
  TKEY_FALSE,
  /// is
  TKEY_IS,
  /// ID = VAL
  NASGN,
  /// ???
  TERROR
};
}