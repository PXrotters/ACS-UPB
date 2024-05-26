module Tests.ParserTest (parserTests) where

import Tests.Test
import Lambda
import Parser
import Default

parseTest :: TestCase Bool
parseTest = do
    section "===== 2.1. Parser ====="
    assert_eq "parse variable" 2 (parseLambda "x") vx
    assert_eq "parse multicharacter variable" 2 (parseLambda "alonzo") (Var "alonzo")
    assert_eq "parse application" 2 (parseLambda "(x y)") (App vx vy)
    assert_eq "parse applications 1" 2 (parseLambda "((x y) z)") (App (App vx vy) vz)
    assert_eq "parse applications 2" 2 (parseLambda "(x (y z))") (App vx (App vy vz))
    assert_eq "parse abstraction" 2 (parseLambda "\\x.y") (Abs "x" vy)
    assert_eq "parse simple" 2 (parseLambda "(\\x.y \\x.x)") (App (Abs "x" vy) i)
    assert_eq "parse 'complex'" 2 (parseLambda "(\\x.\\y.x \\x.\\y.y)") (App k ki)
    assert_eq "parse M-combinator" 4 (parseLambda "\\x.(x x)") m
    assert_eq "parse I-combinator" 4 (parseLambda "\\x.x") i
    assert_eq "parse K-combinator" 4 (parseLambda "\\x.\\y.x") k
    assert_eq "parse KI-combinator" 4 (parseLambda "\\x.\\y.y") ki
    assert_eq "parse C-combinator" 4 (parseLambda "\\x.\\y.\\z.((x z) y)") c
    assert_eq "parse Y-combinator" 4 (parseLambda "\\f.(\\x.(f (x x)) \\x.(f (x x)))") y

parserTests :: IO (Int, Int)
parserTests = runTests [parseTest]
