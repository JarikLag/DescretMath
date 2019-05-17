{
module Lex where
}

%wrapper "basic"

$digit = 0-9
$alpha = [A-Z]

tokens:-

    $white+                       ;
    \(                            {\s -> TLeftBr}
    \)                            {\s -> TRightBr}
    &                             {\s -> TAnd}
    \|                            {\s -> TOr}
    "->"                          {\s -> TImpl}
    !                             {\s -> TNot}
    $alpha [$alpha $digit \']*    {\s -> TVar s}

{
data Token = TLeftBr | TRightBr | TAnd | TOr | TImpl | TNot | TVar String deriving (Eq, Show)
}