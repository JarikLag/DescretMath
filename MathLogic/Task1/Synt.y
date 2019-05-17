{
module Synt where
import Lex
}

%name parse
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

%%

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

data BinaryOp = Impl | Or | And

instance Show BinaryOp where
  show Impl = "->"
  show Or = "|"
  show And = "&"

data Expr = Bin BinaryOp Expr Expr | Not Expr | Var String

instance Show Expr where
  show (Bin op a b) = "(" ++ show op ++ "," ++ show a ++ "," ++ show b ++ ")"
  show (Not a) = "(!" ++ show a ++ ")"
  show (Var a) = a
}