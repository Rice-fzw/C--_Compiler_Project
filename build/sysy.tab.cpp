/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 13 "/root/src/sysy.y"

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "AST.h"
#include "lexer.h"

// 声明 lexer 函数和错误处理函数
int yylex();
void yyerror(std::unique_ptr<BaseAST> &ast, const char *s);
extern YYSTYPE yylval;
extern int yydebug;

using namespace std;


#line 88 "/root/build\r/sysy.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_ROOT_BUILD_SYSY_TAB_HPP_INCLUDED
# define YY_YY_ROOT_BUILD_SYSY_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 4 "/root/src/sysy.y"

  #include <memory>
  #include <string>
  #include <iostream>
  #include <vector>
  #include "AST.h"
  #include "lexer.h"

#line 140 "/root/build\r/sysy.tab.cpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    RETURN = 259,
    CONST = 260,
    VOID = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    BREAK = 265,
    CONTINUE = 266,
    LE = 267,
    GE = 268,
    EQ = 269,
    NE = 270,
    LAND = 271,
    LOR = 272,
    SHL = 273,
    SAR = 274,
    AA = 275,
    MM = 276,
    AE = 277,
    ME = 278,
    UE = 279,
    DE = 280,
    PRE_AA = 281,
    PRE_MM = 282,
    POST_AA = 283,
    POST_MM = 284,
    IDENT = 285,
    INT_CONST = 286
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 33 "/root/src/sysy.y"

  std::string *str_val; 
  int int_val;
  BaseAST *ast_val;
  std::vector<std::unique_ptr<BaseAST>> *vec_val;

#line 190 "/root/build\r/sysy.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (std::unique_ptr<BaseAST> &ast);

#endif /* !YY_YY_ROOT_BUILD_SYSY_TAB_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   306

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  200

#define YYUNDEFTOK  2
#define YYMAXUTOK   286


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,     2,     2,    36,    29,     2,
      50,    51,    34,    32,    45,    33,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    44,
      30,    26,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,    47,    28,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,    27,    49,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    94,    94,   106,   120,   123,   129,   132,   138,   144,
     149,   157,   163,   166,   176,   179,   183,   190,   195,   202,
     208,   213,   221,   224,   227,   233,   242,   245,   249,   255,
     260,   268,   271,   274,   277,   292,   297,   305,   311,   314,
     320,   325,   333,   336,   342,   345,   348,   351,   354,   357,
     360,   363,   366,   372,   375,   381,   384,   390,   393,   398,
     403,   408,   416,   420,   429,   432,   435,   440,   446,   449,
     452,   455,   458,   461,   464,   467,   470,   473,   479,   485,
     493,   496,   502,   505,   508,   514,   517,   523,   526,   532,
     535,   538,   544,   547,   550,   553,   556,   562,   565,   568,
     574,   577,   583,   586,   592,   595,   601,   604,   610,   613,
     619
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "RETURN", "CONST", "VOID", "IF",
  "ELSE", "WHILE", "BREAK", "CONTINUE", "LE", "GE", "EQ", "NE", "LAND",
  "LOR", "SHL", "SAR", "AA", "MM", "AE", "ME", "UE", "DE", "'='", "'|'",
  "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'",
  "PRE_AA", "PRE_MM", "POST_AA", "POST_MM", "IDENT", "INT_CONST", "';'",
  "','", "'['", "']'", "'{'", "'}'", "'('", "')'", "$accept", "CompUnit",
  "CompUnitItem", "Decl", "ConstDecl", "ConstDefList", "BType", "ConstDef",
  "ConstInitVal", "ConstExpList", "VarDecl", "VarDefList", "VarDef",
  "InitVal", "InitValList", "FuncDef", "FuncFParams", "FuncFParam",
  "Block", "BlockItems", "BlockItem", "Stmt", "OptionalExp", "Exp",
  "AssignExp", "LVal", "PrimaryExp", "Number", "UnaryExp", "FuncRParams",
  "MulExp", "Mulop", "AddExp", "Addop", "ShiftExp", "RelExp", "EqExp",
  "BitAndExp", "BitXorExp", "BitOrExp", "LAndExp", "LOrExp", "ConstExp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    61,   124,    94,    38,
      60,    62,    43,    45,    42,    47,    37,    33,   281,   282,
     283,   284,   285,   286,    59,    44,    91,    93,   123,   125,
      40,    41
};
# endif

