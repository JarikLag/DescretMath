module Main where

import qualified Data.Map.Strict as Map
import Data.Maybe
import Lex
import Synt

type MPMap = Map.Map Expr [Expr]
type ProofMap = Map.Map Expr Expr

{-0 for axioms 1-9, 1 for axiom 10, 2 for non-axiom-}
checkAxioms :: Expr -> Integer
checkAxioms expr = case expr of 
                    (Bin Impl a (Bin Impl b c))
                        | a == c -> 0
                    (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl c (Bin Impl d e)) (Bin Impl f g)))
                        | a == c && a == f && b == d && e == g -> 0
                    (Bin Impl a (Bin Impl b (Bin And c d)))
                        | a == c && b == d -> 0
                    (Bin Impl (Bin And a b) c)
                        | a == c -> 0
                        | b == c -> 0
                    (Bin Impl a (Bin Or b c))
                        | a == b -> 0
                        | a == c -> 0
                    (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl c d) (Bin Impl (Bin Or e f) g)))
                        | a == e && c == f && b == d && b == g -> 0
                    (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl c (Not d)) (Not e)))
                        | a == c && a == e && b == d -> 0
                    (Bin Impl (Not(Not a)) b)
                        | a == b -> 1
                    (a) -> 2
        
modifyAxiomsAndHypothesis :: Expr -> IO()
modifyAxiomsAndHypothesis a = do
                                putStrLn $ show $ a
                                putStrLn $ show (Bin Impl a (Bin Impl (Not a) a))
                                putStrLn $ show (Bin Impl (Not a) a)
                                putStrLn $ show (Bin Impl (Not a) (Bin Impl (Not a) (Not a)))
                                putStrLn $ show (Bin Impl (Bin Impl (Not a) (Bin Impl (Not a) (Not a))) (Bin Impl (Bin Impl (Not a) (Bin Impl (Bin Impl (Not a) (Not a)) (Not a))) (Bin Impl (Not a) (Not a))))
                                putStrLn $ show (Bin Impl (Bin Impl (Not a) (Bin Impl (Bin Impl (Not a) (Not a)) (Not a))) (Bin Impl (Not a) (Not a)))
                                putStrLn $ show (Bin Impl (Not a) (Bin Impl (Bin Impl (Not a) (Not a)) (Not a)))
                                putStrLn $ show (Bin Impl (Not a) (Not a))
                                putStrLn $ show (Bin Impl (Bin Impl (Not a) a) (Bin Impl (Bin Impl (Not a) (Not a)) (Not (Not a))))
                                putStrLn $ show (Bin Impl (Bin Impl (Not a) (Not a)) (Not (Not a)))
                                putStrLn $ show (Not (Not a))

