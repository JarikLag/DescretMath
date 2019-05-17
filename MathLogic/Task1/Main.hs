module Main where

import Lex
import Synt

main :: IO()
main = do
        input <- getLine
        let result = parse $ alexScanTokens input
        putStrLn $ show result