#define YYPACT_NINF (-94)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     184,   -94,    13,   -38,    91,   -94,   -94,   -94,    76,   -21,
     -94,   -94,    -3,   -18,   -94,   -94,   -94,    -3,    -9,   117,
     -94,   -12,   -94,     4,   -94,   223,   256,    10,   -94,     6,
     237,   256,    12,    21,   -20,   -94,   256,   256,   256,   256,
     256,    49,   -94,   204,   256,   -94,   -94,   -94,    92,   -94,
     -94,   151,   181,   173,   210,    39,   216,    43,    60,    63,
      86,    93,   -94,    61,    12,    -2,    -4,   -94,   104,   -94,
     -94,    85,   171,   -94,   -94,    13,    12,   -94,   151,   151,
     151,   151,   151,   256,     3,   -94,   -94,   111,    87,   256,
     256,   256,   256,   256,   -94,   -94,   -94,   -94,   -94,   256,
     -94,   -94,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   125,   -94,    12,   -94,
     114,   -94,   138,   256,    90,   127,    99,   123,   -94,   -94,
       6,   -94,   190,   -94,   -94,   135,   -94,   105,   -94,   -94,
     141,   -94,   -94,    11,   223,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   151,   181,   173,   173,   210,   210,   210,   210,
      39,    39,   216,    43,    60,    63,    86,   223,   -94,   256,
     -94,   237,   152,   256,   256,   -94,   -94,   -94,   -94,   -94,
     256,   -94,   256,   -94,   -94,   -94,   -94,   -94,   -94,   147,
     156,   158,   -94,   102,   102,   -94,   201,   -94,   102,   -94
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    11,     0,     0,     0,     2,     4,     6,     0,     0,
       7,     5,     0,     0,     1,     3,     8,     0,    22,     0,
      20,     0,     9,     0,    10,     0,     0,     0,    19,     0,
       0,     0,     0,     0,     0,    35,     0,     0,     0,     0,
       0,    62,    67,     0,     0,    23,    26,    56,    66,    68,
      65,    80,    85,    89,    92,    97,   100,   102,   104,   106,
     108,    55,   110,     0,     0,     0,    22,    21,     0,    12,
      14,     0,    53,    33,    37,     0,     0,    66,    72,    73,
      69,    70,    71,     0,     0,    27,    29,     0,     0,     0,
       0,     0,     0,     0,    74,    75,    82,    83,    84,     0,
      87,    88,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    24,    31,     0,    15,
       0,    17,     0,    53,     0,     0,     0,     0,    39,    42,
       0,    47,    53,    40,    43,     0,    54,    66,    36,    34,
       0,    77,    78,     0,     0,    28,    64,    58,    59,    60,
      61,    57,    81,    86,    90,    91,    95,    96,    93,    94,
      98,    99,   101,   103,   105,   107,   109,     0,    32,     0,
      16,     0,     0,     0,     0,    51,    52,    38,    41,    46,
       0,    63,     0,    76,    30,    25,    18,    13,    44,     0,
       0,     0,    79,    53,    53,    45,    48,    50,    53,    49
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -94,   -94,   208,   -39,   -94,   -94,     1,   209,    47,   -94,
     -94,   -94,   213,   -41,   -94,   -94,   218,   175,   -26,   -94,
     119,   -93,   136,   -25,   -94,   -28,   -94,   -94,   -10,   -94,
     159,   -94,   131,   -94,    78,   139,   153,   150,   154,   149,
     157,   -94,   -11
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    33,    22,    69,   120,
      10,    19,    20,    45,    87,    11,    34,    35,   131,   132,
     133,   134,   135,    62,    47,    48,    49,    50,    51,   143,
      52,    99,    53,   102,    54,    55,    56,    57,    58,    59,
      60,    61,    70
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      46,     9,    86,    12,    13,     9,    73,     1,    77,    77,
      77,    77,    77,     1,    30,    63,     1,    25,    46,    88,
      71,    18,    25,    36,    37,    75,    78,    79,    80,    81,
      82,    76,    23,   129,    31,    38,    39,    26,   117,    21,
      40,    27,    26,    75,   137,    41,    42,   136,    66,   118,
     139,   105,   106,    44,   141,    32,   182,   121,   140,   142,
      72,    64,   183,    74,   147,   148,   149,   150,   151,   107,
     108,    77,   111,   130,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,   112,   152,
     113,    14,   168,   129,     1,    83,     2,     3,   136,    84,
     196,   197,   114,   184,   137,   199,   123,   136,   116,   124,
     115,   125,   126,   127,    89,    90,    91,    92,    93,    46,
      16,    17,    36,    37,    36,    37,   185,    89,    90,    91,
      92,   180,   122,   130,    38,    39,    38,    39,   146,    40,
     173,    40,    46,   175,    41,    42,    41,    42,   189,   190,
      72,   167,    44,   119,    44,   191,   144,   192,   186,   169,
     145,    28,    29,   170,   171,   137,   137,   176,   136,   136,
     137,    94,    95,   136,     1,   123,     2,   174,   124,   179,
     125,   126,   127,   156,   157,   158,   159,     1,   181,     2,
       3,    36,    37,     1,   123,     2,   188,   124,   193,   125,
     126,   127,   195,    38,    39,   100,   101,   194,    40,   198,
      36,    37,    15,    41,    42,    96,    97,    98,   187,    72,
     128,    44,    38,    39,    36,    37,    24,    40,   103,   104,
     109,   110,    41,    42,   154,   155,    38,    39,    72,   177,
      44,    40,    67,    36,    37,    65,    41,    42,   160,   161,
     138,   178,    43,    85,    44,    38,    39,    36,    37,   172,
      40,   153,   163,   165,   162,    41,    42,   164,     0,    38,
      39,    43,   166,    44,    40,     0,    36,    37,     0,    41,
      42,     0,     0,     0,     0,    68,     0,    44,    38,    39,
       0,     0,     0,    40,     0,     0,     0,     0,    41,    42,
       0,     0,     0,     0,     0,     0,    44
};