modify10thAxiom :: Expr -> IO()
modify10thAxiom (Bin Impl (Not(Not a)) b) = do
                                                putStrLn $ show (Bin Impl a (Bin Impl (Not (Not a)) a))
                                                putStrLn $ show (Bin Impl (Bin Impl a (Bin Impl (Not (Not a)) a)) (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl a (Bin Impl (Not (Not a)) a))))
                                                putStrLn $ show (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl a (Bin Impl (Not (Not a)) a)))
                                                putStrLn $ show (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl a (Not (Bin Impl (Not (Not a)) a))))
                                                putStrLn $ show (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not (Bin Impl (Not (Not a)) a))))
                                                putStrLn $ show (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not (Bin Impl (Not (Not a)) a))) (Not (Bin Impl (Not (Not a)) a))))
                                                putStrLn $ show (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not (Bin Impl (Not (Not a)) a)))) (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not (Bin Impl (Not (Not a)) a))) (Not (Bin Impl (Not (Not a)) a)))) (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not (Bin Impl (Not (Not a)) a)))))
                                                putStrLn $ show (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not (Bin Impl (Not (Not a)) a))) (Not (Bin Impl (Not (Not a)) a)))) (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not (Bin Impl (Not (Not a)) a))))
                                                putStrLn $ show (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not (Bin Impl (Not (Not a)) a)))
                                                putStrLn $ show (Bin Impl (Bin Impl a (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Not (Bin Impl (Not (Not a)) a))) (Not a)))
                                                putStrLn $ show (Bin Impl (Bin Impl (Bin Impl a (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Not (Bin Impl (Not (Not a)) a))) (Not a))) (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Not (Bin Impl (Not (Not a)) a))) (Not a)))))
                                                putStrLn $ show (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Not (Bin Impl (Not (Not a)) a))) (Not a))))
                                                putStrLn $ show (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl a (Bin Impl (Not (Not a)) a))) (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Not (Bin Impl (Not (Not a)) a))) (Not a)))) (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Not (Bin Impl (Not (Not a)) a))) (Not a)))))
                                                putStrLn $ show (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Not (Bin Impl (Not (Not a)) a))) (Not a)))) (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Not (Bin Impl (Not (Not a)) a))) (Not a))))
                                                putStrLn $ show (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Not (Bin Impl (Not (Not a)) a))) (Not a)))
                                                putStrLn $ show (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl a (Not (Bin Impl (Not (Not a)) a)))) (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Not (Bin Impl (Not (Not a)) a))) (Not a))) (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not a))))
                                                putStrLn $ show (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl a (Not (Bin Impl (Not (Not a)) a))) (Not a))) (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not a)))
                                                putStrLn $ show (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not a))
                                                putStrLn $ show (Bin Impl (Not a) (Bin Impl (Not (Not a)) a))
                                                putStrLn $ show (Bin Impl (Bin Impl (Not a) (Bin Impl (Not (Not a)) a)) (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Not a) (Bin Impl (Not (Not a)) a))))
                                                putStrLn $ show (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Not a) (Bin Impl (Not (Not a)) a)))
                                                putStrLn $ show (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not a)) (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Not a) (Bin Impl (Not (Not a)) a))) (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Not (Not a)) a))))
                                                putStrLn $ show (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Not a) (Bin Impl (Not (Not a)) a))) (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Not (Not a)) a)))
                                                putStrLn $ show (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Not (Not a)) a))
                                                putStrLn $ show (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Bin Impl (Not (Not a)) a)) (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not (Bin Impl (Not (Not a)) a))) (Not (Not (Bin Impl (Not (Not a)) a)))))
                                                putStrLn $ show (Bin Impl (Bin Impl (Not (Bin Impl (Not (Not a)) a)) (Not (Bin Impl (Not (Not a)) a))) (Not (Not (Bin Impl (Not (Not a)) a))))
                                                putStrLn $ show (Not (Not (Bin Impl (Not (Not a)) a)))


