module Tests.Test where

import Control.Exception (catch, ErrorCall(..))
import Data.List (sort)

data TestCase a = Test {
    info :: String,
    points :: Int,
    max_points :: Int,
    state :: a
}

instance Monad TestCase where
    return x = Test "" 0 0 x
    x >>= f = Test ninfo npoints nmax_points nstate
      where
        y = f (state x)
        ninfo = info x ++ newline ++ info y
        newline = if info y == "" then "" else "\n"
        npoints = points x + points y
        nmax_points = max_points x + max_points y
        nstate = state y

instance Applicative TestCase where
    pure = return
    f <*> x = do
        g <- f
        y <- x
        return (g y)

instance Functor TestCase where
    fmap f x = do
        y <- x
        return (f y)

red :: String -> String
-- red msg = msg -- uncomment this line to disable color
red msg = "\x1b[31m" ++ msg ++ "\x1b[0m"

green :: String -> String
-- green msg = msg -- uncomment this line to disable color
green msg = "\x1b[32m" ++ msg ++ "\x1b[0m"

assert :: String -> Int -> Bool -> TestCase Bool
assert msg points cond = Test info (if cond then points else 0) points cond
  where
    info = (if cond then green "[PASSED] " else red "[FAILED] ") ++ msg

assert_eq :: (Eq a, Show a) => String -> Int -> a -> a -> TestCase Bool
assert_eq msg points actual expected = assert aug_msg points (expected == actual)
  where
    aug_msg = msg ++ error_msg
    error_msg = if expected == actual 
                then ""
                else "\nExpected: " ++ show expected ++ 
                     "\n  Actual: " ++ show actual

assert_count_eq :: (Ord a, Show a) => String -> Int -> [a] -> [a] -> TestCase Bool
assert_count_eq msg points actual expected = assert_eq msg points (sort actual) (sort expected)

assert_neq :: (Eq a, Show a) => String -> Int -> a -> a -> TestCase Bool
assert_neq msg points actual expected = assert msg points (expected /= actual)

assert_err :: String -> Int -> Either String a -> TestCase Bool
assert_err msg points (Left _) = assert msg points True
assert_err msg points (Right _) = assert msg points False

section :: String -> TestCase ()
section msg = Test msg 0 0 ()

eval :: TestCase a -> IO (Int, Int)
eval test = catch (f test) handler
  where
    f :: TestCase a -> IO (Int, Int)
    f test = do
        putStrLn $ info test
        return $ (points test, max_points test)

    handler :: ErrorCall -> IO (Int, Int)
    handler (ErrorCall msg) = do
        putStrLn $ red $ "\n[ERROR] " ++ msg
        return (0, 0)

runTests :: [TestCase a] -> IO (Int, Int)
runTests tests = do
    evals <- mapM eval tests
    let score = sum $ map fst evals
    let max_score = sum $ map snd evals
    return (score, max_score)
