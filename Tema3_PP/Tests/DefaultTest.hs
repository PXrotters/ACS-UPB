module Tests.DefaultTest (defaultTests) where

import Tests.Test
import Lambda
import Default

evaluate :: Lambda -> Lambda
evaluate = last . simplify normalStep

boolTest :: TestCase Bool
boolTest = do
    section "===== 4.1. Bool tests ====="
    assert_eq "And True True" 0 (evaluate (App (App bAnd bTrue) bTrue)) bTrue
    assert_eq "And True False" 1 (evaluate (App (App bAnd bTrue) bFalse)) bFalse
    assert_eq "Or True False" 0 (evaluate (App (App bOr bTrue) bFalse)) bTrue
    assert_eq "Or False False" 1 (evaluate (App (App bOr bFalse) bFalse)) bFalse
    assert_eq "Not True" 0 (evaluate (App bNot bTrue)) bFalse
    assert_eq "Not False" 1 (evaluate (App bNot bFalse)) bTrue
    assert_eq "Xor True True" 1 (evaluate (App (App bXor bTrue) bTrue)) bFalse
    assert_eq "Xor True False" 1 (evaluate (App (App bXor bTrue) bFalse)) bTrue
    assert_eq "Xor False False" 1 (evaluate (App (App bXor bFalse) bFalse)) bFalse

pairTest :: TestCase Bool
pairTest = do
    section "===== 4.2. Pair tests ====="
    assert_eq "First (Pair x y)" 2 (evaluate (App first (App (App pair vx) vy))) vx
    assert_eq "Second (Pair x y)" 2 (evaluate (App second (App (App pair vx) vy))) vy

naturalTest :: TestCase Bool
naturalTest = do
    section "===== 4.3. Natural tests ====="
    assert_eq "Succ 0" 0 (evaluate (App nSucc n0)) n1
    assert_eq "Succ Succ 0" 1 (evaluate (App nSucc (App nSucc n0))) n2
    assert_eq "Pred 0" 0 (evaluate (App nPred n0)) n0
    assert_eq "Pred 1" 0 (evaluate (App nPred n1)) n0
    assert_eq "Pred 2" 1 (evaluate (App nPred n2)) n1
    assert_eq "Add 1 1" 0 (evaluate (App (App nAdd n1) n1)) n2
    assert_eq "Add 1 2 = Succ 2" 1 (evaluate (App (App nAdd n1) n2)) (evaluate (App nSucc n2))
    assert_eq "Sub 2 1" 0 (evaluate (App (App nSub n2) n1)) n1
    assert_eq "Sub 2 2" 0 (evaluate (App (App nSub n2) n2)) n0
    assert_eq "Sub 1 2" 1 (evaluate (App (App nSub n2) n2)) n0
    assert_eq "Mult 1 2" 0 (evaluate (App (App nMult n1) n2)) n2
    assert_eq "Mult 2 2" 1 (evaluate (App (App nMult n2) n2)) (evaluate (App (App nAdd n2) n2))


defaultTests :: IO (Int, Int)
defaultTests = runTests
    [ boolTest
    , pairTest
    , naturalTest
    ]
