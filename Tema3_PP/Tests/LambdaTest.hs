module Tests.LambdaTest (lambdaTests) where

import Data.List ((\\))

import Tests.Test
import Lambda
import Default

eqTest :: TestCase Bool
eqTest = do
    section "===== Eq tests (sanity check) ====="
    assert_eq "x == x" 0 vx vx
    assert_eq "x == y" 0 vx vy
    assert_eq "λx.x == λx.x" 0 (Abs "x" vx) (Abs "x" vx)
    assert_eq "λx.x == λy.y" 0 (Abs "x" vx) (Abs "y" vy)
    assert_neq "λx.x != λx.y" 0 (Abs "x" vx) (Abs "x" vy)
    assert_eq "(x y) == (n m)" 0 (App vx vy) (App vn vm)
    assert_neq "λx.λy.(x y) != λx.λz.(x y)" 0 e1 e2
      where
        e1 = Abs "x" (Abs "y" (App vx vy))
        e2 = Abs "x" (Abs "z" (App vx vy))

varsTest :: TestCase Bool
varsTest = do
    section "===== 1.1. vars tests ====="
    assert_eq "vars x" 0 (vars vx) ["x"]
    assert_eq "vars (λx.x)" 1 (vars (Abs "x" vx)) ["x"]
    assert_eq "vars (λx.y)" 1 (vars (Abs "x" vy)) ["x", "y"]
    assert_eq "vars (x y)" 1 (vars (App vx vy)) ["x", "y"]
    assert_eq "vars (λx.(x x))" 1 (vars (Abs "x" (App vx vy)) ) ["x", "y"]
    assert_eq "vars (λx.(x y))" 1 (vars (Abs "x" (App vx vy)) ) ["x", "y"]

freeVarsTest :: TestCase Bool
freeVarsTest = do
    section "===== 1.2. freeVars tests ====="
    assert_count_eq "freeVars x" 0 (freeVars vx) ["x"]
    assert_count_eq "freeVars (λx.x)" 1 (freeVars (Abs "x" vx)) []
    assert_count_eq "freeVars (λx.y)" 1 (freeVars (Abs "x" vy)) ["y"]
    assert_count_eq "freeVars (x y)" 1 (freeVars (App vx vy)) ["x", "y"]
    assert_count_eq ("freeVars " ++ show e) 1 (freeVars e) ["x", "z"]
    assert_count_eq ("freeVars " ++ show y) 1 (freeVars y) []
      where 
        e = App (Abs "x" (Var "z")) (App (Var "x") (Var "z"))

newVarTest :: TestCase Bool
newVarTest = do
    section "===== 1.3. newVar tests ====="
    assert_eq "newVar 'a'" 1 (newVar ["a"]) "b"
    assert_eq "newVar 'a'..'e'" 1 (newVar ["a", "b", "c", "d", "e"]) "f"
    assert_eq "newVar 2 chars" 2 (newVar alphabet) "aa"
    assert_eq "newVar 3 chars" 2 (newVar alphabet_2) "aaa"
    assert_eq "newVar find missing" 2 (newVar $ alphabet_2 \\ ["cd"]) "cd"
    assert_eq "newVar multiple missing" 2 (newVar $ alphabet_2 \\ ["cd", "ab"]) "ab"
      where
        alphabet = map (:[]) ['a'..'z']
        alphabet_2 = [a ++ b | a <- alphabet, b <- "":alphabet]

isNormalFormTest :: TestCase Bool
isNormalFormTest = do
    section "===== 1.4. isNormalForm tests ====="
    assert "x" 0 (isNormalForm vx)
    assert "λx.x" 0 (isNormalForm $ Abs "x" vx)
    assert "(x y)" 0 (isNormalForm $ App vx vy)
    assert "λx.(x y)" 0 (isNormalForm $ Abs "x" (App vx vy))
    assert "(λx.(x x) x)" 1 (not $ isNormalForm $ App m vx)
    assert "(λx.(x x) λx.(x x))" 1 (not $ isNormalForm $ App m m)
    assert (show y) 2 (not $ isNormalForm y)
    assert "λx.(λx.(x x) x)" 1 (not $ isNormalForm $ Abs "x" $ App m vx)

reduceTest :: TestCase Bool
reduceTest = do
    section "===== 1.5. reduce tests ====="
    assert_eq "reduce variable" 2 (reduce "x" vx m) m
    assert_eq "reduce free variable" 2 (reduce "x" vy m) vy
    assert_eq "reduce application" 2 (reduce "x" (App vx vx) m) (App m m)
    assert_eq "reduce abstraction" 2 (reduce "x" (Abs "y" vx) m) (Abs "y" m)
    assert_eq "reduce abstraction same name" 2 (reduce "x" (Abs "x" vx) m) (Abs "x" vx)
    assert_eq "reduce variable capture" 5 (reduce "x" e1 e2) e
    assert_eq "reduce complex" 5 (reduce "y" e1 e2) (Abs "x" (App vy vx))
      where
        e = Abs "a" (App (Abs "x" vy) (Var "a"))
        e1 = Abs "y" (App vx vy)
        e2 = Abs "x" vy

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

normalStepTest :: TestCase Bool
normalStepTest = do
    section "===== 1.6. normalStep tests ====="
    assert_eq "normalStep variable" 1 (normalStep vx) vx
    assert_eq "normalStep reduction" 1 (normalStep $ App m vx) (App vx vx)
    assert_eq "normalStep complex" 2 (normalStep $ App (Abs "x" vy) (App m m)) vy
    assert_eq "normalStep 1 step" 2 (normalStep expr1) (normalAns1 !! 1)
    assert_eq "normalStep 2 steps" 2 (normalStep $ normalStep expr1) (normalAns1 !! 2)
    assert_eq "normalStep y" 2 (normalStep y) y1
      where
        y1 = let (Abs "f" expr) = y in Abs "f" (App (Var "f") expr)

applicativeStepTest :: TestCase Bool
applicativeStepTest = do
    section "===== 1.7. applicativeStep tests ====="
    assert_eq "applicativeStep variable" 1 (applicativeStep vx) vx
    assert_eq "applicativeStep reduction" 1 (applicativeStep $ App m vx) (App vx vx)
    assert_eq "applicativeStep complex" 2 (applicativeStep expr) expr
    assert_eq "applicativeStep 1 step" 2 (applicativeStep expr1) (applicativeAns1 !! 1)
    assert_eq "applicativeStep 2 steps" 2 (applicativeStep $ applicativeStep expr1) (applicativeAns1 !! 2)
    assert_eq "applicativeStep 3 steps" 2 (applicativeStep $ applicativeStep $ applicativeStep expr1) (applicativeAns1 !! 3)
  where
    expr = App (Abs "x" vy) (App m m)

simplifyTest :: TestCase Bool
simplifyTest = do
    section "===== 1.8. simplify tests ====="
    assert_eq "simplify normalForm" 1 (simplify id c) [c]
    assert_eq "simplify normal order" 2 (simplify normalStep expr1) normalAns1
    assert_eq "simplify applicative order" 2 (simplify applicativeStep expr1) applicativeAns1

lambdaTests :: IO (Int, Int)
lambdaTests = runTests 
    [ eqTest
    , varsTest
    , freeVarsTest
    , newVarTest
    , isNormalFormTest
    , reduceTest
    , normalStepTest
    , applicativeStepTest
    , simplifyTest
    ]