static const yytype_int16 yycheck[] =
{
      25,     0,    43,     2,    42,     4,    32,     3,    36,    37,
      38,    39,    40,     3,    26,    26,     3,    26,    43,    44,
      31,    42,    26,    20,    21,    45,    36,    37,    38,    39,
      40,    51,    50,    72,    46,    32,    33,    46,    64,    42,
      37,    50,    46,    45,    72,    42,    43,    72,    42,    51,
      76,    12,    13,    50,    51,    51,    45,    68,    83,    84,
      48,    51,    51,    42,    89,    90,    91,    92,    93,    30,
      31,    99,    29,    72,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    28,    99,
      27,     0,   118,   132,     3,    46,     5,     6,   123,    50,
     193,   194,    16,   144,   132,   198,     4,   132,    47,     7,
      17,     9,    10,    11,    22,    23,    24,    25,    26,   144,
      44,    45,    20,    21,    20,    21,   167,    22,    23,    24,
      25,    26,    47,   132,    32,    33,    32,    33,    51,    37,
      50,    37,   167,    44,    42,    43,    42,    43,   173,   174,
      48,    26,    50,    49,    50,   180,    45,   182,   169,    45,
      49,    44,    45,    49,    26,   193,   194,    44,   193,   194,
     198,    20,    21,   198,     3,     4,     5,    50,     7,    44,
       9,    10,    11,   105,   106,   107,   108,     3,    47,     5,
       6,    20,    21,     3,     4,     5,    44,     7,    51,     9,
      10,    11,    44,    32,    33,    32,    33,    51,    37,     8,
      20,    21,     4,    42,    43,    34,    35,    36,   171,    48,
      49,    50,    32,    33,    20,    21,    17,    37,    18,    19,
      14,    15,    42,    43,   103,   104,    32,    33,    48,    49,
      50,    37,    29,    20,    21,    27,    42,    43,   109,   110,
      75,   132,    48,    49,    50,    32,    33,    20,    21,   123,
      37,   102,   112,   114,   111,    42,    43,   113,    -1,    32,
      33,    48,   115,    50,    37,    -1,    20,    21,    -1,    42,
      43,    -1,    -1,    -1,    -1,    48,    -1,    50,    32,    33,
      -1,    -1,    -1,    37,    -1,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     6,    53,    54,    55,    56,    57,    58,
      62,    67,    58,    42,     0,    54,    44,    45,    42,    63,
      64,    42,    59,    50,    59,    26,    46,    50,    44,    45,
      26,    46,    51,    58,    68,    69,    20,    21,    32,    33,
      37,    42,    43,    48,    50,    65,    75,    76,    77,    78,
      79,    80,    82,    84,    86,    87,    88,    89,    90,    91,
      92,    93,    75,    94,    51,    68,    42,    64,    48,    60,
      94,    94,    48,    70,    42,    45,    51,    77,    80,    80,
      80,    80,    80,    46,    50,    49,    65,    66,    75,    22,
      23,    24,    25,    26,    20,    21,    34,    35,    36,    83,
      32,    33,    85,    18,    19,    12,    13,    30,    31,    14,
      15,    29,    28,    27,    16,    17,    47,    70,    51,    49,
      61,    94,    47,     4,     7,     9,    10,    11,    49,    55,
      58,    70,    71,    72,    73,    74,    75,    77,    69,    70,
      75,    51,    75,    81,    45,    49,    51,    75,    75,    75,
      75,    75,    80,    82,    84,    84,    86,    86,    86,    86,
      87,    87,    88,    89,    90,    91,    92,    26,    70,    45,
      49,    26,    74,    50,    50,    44,    44,    49,    72,    44,
      26,    47,    45,    51,    65,    65,    94,    60,    44,    75,
      75,    75,    75,    51,    51,    44,    73,    73,     8,    73
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    53,    54,    54,    55,    55,    56,    57,
      57,    58,    59,    59,    60,    60,    60,    61,    61,    62,
      63,    63,    64,    64,    64,    64,    65,    65,    65,    66,
      66,    67,    67,    67,    67,    68,    68,    69,    70,    70,
      71,    71,    72,    72,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    74,    74,    75,    75,    76,    76,    76,
      76,    76,    77,    77,    78,    78,    78,    79,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    81,    81,
      82,    82,    83,    83,    83,    84,    84,    85,    85,    86,
      86,    86,    87,    87,    87,    87,    87,    88,    88,    88,
      89,    89,    90,    90,    91,    91,    92,    92,    93,    93,
      94
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     3,
       3,     1,     3,     6,     1,     2,     3,     1,     3,     3,
       1,     3,     1,     3,     4,     6,     1,     2,     3,     1,
       3,     5,     6,     5,     6,     1,     3,     2,     3,     2,
       1,     2,     1,     1,     3,     4,     2,     1,     5,     7,
       5,     2,     2,     0,     1,     1,     1,     3,     3,     3,
       3,     3,     1,     4,     3,     1,     1,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     4,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     3,     1,     1,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (ast, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, ast); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, std::unique_ptr<BaseAST> &ast)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (ast);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, std::unique_ptr<BaseAST> &ast)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, ast);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, std::unique_ptr<BaseAST> &ast)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , ast);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, ast); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, std::unique_ptr<BaseAST> &ast)
{
  YYUSE (yyvaluep);
  YYUSE (ast);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (std::unique_ptr<BaseAST> &ast)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 94 "/root/src/sysy.y"
                 {
      auto comp_unit = new CompUnitAST();
      // 根据类型添加到对应vector中
      if (auto* decl = dynamic_cast<ConstDeclAST*>((yyvsp[0].ast_val))) {
          comp_unit->addDecl((yyvsp[0].ast_val));
      } else if (auto* decl = dynamic_cast<VarDeclAST*>((yyvsp[0].ast_val))) {
          comp_unit->addDecl((yyvsp[0].ast_val));
      } else {
          comp_unit->addFuncDef((yyvsp[0].ast_val));
      }
      ast = std::unique_ptr<BaseAST>(comp_unit);
  }
#line 1542 "/root/build\r/sysy.tab.cpp"
    break;

  case 3:
#line 106 "/root/src/sysy.y"
                          {
      auto comp_unit = static_cast<CompUnitAST*>(ast.get());
      // 根据类型添加到对应vector中
      if (auto* decl = dynamic_cast<ConstDeclAST*>((yyvsp[0].ast_val))) {
          comp_unit->addDecl((yyvsp[0].ast_val));
      } else if (auto* decl = dynamic_cast<VarDeclAST*>((yyvsp[0].ast_val))) {
          comp_unit->addDecl((yyvsp[0].ast_val));
      } else {
          comp_unit->addFuncDef((yyvsp[0].ast_val));
      }
  }
#line 1558 "/root/build\r/sysy.tab.cpp"
    break;

  case 4:
#line 120 "/root/src/sysy.y"
         {
      (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 1566 "/root/build\r/sysy.tab.cpp"
    break;

  case 5:
#line 123 "/root/src/sysy.y"
            {
      (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 1574 "/root/build\r/sysy.tab.cpp"
    break;

  case 6:
#line 129 "/root/src/sysy.y"
              {
    (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 1582 "/root/build\r/sysy.tab.cpp"
    break;

  case 7:
#line 132 "/root/src/sysy.y"
            {
    (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 1590 "/root/build\r/sysy.tab.cpp"
    break;

  case 8:
#line 138 "/root/src/sysy.y"
                    {
    (yyval.ast_val) = (yyvsp[-1].ast_val);  // Use ConstDefList as AST
  }
#line 1598 "/root/build\r/sysy.tab.cpp"
    break;

  case 9:
#line 144 "/root/src/sysy.y"
                         {  // single variable: const int x = 1;
    std::vector<std::unique_ptr<ConstDefAST>> defs;
    defs.push_back(std::unique_ptr<ConstDefAST>(static_cast<ConstDefAST*>((yyvsp[0].ast_val))));
    (yyval.ast_val) = new ConstDeclAST(*(yyvsp[-1].str_val), std::move(defs));
  }
#line 1608 "/root/build\r/sysy.tab.cpp"
    break;

  case 10:
#line 149 "/root/src/sysy.y"
                              {  // Multiple variables: const int x = 1, y = 2;
    auto decl = static_cast<ConstDeclAST*>((yyvsp[-2].ast_val));
    decl->const_defs.push_back(std::unique_ptr<ConstDefAST>(static_cast<ConstDefAST*>((yyvsp[0].ast_val))));
    (yyval.ast_val) = decl;
  }
#line 1618 "/root/build\r/sysy.tab.cpp"
    break;

  case 11:
#line 157 "/root/src/sysy.y"
        {
    (yyval.str_val) = new string("int");
  }
#line 1626 "/root/build\r/sysy.tab.cpp"
    break;

  case 12:
#line 163 "/root/src/sysy.y"
                           {
    (yyval.ast_val) = new ConstDefAST("=", *(yyvsp[-2].str_val), std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 1634 "/root/build\r/sysy.tab.cpp"
    break;

  case 13:
#line 166 "/root/src/sysy.y"
                                            {
    std::vector<std::unique_ptr<BaseAST>> dims;
    dims.push_back(std::unique_ptr<BaseAST>((yyvsp[-3].ast_val)));
    (yyval.ast_val) = new ConstArrayDefAST(*(yyvsp[-5].str_val), std::move(dims), std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
    delete (yyvsp[-5].str_val);
  }
#line 1645 "/root/build\r/sysy.tab.cpp"
    break;

  case 14:
#line 176 "/root/src/sysy.y"
             {
    (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 1653 "/root/build\r/sysy.tab.cpp"
    break;

  case 15:
#line 179 "/root/src/sysy.y"
            {
    std::vector<std::unique_ptr<BaseAST>> empty_elements;
    (yyval.ast_val) = new ArrayInitValAST(std::move(empty_elements), true);
  }
#line 1662 "/root/build\r/sysy.tab.cpp"
    break;

  case 16:
#line 183 "/root/src/sysy.y"
                         {
    (yyval.ast_val) = new ArrayInitValAST(std::move(*((yyvsp[-1].vec_val))), true);
    delete (yyvsp[-1].vec_val);
  }
#line 1671 "/root/build\r/sysy.tab.cpp"
    break;

  case 17:
#line 190 "/root/src/sysy.y"
             {
    auto list = new std::vector<std::unique_ptr<BaseAST>>();
    list->push_back(std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
    (yyval.vec_val) = list;
  }
#line 1681 "/root/build\r/sysy.tab.cpp"
    break;

  case 18:
#line 195 "/root/src/sysy.y"
                              {
      (yyvsp[-2].vec_val)->push_back(std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
      (yyval.vec_val) = (yyvsp[-2].vec_val);
  }
#line 1690 "/root/build\r/sysy.tab.cpp"
    break;

  case 19:
#line 202 "/root/src/sysy.y"
                         {
      (yyval.ast_val) = (yyvsp[-1].ast_val); // Use VarDefList as AST
  }
#line 1698 "/root/build\r/sysy.tab.cpp"
    break;

  case 20:
#line 208 "/root/src/sysy.y"
           { // Single variable: int x; int x = 1;
      std::vector<std::unique_ptr<VarDefAST>> defs;
      defs.push_back(std::unique_ptr<VarDefAST>(static_cast<VarDefAST*>((yyvsp[0].ast_val))));
      (yyval.ast_val) = new VarDeclAST("int", std::move(defs));
  }
#line 1708 "/root/build\r/sysy.tab.cpp"
    break;

  case 21:
#line 213 "/root/src/sysy.y"
                          { //Multiple variables: int x = 1, y = 2;
      auto decl = static_cast<VarDeclAST*>((yyvsp[-2].ast_val));
      decl->var_defs.push_back(std::unique_ptr<VarDefAST>(static_cast<VarDefAST*>((yyvsp[0].ast_val))));
      (yyval.ast_val) = decl;
  }
#line 1718 "/root/build\r/sysy.tab.cpp"
    break;

  case 22:
#line 221 "/root/src/sysy.y"
          {
      (yyval.ast_val) = new VarDefAST(*(yyvsp[0].str_val));
  }
#line 1726 "/root/build\r/sysy.tab.cpp"
    break;

  case 23:
#line 224 "/root/src/sysy.y"
                      {
      (yyval.ast_val) = new VarDefAST("=", *(yyvsp[-2].str_val), std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 1734 "/root/build\r/sysy.tab.cpp"
    break;

  case 24:
#line 227 "/root/src/sysy.y"
                           {
      std::vector<std::unique_ptr<BaseAST>> dims;
      dims.push_back(std::unique_ptr<BaseAST>((yyvsp[-1].ast_val)));
      (yyval.ast_val) = new VarArrayDefAST(*(yyvsp[-3].str_val), std::move(dims));
      delete (yyvsp[-3].str_val);
  }
#line 1745 "/root/build\r/sysy.tab.cpp"
    break;

  case 25:
#line 233 "/root/src/sysy.y"
                                       {
      std::vector<std::unique_ptr<BaseAST>> dims;
      dims.push_back(std::unique_ptr<BaseAST>((yyvsp[-3].ast_val)));
      (yyval.ast_val) = new VarArrayDefAST(*(yyvsp[-5].str_val), std::move(dims), std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
      delete (yyvsp[-5].str_val);
  }
#line 1756 "/root/build\r/sysy.tab.cpp"
    break;

  case 26:
#line 242 "/root/src/sysy.y"
        {
      (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 1764 "/root/build\r/sysy.tab.cpp"
    break;

  case 27:
#line 245 "/root/src/sysy.y"
            {
    std::vector<std::unique_ptr<BaseAST>> empty_elements;
    (yyval.ast_val) = new ArrayInitValAST(std::move(empty_elements), false);
  }
#line 1773 "/root/build\r/sysy.tab.cpp"
    break;

  case 28:
#line 249 "/root/src/sysy.y"
                        {
    (yyval.ast_val) = (yyvsp[-1].ast_val);
  }
#line 1781 "/root/build\r/sysy.tab.cpp"
    break;

  case 29:
#line 255 "/root/src/sysy.y"
            {
    std::vector<std::unique_ptr<BaseAST>> elements;
    elements.push_back(std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
    (yyval.ast_val) = new ArrayInitValAST(std::move(elements), false);
  }
#line 1791 "/root/build\r/sysy.tab.cpp"
    break;

  case 30:
#line 260 "/root/src/sysy.y"
                            {
      auto list = static_cast<ArrayInitValAST*>((yyvsp[-2].ast_val));
      list->elements.push_back(std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
      (yyval.ast_val) = list;
  }
#line 1801 "/root/build\r/sysy.tab.cpp"
    break;

  case 31:
#line 268 "/root/src/sysy.y"
                              {
    (yyval.ast_val) = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST(*((yyvsp[-4].str_val)))), *(yyvsp[-3].str_val), std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 1809 "/root/build\r/sysy.tab.cpp"
    break;

  case 32:
#line 271 "/root/src/sysy.y"
                                          {
    (yyval.ast_val) = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST(*((yyvsp[-5].str_val)))), *(yyvsp[-4].str_val), std::unique_ptr<FuncFParamListAST>(static_cast<FuncFParamListAST*>((yyvsp[-2].ast_val))), std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 1817 "/root/build\r/sysy.tab.cpp"
    break;

  case 33:
#line 274 "/root/src/sysy.y"
                             {
    (yyval.ast_val) = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST("void")), *(yyvsp[-3].str_val), std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 1825 "/root/build\r/sysy.tab.cpp"
    break;

  case 34:
#line 277 "/root/src/sysy.y"
                                         {
    (yyval.ast_val) = new FuncDefAST(std::unique_ptr<BaseAST>(new FuncTypeAST("void")), *(yyvsp[-4].str_val), std::unique_ptr<FuncFParamListAST>(static_cast<FuncFParamListAST*>((yyvsp[-2].ast_val))), std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 1833 "/root/build\r/sysy.tab.cpp"
    break;

  case 35:
#line 292 "/root/src/sysy.y"
               {
      auto param_list = new FuncFParamListAST(std::vector<std::unique_ptr<FuncFParamAST>>());
      param_list->params.push_back(std::unique_ptr<FuncFParamAST>(static_cast<FuncFParamAST*>((yyvsp[0].ast_val))));
      (yyval.ast_val) = param_list;
  }
#line 1843 "/root/build\r/sysy.tab.cpp"
    break;

  case 36:
#line 297 "/root/src/sysy.y"
                               {
      auto param_list = static_cast<FuncFParamListAST*>((yyvsp[-2].ast_val));
      param_list->params.push_back(std::unique_ptr<FuncFParamAST>(static_cast<FuncFParamAST*>((yyvsp[0].ast_val))));
      (yyval.ast_val) = param_list;
  }
#line 1853 "/root/build\r/sysy.tab.cpp"
    break;

  case 37:
#line 305 "/root/src/sysy.y"
                {
      (yyval.ast_val) = new FuncFParamAST(*(yyvsp[-1].str_val), *(yyvsp[0].str_val));
  }
#line 1861 "/root/build\r/sysy.tab.cpp"
    break;

  case 38:
#line 311 "/root/src/sysy.y"
                       {
    (yyval.ast_val) = (yyvsp[-1].ast_val);
  }
#line 1869 "/root/build\r/sysy.tab.cpp"
    break;

  case 39:
#line 314 "/root/src/sysy.y"
            {  // deal with empty block
    (yyval.ast_val) = new BlockAST();
  }
#line 1877 "/root/build\r/sysy.tab.cpp"
    break;

  case 40:
#line 320 "/root/src/sysy.y"
              {
    auto block = new BlockAST();
    block->items.push_back(unique_ptr<BaseAST>((yyvsp[0].ast_val)));
    (yyval.ast_val) = block;
  }
#line 1887 "/root/build\r/sysy.tab.cpp"
    break;

  case 41:
#line 325 "/root/src/sysy.y"
                         {
    auto block = static_cast<BlockAST*>((yyvsp[-1].ast_val));
    block->items.push_back(unique_ptr<BaseAST>((yyvsp[0].ast_val)));
    (yyval.ast_val) = block;
  }
#line 1897 "/root/build\r/sysy.tab.cpp"
    break;

  case 42:
#line 333 "/root/src/sysy.y"
         {
    (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 1905 "/root/build\r/sysy.tab.cpp"
    break;

  case 43:
#line 336 "/root/src/sysy.y"
         {
    (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 1913 "/root/build\r/sysy.tab.cpp"
    break;

  case 44:
#line 342 "/root/src/sysy.y"
                           {
      (yyval.ast_val) = StmtAST::makeReturn((yyvsp[-1].ast_val));
  }
#line 1921 "/root/build\r/sysy.tab.cpp"
    break;

  case 45:
#line 345 "/root/src/sysy.y"
                     {
      (yyval.ast_val) = StmtAST::makeAssign((yyvsp[-3].ast_val), (yyvsp[-1].ast_val));
  }
#line 1929 "/root/build\r/sysy.tab.cpp"
    break;

  case 46:
#line 348 "/root/src/sysy.y"
                    {
      (yyval.ast_val) = StmtAST::makeExpression((yyvsp[-1].ast_val));
  }
#line 1937 "/root/build\r/sysy.tab.cpp"
    break;

  case 47:
#line 351 "/root/src/sysy.y"
          {
      (yyval.ast_val) = StmtAST::makeBlock((yyvsp[0].ast_val));
  }
#line 1945 "/root/build\r/sysy.tab.cpp"
    break;

  case 48:
#line 354 "/root/src/sysy.y"
                        {  // if without else
      (yyval.ast_val) = new IfStmtAST((yyvsp[-2].ast_val), (yyvsp[0].ast_val));
  }
#line 1953 "/root/build\r/sysy.tab.cpp"
    break;

  case 49:
#line 357 "/root/src/sysy.y"
                                  {  // if with else
      (yyval.ast_val) = new IfStmtAST((yyvsp[-4].ast_val), (yyvsp[-2].ast_val), (yyvsp[0].ast_val));
  }
#line 1961 "/root/build\r/sysy.tab.cpp"
    break;

  case 50:
#line 360 "/root/src/sysy.y"
                           {
  (yyval.ast_val) = new WhileStmtAST((yyvsp[-2].ast_val), (yyvsp[0].ast_val));
  }
#line 1969 "/root/build\r/sysy.tab.cpp"
    break;

  case 51:
#line 363 "/root/src/sysy.y"
              {
      (yyval.ast_val) = StmtAST::makeBreak();
  }
#line 1977 "/root/build\r/sysy.tab.cpp"
    break;

  case 52:
#line 366 "/root/src/sysy.y"
                 {
      (yyval.ast_val) = StmtAST::makeContinue();
  }
#line 1985 "/root/build\r/sysy.tab.cpp"
    break;

  case 53:
#line 372 "/root/src/sysy.y"
                {
      (yyval.ast_val) = nullptr;
  }
#line 1993 "/root/build\r/sysy.tab.cpp"
    break;

  case 54:
#line 375 "/root/src/sysy.y"
        {
      (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 2001 "/root/build\r/sysy.tab.cpp"
    break;

  case 55:
#line 381 "/root/src/sysy.y"
           {
    (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 2009 "/root/build\r/sysy.tab.cpp"
    break;

  case 56:
#line 384 "/root/src/sysy.y"
              {
    (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 2017 "/root/build\r/sysy.tab.cpp"
    break;

  case 57:
#line 390 "/root/src/sysy.y"
                 {
    (yyval.ast_val) = StmtAST::makeAssign((yyvsp[-2].ast_val), (yyvsp[0].ast_val));
  }
#line 2025 "/root/build\r/sysy.tab.cpp"
    break;

  case 58:
#line 393 "/root/src/sysy.y"
                {
    auto lval_copy = new LValAST(static_cast<LValAST*>((yyvsp[-2].ast_val))->ident);
    auto add_exp = new AddExpAST("+", std::unique_ptr<BaseAST>(lval_copy), std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
    (yyval.ast_val) = StmtAST::makeAssign((yyvsp[-2].ast_val), add_exp);
  }
#line 2035 "/root/build\r/sysy.tab.cpp"
    break;

  case 59:
#line 398 "/root/src/sysy.y"
                {
    auto lval_copy = new LValAST(static_cast<LValAST*>((yyvsp[-2].ast_val))->ident);
    auto sub_exp = new AddExpAST("-", std::unique_ptr<BaseAST>(lval_copy), std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
    (yyval.ast_val) = StmtAST::makeAssign((yyvsp[-2].ast_val), sub_exp);
  }
#line 2045 "/root/build\r/sysy.tab.cpp"
    break;

  case 60:
#line 403 "/root/src/sysy.y"
                {
    auto lval_copy = new LValAST(static_cast<LValAST*>((yyvsp[-2].ast_val))->ident);
    auto mul_exp = new MulExpAST("*", std::unique_ptr<BaseAST>(lval_copy), std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
    (yyval.ast_val) = StmtAST::makeAssign((yyvsp[-2].ast_val), mul_exp);
  }
#line 2055 "/root/build\r/sysy.tab.cpp"
    break;

  case 61:
#line 408 "/root/src/sysy.y"
                {
    auto lval_copy = new LValAST(static_cast<LValAST*>((yyvsp[-2].ast_val))->ident);
    auto div_exp = new MulExpAST("/", std::unique_ptr<BaseAST>(lval_copy), std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
    (yyval.ast_val) = StmtAST::makeAssign((yyvsp[-2].ast_val), div_exp);
  }
#line 2065 "/root/build\r/sysy.tab.cpp"
    break;

  case 62:
#line 416 "/root/src/sysy.y"
          {
    (yyval.ast_val) = new LValAST(*(yyvsp[0].str_val));
    delete (yyvsp[0].str_val);
  }
#line 2074 "/root/build\r/sysy.tab.cpp"
    break;

  case 63:
#line 420 "/root/src/sysy.y"
                      { /* 一维数组访问 */
    std::vector<std::unique_ptr<BaseAST>> indices;
    indices.push_back(std::unique_ptr<BaseAST>((yyvsp[-1].ast_val)));
    (yyval.ast_val) = new ArrayAccessAST(*(yyvsp[-3].str_val), std::move(indices));
    delete (yyvsp[-3].str_val);
  }
#line 2085 "/root/build\r/sysy.tab.cpp"
    break;

  case 64:
#line 429 "/root/src/sysy.y"
                {
    (yyval.ast_val) = new PrimaryExpAST(unique_ptr<BaseAST>((yyvsp[-1].ast_val)));
  }
#line 2093 "/root/build\r/sysy.tab.cpp"
    break;

  case 65:
#line 432 "/root/src/sysy.y"
           {
    (yyval.ast_val) = new PrimaryExpAST((yyvsp[0].int_val));
  }
#line 2101 "/root/build\r/sysy.tab.cpp"
    break;

  case 66:
#line 435 "/root/src/sysy.y"
         {
    (yyval.ast_val) = new PrimaryExpAST((yyvsp[0].ast_val)); 
  }
#line 2109 "/root/build\r/sysy.tab.cpp"
    break;

  case 67:
#line 440 "/root/src/sysy.y"
              {
    (yyval.int_val) = (yyvsp[0].int_val);
  }
#line 2117 "/root/build\r/sysy.tab.cpp"
    break;

  case 68:
#line 446 "/root/src/sysy.y"
               {
    (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 2125 "/root/build\r/sysy.tab.cpp"
    break;

  case 69:
#line 449 "/root/src/sysy.y"
                           {  // 使用 ! 的优先级
    (yyval.ast_val) = new UnaryExpAST("+", std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2133 "/root/build\r/sysy.tab.cpp"
    break;

  case 70:
#line 452 "/root/src/sysy.y"
                           {  // 使用 ! 的优先级
    (yyval.ast_val) = new UnaryExpAST("-", std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2141 "/root/build\r/sysy.tab.cpp"
    break;

  case 71:
#line 455 "/root/src/sysy.y"
                 {
    (yyval.ast_val) = new UnaryExpAST("!", std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2149 "/root/build\r/sysy.tab.cpp"
    break;

  case 72:
#line 458 "/root/src/sysy.y"
                             {
    (yyval.ast_val) = new UnaryExpAST("++", std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2157 "/root/build\r/sysy.tab.cpp"
    break;

  case 73:
#line 461 "/root/src/sysy.y"
                             {
    (yyval.ast_val) = new UnaryExpAST("--", std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2165 "/root/build\r/sysy.tab.cpp"
    break;

  case 74:
#line 464 "/root/src/sysy.y"
                              {
    (yyval.ast_val) = new UnaryExpAST("post++", std::unique_ptr<BaseAST>((yyvsp[-1].ast_val)));
  }
#line 2173 "/root/build\r/sysy.tab.cpp"
    break;

  case 75:
#line 467 "/root/src/sysy.y"
                              {
    (yyval.ast_val) = new UnaryExpAST("post--", std::unique_ptr<BaseAST>((yyvsp[-1].ast_val)));
  }
#line 2181 "/root/build\r/sysy.tab.cpp"
    break;

  case 76:
#line 470 "/root/src/sysy.y"
                              {
      (yyval.ast_val) = new UnaryExpAST(*(yyvsp[-3].str_val), std::unique_ptr<FuncRParamsAST>(static_cast<FuncRParamsAST*>((yyvsp[-1].ast_val))));
  }
#line 2189 "/root/build\r/sysy.tab.cpp"
    break;

  case 77:
#line 473 "/root/src/sysy.y"
                  { 
      (yyval.ast_val) = new UnaryExpAST(*(yyvsp[-2].str_val)); 
  }
#line 2197 "/root/build\r/sysy.tab.cpp"
    break;

  case 78:
#line 479 "/root/src/sysy.y"
        {
      // 单个参数
      auto params = new FuncRParamsAST(std::vector<std::unique_ptr<BaseAST>>());
      params->params.push_back(std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
      (yyval.ast_val) = params;
  }
#line 2208 "/root/build\r/sysy.tab.cpp"
    break;

  case 79:
#line 485 "/root/src/sysy.y"
                        {
      // 多个参数
      auto params = static_cast<FuncRParamsAST*>((yyvsp[-2].ast_val));
      params->params.push_back(std::unique_ptr<BaseAST>((yyvsp[0].ast_val)));
      (yyval.ast_val) = params;
  }
#line 2219 "/root/build\r/sysy.tab.cpp"
    break;

  case 80:
#line 493 "/root/src/sysy.y"
             {
    (yyval.ast_val) = new MulExpAST(unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2227 "/root/build\r/sysy.tab.cpp"
    break;

  case 81:
#line 496 "/root/src/sysy.y"
                          {
    (yyval.ast_val) = new MulExpAST(*(yyvsp[-1].str_val), unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2235 "/root/build\r/sysy.tab.cpp"
    break;

  case 82:
#line 502 "/root/src/sysy.y"
        {
    (yyval.str_val) = new string("*");
  }
#line 2243 "/root/build\r/sysy.tab.cpp"
    break;

  case 83:
#line 505 "/root/src/sysy.y"
        {
    (yyval.str_val) = new string("/");
  }
#line 2251 "/root/build\r/sysy.tab.cpp"
    break;

  case 84:
#line 508 "/root/src/sysy.y"
        {
    (yyval.str_val) = new string("%");
  }
#line 2259 "/root/build\r/sysy.tab.cpp"
    break;

  case 85:
#line 514 "/root/src/sysy.y"
           {
    (yyval.ast_val) = new AddExpAST(unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2267 "/root/build\r/sysy.tab.cpp"
    break;

  case 86:
#line 517 "/root/src/sysy.y"
                        {
    (yyval.ast_val) = new AddExpAST(*(yyvsp[-1].str_val), unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2275 "/root/build\r/sysy.tab.cpp"
    break;

  case 87:
#line 523 "/root/src/sysy.y"
        {
    (yyval.str_val) = new string("+");
  }
#line 2283 "/root/build\r/sysy.tab.cpp"
    break;

  case 88:
#line 526 "/root/src/sysy.y"
        {
    (yyval.str_val) = new string("-");
  }
#line 2291 "/root/build\r/sysy.tab.cpp"
    break;

  case 89:
#line 532 "/root/src/sysy.y"
           {
    (yyval.ast_val) = new ShiftExpAST(unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2299 "/root/build\r/sysy.tab.cpp"
    break;

  case 90:
#line 535 "/root/src/sysy.y"
                        {
    (yyval.ast_val) = new ShiftExpAST("<<", unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2307 "/root/build\r/sysy.tab.cpp"
    break;

  case 91:
#line 538 "/root/src/sysy.y"
                        {
    (yyval.ast_val) = new ShiftExpAST(">>", unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2315 "/root/build\r/sysy.tab.cpp"
    break;

  case 92:
#line 544 "/root/src/sysy.y"
             {
    (yyval.ast_val) = new RelExpAST(unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2323 "/root/build\r/sysy.tab.cpp"
    break;

  case 93:
#line 547 "/root/src/sysy.y"
                        {
    (yyval.ast_val) = new RelExpAST("<", unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2331 "/root/build\r/sysy.tab.cpp"
    break;

  case 94:
#line 550 "/root/src/sysy.y"
                        {
    (yyval.ast_val) = new RelExpAST(">", unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2339 "/root/build\r/sysy.tab.cpp"
    break;

  case 95:
#line 553 "/root/src/sysy.y"
                       {
    (yyval.ast_val) = new RelExpAST("<=", unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2347 "/root/build\r/sysy.tab.cpp"
    break;

  case 96:
#line 556 "/root/src/sysy.y"
                       {
    (yyval.ast_val) = new RelExpAST(">=", unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2355 "/root/build\r/sysy.tab.cpp"
    break;

  case 97:
#line 562 "/root/src/sysy.y"
           {
    (yyval.ast_val) = new EqExpAST(unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2363 "/root/build\r/sysy.tab.cpp"
    break;

  case 98:
#line 565 "/root/src/sysy.y"
                    {
    (yyval.ast_val) = new EqExpAST("==", unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2371 "/root/build\r/sysy.tab.cpp"
    break;

  case 99:
#line 568 "/root/src/sysy.y"
                    {
    (yyval.ast_val) = new EqExpAST("!=", unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2379 "/root/build\r/sysy.tab.cpp"
    break;

  case 100:
#line 574 "/root/src/sysy.y"
          {
    (yyval.ast_val) = new BitExpAST(unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2387 "/root/build\r/sysy.tab.cpp"
    break;

  case 101:
#line 577 "/root/src/sysy.y"
                        {
    (yyval.ast_val) = new BitExpAST("&", unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2395 "/root/build\r/sysy.tab.cpp"
    break;

  case 102:
#line 583 "/root/src/sysy.y"
              {
    (yyval.ast_val) = new BitExpAST(unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2403 "/root/build\r/sysy.tab.cpp"
    break;

  case 103:
#line 586 "/root/src/sysy.y"
                            {
    (yyval.ast_val) = new BitExpAST("^", unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2411 "/root/build\r/sysy.tab.cpp"
    break;

  case 104:
#line 592 "/root/src/sysy.y"
              {
    (yyval.ast_val) = new BitExpAST(unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2419 "/root/build\r/sysy.tab.cpp"
    break;

  case 105:
#line 595 "/root/src/sysy.y"
                           {
    (yyval.ast_val) = new BitExpAST("|", unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2427 "/root/build\r/sysy.tab.cpp"
    break;

  case 106:
#line 601 "/root/src/sysy.y"
             {
    (yyval.ast_val) = new LAndExpAST(unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2435 "/root/build\r/sysy.tab.cpp"
    break;

  case 107:
#line 604 "/root/src/sysy.y"
                          {
    (yyval.ast_val) = new LAndExpAST("&&", unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2443 "/root/build\r/sysy.tab.cpp"
    break;

  case 108:
#line 610 "/root/src/sysy.y"
            {
    (yyval.ast_val) = new LOrExpAST(unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2451 "/root/build\r/sysy.tab.cpp"
    break;

  case 109:
#line 613 "/root/src/sysy.y"
                       {
    (yyval.ast_val) = new LOrExpAST("||", unique_ptr<BaseAST>((yyvsp[-2].ast_val)), unique_ptr<BaseAST>((yyvsp[0].ast_val)));
  }
#line 2459 "/root/build\r/sysy.tab.cpp"
    break;

  case 110:
#line 619 "/root/src/sysy.y"
        {
    (yyval.ast_val) = (yyvsp[0].ast_val);
  }
#line 2467 "/root/build\r/sysy.tab.cpp"
    break;


#line 2471 "/root/build\r/sysy.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (ast, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (ast, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, ast);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, ast);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (ast, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, ast);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, ast);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 623 "/root/src/sysy.y"


void yyerror(unique_ptr<BaseAST> &ast, const char *s) {
  cerr << "error: " << s << endl;
}