modifyModusPonens :: Expr -> Expr -> IO()
modifyModusPonens a b = do
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not b)))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl a (Not b)))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl a (Not b))) (Bin Impl (Not b) (Bin Impl (Not b) (Bin Impl a (Not b)))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Not b) (Bin Impl a (Not b))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl a (Not b))) (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Bin Impl (Not b) (Bin Impl a (Not b))) (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Not b) (Bin Impl a (Not b))) (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl (Not b) (Bin Impl a (Not b))) (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Not b) (Bin Impl a (Not b)))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Not b) (Bin Impl a (Not b))) (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Not b) (Bin Impl a (Not b))) (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Bin Impl a b) (Not b)) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Bin Impl (Bin Impl a b) (Not b)) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not b)) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b)))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not b)) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not b))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not b)) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b)))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b)))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not b)) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b)))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b))))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not b) (Bin Impl a (Not b)))) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b)))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b))))
                            putStrLn $ show (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a)))
                            putStrLn $ show (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a)))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a))))
                            putStrLn $ show (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl a (Not b))) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a))) (Bin Impl (Bin Impl a b) (Not a))))
                            putStrLn $ show (Bin Impl (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl a (Not b))) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a))) (Bin Impl (Bin Impl a b) (Not a)))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl a (Not b))) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a))) (Bin Impl (Bin Impl a b) (Not a))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl a (Not b))) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a))) (Bin Impl (Bin Impl a b) (Not a)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl a (Not b)))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl a (Not b))) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a))) (Bin Impl (Bin Impl a b) (Not a))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a))) (Bin Impl (Bin Impl a b) (Not a))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl a (Not b))) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a))) (Bin Impl (Bin Impl a b) (Not a))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a))) (Bin Impl (Bin Impl a b) (Not a)))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a))) (Bin Impl (Bin Impl a b) (Not a))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a)))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a))) (Bin Impl (Bin Impl a b) (Not a)))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not a)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Bin Impl a (Not b)) (Not a))) (Bin Impl (Bin Impl a b) (Not a)))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not a))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not a)))
                            putStrLn $ show (Not (Not a))
                            putStrLn $ show (Bin Impl (Not (Not a)) (Bin Impl (Not b) (Not (Not a))))
                            putStrLn $ show (Bin Impl (Not b) (Not (Not a)))
                            putStrLn $ show (Bin Impl (Not (Not a)) (Bin Impl (Bin Impl a b) (Not (Not a))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not (Not a)) (Bin Impl (Bin Impl a b) (Not (Not a)))) (Bin Impl (Not b) (Bin Impl (Not (Not a)) (Bin Impl (Bin Impl a b) (Not (Not a))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Not (Not a)) (Bin Impl (Bin Impl a b) (Not (Not a)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Not (Not a))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Not (Not a)) (Bin Impl (Bin Impl a b) (Not (Not a))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not (Not a))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Not (Not a)) (Bin Impl (Bin Impl a b) (Not (Not a))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not (Not a)))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not (Not a))))
                            putStrLn $ show (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Not b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Bin Impl a b) (Not a)) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Bin Impl (Bin Impl a b) (Not a)) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not a)) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not a)) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not a))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not a)) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not a)) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not a) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not a))) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not a))) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not a))) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b)))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not a))) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not (Not a)))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not a))) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b)))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b)))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not a))) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b)))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b))))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Bin Impl (Not (Not a)) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b)))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b))))
                            putStrLn $ show (Not (Not (Bin Impl a b)))
                            putStrLn $ show (Bin Impl (Not (Not (Bin Impl a b))) (Bin Impl (Not b) (Not (Not (Bin Impl a b)))))
                            putStrLn $ show (Bin Impl (Not b) (Not (Not (Bin Impl a b))))
                            putStrLn $ show (Bin Impl (Not (Not (Bin Impl a b))) (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not (Not (Bin Impl a b))) (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b))))) (Bin Impl (Not b) (Bin Impl (Not (Not (Bin Impl a b))) (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Not (Not (Bin Impl a b))) (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Not (Not (Bin Impl a b)))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Not (Not (Bin Impl a b))) (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Not (Not (Bin Impl a b))) (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))))) (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Bin Impl a b) (Not (Bin Impl a b))) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))) (Not (Bin Impl a b))))
                            putStrLn $ show (Bin Impl (Bin Impl (Bin Impl (Bin Impl a b) (Not (Bin Impl a b))) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))) (Not (Bin Impl a b)))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Bin Impl a b))) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))) (Not (Bin Impl a b))))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Bin Impl a b))) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))) (Not (Bin Impl a b)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not (Bin Impl a b)))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Bin Impl a b))) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))) (Not (Bin Impl a b))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))) (Not (Bin Impl a b))))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Bin Impl a b))) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))) (Not (Bin Impl a b))))) (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))) (Not (Bin Impl a b)))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))) (Not (Bin Impl a b))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b))))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))) (Not (Bin Impl a b)))) (Bin Impl (Not b) (Not (Bin Impl a b)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Bin Impl (Bin Impl a b) (Not (Not (Bin Impl a b)))) (Not (Bin Impl a b)))) (Bin Impl (Not b) (Not (Bin Impl a b))))
                            putStrLn $ show (Bin Impl (Not b) (Not (Bin Impl a b)))
                            putStrLn $ show (Bin Impl (Not (Bin Impl a b)) (Bin Impl (Not (Not (Bin Impl a b))) (Not a)))
                            putStrLn $ show (Bin Impl (Bin Impl (Not (Bin Impl a b)) (Bin Impl (Not (Not (Bin Impl a b))) (Not a))) (Bin Impl (Not b) (Bin Impl (Not (Bin Impl a b)) (Bin Impl (Not (Not (Bin Impl a b))) (Not a)))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Not (Bin Impl a b)) (Bin Impl (Not (Not (Bin Impl a b))) (Not a))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Not (Bin Impl a b))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Not (Bin Impl a b)) (Bin Impl (Not (Not (Bin Impl a b))) (Not a)))) (Bin Impl (Not b) (Bin Impl (Not (Not (Bin Impl a b))) (Not a)))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Not (Bin Impl a b)) (Bin Impl (Not (Not (Bin Impl a b))) (Not a)))) (Bin Impl (Not b) (Bin Impl (Not (Not (Bin Impl a b))) (Not a))))
                            putStrLn $ show (Bin Impl (Not b) (Bin Impl (Not (Not (Bin Impl a b))) (Not a)))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Not (Not (Bin Impl a b)))) (Bin Impl (Bin Impl (Not b) (Bin Impl (Not (Not (Bin Impl a b))) (Not a))) (Bin Impl (Not b) (Not a))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Bin Impl (Not (Not (Bin Impl a b))) (Not a))) (Bin Impl (Not b) (Not a)))
                            putStrLn $ show (Bin Impl (Not b) (Not a))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Not a)) (Bin Impl (Bin Impl (Not b) (Not (Not a))) (Not (Not b))))
                            putStrLn $ show (Bin Impl (Bin Impl (Not b) (Not (Not a))) (Not (Not b)))
                            putStrLn $ show (Not (Not b))

