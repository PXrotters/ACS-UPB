module Tests.BindingTest (bindingTests) where

import Tests.Test
import Lambda
import Parser
import Binding
import Default

simplifyCtxTest :: TestCase Bool
simplifyCtxTest = do
    section "===== 3.1. simplifyCtx ====="
    assert_eq "simplifyCtx normalForm" 1 (simplifyCtx [] normalStep vx) (Right [vx])
    assert_eq "simplifyCtx normal order" 2 (simplifyCtx [] normalStep expr1) (Right normalAns1)
    assert_eq "simplifyCtx applicative order" 2 (simplifyCtx [] applicativeStep expr1) (Right applicativeAns1)
    assert_err "simplifyCtx error" 2 (simplifyCtx [("X", vx)] id (Macro "Y"))
    assert_eq "simplifyCtx simple" 2 (simplifyCtx [("X", vx)] id (Macro "X")) (Right [vx])
    assert_eq "simplifyCtx complex" 6 (simplifyCtx defaultContext normalStep complexRxpr) (Right complexAns)
      where
        expr1 = App (App k vx) (App ki vy)
        normalAns1 = [ expr1
                     , App (Abs "y" vx) (App ki vy)
                     , vx
                     ]
        applicativeAns1 = [ expr1
                          , App (Abs "y" vx) (App ki vy) 
                          , App (Abs "y" vx) (Abs "z" vz)
                          , vx
                          ]
        complexRxpr = App (Macro "C") (App (Macro "K") (Macro "I"))
        complexAns = [ App c (App k i)
                      , Abs "y" $ Abs "z" $ App (App (App k i) vz) vy
                      , Abs "y" $ Abs "z" $ App (App ki vz) vy
                      , Abs "y" $ Abs "z" $ App i vy
                      , k
                      ]

parseMacroTest :: TestCase Bool
parseMacroTest = do
    section "===== 3.2. parseMacro ====="
    assert_eq "parse simple macro" 0 (parseLambda "X") (Macro "X")
    assert_eq "parse multicharacter macro" 1 (parseLambda "CHURCH") (Macro "CHURCH")
    assert_eq "parse macro with digits" 1 (parseLambda "420B3") (Macro "420B3")
    assert_eq "parse application" 1 (parseLambda "((AND TRUE) FALSE)") expr1
    assert_eq "parse abstraction" 1 (parseLambda "\\x.TRUE") (Abs "x" (Macro "TRUE"))
    assert_eq "parse complex" 1 (parseLambda "(\\x.(AND x) FALSE)") expr2
      where
        expr1 = (App (App (Macro "AND") (Macro "TRUE")) (Macro "FALSE"))
        expr2 = (App (Abs "x" (App (Macro "AND") (Var "x"))) (Macro "FALSE"))

parseLineTest :: TestCase Bool
parseLineTest = do
    section "===== 3.3. parseLine ====="
    assert_eq "parse simple eval" 1 (parseLine "x") (Right $ Eval vx)
    assert_eq "parse eval" 1 (parseLine "\\x.(x x)") (Right $ Eval m)
    assert_eq "parse simple binding" 1 (parseLine "X=x") (Right $ Binding "X" vx)
    assert_eq "parse binding" 1 (parseLine "TRUE=\\x.\\y.x") (Right $ Binding "TRUE" k)
    assert_err "parse error" 1 (parseLine "x x")

bindingTests :: IO (Int, Int)
bindingTests = runTests
    [ simplifyCtxTest
    , parseMacroTest
    , parseLineTest
    ]
