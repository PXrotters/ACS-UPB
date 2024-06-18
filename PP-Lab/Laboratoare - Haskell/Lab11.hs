instance Functor Maybe where
  fmap f x = 
    case x of
       Just v -> Just (f v)
       Nothing -> Nothing
 
instance Monad Maybe where
  return = Just
  mx >>= f = 
      case mx of 
        Just v -> f v
        Nothing -> Nothing

-- 11.1.1
add5 :: Maybe Int -> Maybe Int
add5 = fmap (+5)

-- 11.1.2
add :: Maybe Int -> Maybe Int -> Maybe Int
add ma mb = do
    a <- ma
    b <- mb
    return (a + b)

sub :: Maybe Int -> Maybe Int -> Maybe Int
sub ma mb = do
    a <- ma
    b <- mb
    return (a - b)

mult :: Maybe Int -> Maybe Int -> Maybe Int
mult ma mb = do
    a <- ma
    b <- mb
    return (a * b)

-- 11.2.1
main :: IO ()
main = putStrLn "Hello, World!"

-- 11.2.2
fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = fib (n - 1) + fib (n - 2)

main :: IO ()
main = do
    putStrLn "Enter a number:"
    n <- readLn
    print (fib n)

-- 11.2.3
import Data.List (sort)

main :: IO ()
main = do
    putStrLn "Enter the number of elements:"
    n <- readLn
    putStrLn "Enter the elements:"
    elements <- sequence (replicate n readLn)
    putStrLn "Sorted elements:"
    print (sort elements)

-- 11.2.4
collatz :: Int -> [Int]
collatz 1 = [1]
collatz n
    | even n    = n : collatz (n `div` 2)
    | otherwise = n : collatz (3 * n + 1)

main :: IO ()
main = do
    putStrLn "Enter a number:"
    n <- readLn
    putStrLn "Collatz sequence:"
    print (collatz n)

-- 11.3.1
type Pos = (Int, Int)

moveKnight :: Pos -> [Pos]
moveKnight (x, y) = do
    (dx, dy) <- [(2, 1), (2, -1), (-2, 1), (-2, -1), (1, 2), (1, -2), (-1, 2), (-1, -2)]
    let newPos = (x + dx, y + dy)
    guard (withinBounds newPos)
    return newPos
  where
    withinBounds (x, y) = x >= 1 && x <= 8 && y >= 1 && y <= 8

-- 11.3.2
canReachIn3 :: Pos -> Pos -> Bool
canReachIn3 start end = end `elem` (moveKnight =<< moveKnight =<< moveKnight start)

-- 11.3.3
canReachInK :: Int -> Pos -> Pos -> Bool
canReachInK 0 start end = start == end
canReachInK k start end = end `elem` (moveKnight =<< canReachInK (k-1) start)

-- 11.4.1
newtype Prob a = Prob [(a, Float)] deriving Show

instance Functor Prob where
    fmap f (Prob xs) = Prob [(f x, p) | (x, p) <- xs]

-- Check the functor laws
prob :: Prob Int
prob = Prob [(1, 0.5), (2, 0.25), (3, 0.25)]

-- fmap (+3) prob = Prob [(4, 0.5), (5, 0.25), (6, 0.25)]

-- 11.4.2
flatten :: Prob (Prob a) -> Prob a
flatten (Prob xs) = Prob [(a, p * q) | (Prob ys, p) <- xs, (a, q) <- ys]

-- Test flatten
nested_prob :: Prob (Prob Int)
nested_prob = Prob [(prob, 0.7), (prob, 0.3)]

-- flatten nested_prob = Prob [(1,0.35),(2,0.175),(3,0.175),(1,0.15),(2,0.075),(3,0.075)]

-- 11.4.3
instance Monad Prob where
    return x = Prob [(x, 1.0)]
    (Prob xs) >>= f = flatten (Prob [(f x, p) | (x, p) <- xs])

-- Define Applicative instance as required by Monad
instance Applicative Prob where
    pure = return
    (<*>) = ap

-- Test Monad laws
coin :: Prob Coin
coin = Prob [(Heads, 0.5), (Tails, 0.5)]

unfair_coin :: Prob Coin
unfair_coin = Prob [(Heads, 0.6), (Tails, 0.4)]

flipCoins :: Prob [Coin]
flipCoins = do
    x <- coin
    y <- coin
    z <- coin
    return [x, y, z]

-- 11.4.4
die :: Int -> Prob Int
die n = Prob [(i, 1.0 / fromIntegral n) | i <- [1..n]]

-- Example usage
-- (,) <$> (die 20) <*> (die 6) -- the probability distribution of rolling a d20 followed by a d6

-- 11.4.5
data Disease = HasDisease | NoDisease deriving Show
data TestResult = Positive | Negative deriving Show

testAccuracy :: Prob (Disease, TestResult)
testAccuracy = do
    disease <- Prob [(HasDisease, 0.01), (NoDisease, 0.99)]
    result <- case disease of
        HasDisease -> Prob [(Positive, 0.95), (Negative, 0.05)]
        NoDisease  -> Prob [(Positive, 0.05), (Negative, 0.95)]
    return (disease, result)

probabilityOfDiseaseGivenPositive :: Float
probabilityOfDiseaseGivenPositive =
    let Prob xs = testAccuracy
        positiveTests = filter (\(_, result) -> result == Positive) xs
        totalPositiveProb = sum (map snd positiveTests)
        diseaseGivenPositive = filter (\(disease, _) -> disease == HasDisease) positiveTests
        totalDiseasePositiveProb = sum (map snd diseaseGivenPositive)
    in totalDiseasePositiveProb / totalPositiveProb