addModusPonens :: Expr -> MPMap -> MPMap
addModusPonens expr mp = case expr of 
                            (Bin Impl a b) -> case Map.lookup b mp of
                                                Nothing -> Map.insert b [a] mp
                                                Just list -> Map.insert b (list ++ [a]) mp
                            (a) -> mp

addProof :: Expr -> ProofMap -> ProofMap
addProof expr proof = case Map.lookup expr proof of
                        Nothing -> Map.insert expr expr proof
                        Just a -> proof

checkProof :: [Expr] -> ProofMap -> (Bool, Expr)
checkProof [] _ = (False, (Var "1"))
checkProof (expr:exprs) proof = case Map.lookup expr proof of
                                Nothing -> checkProof exprs proof
                                Just e -> (True, e)

checkModusPonens :: Expr -> MPMap -> ProofMap -> (Bool, Expr)
checkModusPonens expr mp proof = do
                                    let list = Map.lookup expr mp
                                    if isJust $ list
                                        then checkProof (fromJust list) proof
                                    else (False, (Var "1"))

readAll :: MPMap -> ProofMap -> Expr -> String -> IO()
readAll mp proof lastStatement str = do
                                        let expression = parse $ alexScanTokens str
                                        let isAxiom = checkAxioms $ expression
                                        let pair = checkModusPonens expression mp proof
                                        if (fst pair) == True
                                            then modifyModusPonens (snd pair) expression
                                        else if isAxiom == 0 || isAxiom == 2
                                            then modifyAxiomsAndHypothesis expression
                                        else modify10thAxiom expression
                                        if expression == lastStatement
                                            then return ()
                                        else do
                                                input <- getLine
                                                readAll (addModusPonens expression mp) (addProof expression proof) lastStatement input
                        
printList :: [Expr] -> IO()
printList [] = return ()
printList (expr:exprs) = do
                            putStr $ show expr
                            if (length exprs) > 0
                                then putStr $ ", "
                            else putStr $ " "
                            printList exprs
                            
main :: IO()
main = do
        input <- getLine
        let fst = parseFirstLine $ alexScanTokens input
        if (length fst) > 1
            then printList (reverse (tail fst))
        else printList []
        putStrLn $ "|- " ++ show (Not (Not (head fst)))
        input <- getLine
        readAll Map.empty Map.empty (head fst) input