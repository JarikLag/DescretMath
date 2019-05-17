{
module Synt where
import Lex
}

%name parseFirstLine Terminal
%name parse Expr
%tokentype {Token}
%error {parseError}

%token
    var     {TVar $$}
    leftBr  {TLeftBr}
    rightBr {TRightBr}
    and     {TAnd}
    or      {TOr}
    impl    {TImpl}
    not     {TNot}
    comma   {TComma}
    turn    {TTurnstile}

%%

Terminal
        : Context turn Expr {$3 : $1}

Context
        : {- empty -}        { [] }
        | Expr               { [$1] }
        | Context comma Expr {$3 : $1}

Expr                        
    : Disj                  {$1}
    | Disj impl Expr        {Bin Impl $1 $3}
    
Disj
    : Conj                  {$1}
    | Disj or Conj          {Bin Or $1 $3}

Conj
    : Neg                   {$1}
    | Conj and Neg          {Bin And $1 $3}
    
Neg
    : not Neg               {Not $2}
    | leftBr Expr rightBr   {$2}
    | var                   {Var $1}
    
{
parseError :: [Token] -> a
parseError _ = error "Parse error"

data BinaryOp = Impl | Or | And deriving (Eq, Ord)

instance Show BinaryOp where
  show Impl = "->"
  show Or = "|"
  show And = "&"

data Expr = Bin BinaryOp Expr Expr | Not Expr | Var String deriving (Eq, Ord)

instance Show Expr where
  show (Bin op a b) = "(" ++ show a ++ " " ++ show op ++ " " ++ show b ++ ")"
  show (Not a) = "!" ++ show a
  show (Var a) = a
}