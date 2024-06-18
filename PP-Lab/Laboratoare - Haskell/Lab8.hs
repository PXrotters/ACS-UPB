-- 8.1.1
fact :: Int -> Int
fact n = go n 1
  where
    go 0 acc = acc
    go n acc = go (n - 1) (acc * n)

-- 8.1.2
mygcd :: Int -> Int -> Int
mygcd a b = go a b
  where
    go a 0 = a
    go a b = go b (a `mod` b)

-- 8.1.3
mySqrt :: Int -> Int
mySqrt n = floor (sqrt (fromIntegral n :: Double))

-- 8.1.4
mymin :: [Int] -> Int
mymin [] = error "empty list"
mymin (x:xs) = go xs x
  where
    go [] acc = acc
    go (y:ys) acc = go ys (min y acc)

mymax :: [Int] -> Int
mymax [] = error "empty list"
mymax (x:xs) = go xs x
  where
    go [] acc = acc
    go (y:ys) acc = go ys (max y acc)

-- 8.1.5
unique :: [Int] -> [Int]
unique [] = []
unique (x:xs) = x : unique (filter (/= x) xs)

-- 8.1.6
fizzBuzz :: [Int] -> [String]
fizzBuzz = map fb
  where
    fb n
      | n `mod` 15 == 0 = "FizzBuzz"
      | n `mod` 3 == 0  = "Fizz"
      | n `mod` 5 == 0  = "Buzz"
      | otherwise       = show n

-- 8.1.7
extendedFizzBuzz :: [Int] -> [String]
extendedFizzBuzz = map efb
  where
    efb n
      | n `mod` 105 == 0 = "FizzBuzzBazz"
      | n `mod` 35 == 0  = "BuzzBazz"
      | n `mod` 21 == 0  = "FizzBazz"
      | n `mod` 15 == 0  = "FizzBuzz"
      | n `mod` 7 == 0   = "Bazz"
      | n `mod` 5 == 0   = "Buzz"
      | n `mod` 3 == 0   = "Fizz"
      | otherwise        = show n

-- 8.2.1
mem :: (Integer -> Bool) -> Integer -> Bool
mem s x = s x

-- 8.2.2
powersOf2 :: Integer -> Bool
powersOf2 x = x > 0 && (x .&. (x - 1)) == 0

-- 8.2.3
naturals :: Integer -> Bool
naturals x = x >= 0

-- 8.2.4
intersection :: (Integer -> Bool) -> (Integer -> Bool) -> (Integer -> Bool)
intersection s1 s2 = \x -> s1 x && s2 x

-- 8.2.5
intersection' :: (Integer -> Bool) -> (Integer -> Bool) -> Integer -> Bool
intersection' s1 s2 x = s1 x && s2 x

-- 8.2.6
toSet :: [Integer] -> (Integer -> Bool)
toSet xs = \x -> x `elem` xs

-- 8.2.7
capList :: [Integer -> Bool] -> Integer -> Bool
capList [] _ = False
capList sets x = all (\s -> s x) sets

-- 8.2.8
capList' :: [Integer -> Bool] -> Integer -> Bool
capList' [] _ = False
capList' (s:ss) x = s x && capList' ss x

-- 8.2.9
setsOperation :: [Integer -> Bool] -> ((Integer -> Bool) -> (Integer -> Bool) -> (Integer -> Bool)) -> (Integer -> Bool)
setsOperation sets op = foldr1 op sets

-- 8.2.10
applySet :: (Integer -> Bool) -> [Integer] -> [Integer]
applySet s xs = filter s xs

-- 8.2.11
partitionSet :: (Integer -> Bool) -> [Integer] -> ([Integer], [Integer])
partitionSet s xs = partition s xs
  where
    partition _ [] = ([], [])
    partition s (x:xs) =
      let (inSet, outSet) = partition s xs
      in if s x then (x:inSet, outSet) else (inSet, x:outSet)

-- 8.3.1
mymapl :: (a -> b) -> [a] -> [b]
mymapl f = foldl (\acc x -> acc ++ [f x]) []

mymapr :: (a -> b) -> [a] -> [b]
mymapr f = foldr (\x acc -> f x : acc) []

-- 8.3.2
myfilterl :: (a -> Bool) -> [a] -> [a]
myfilterl p = foldl (\acc x -> if p x then acc ++ [x] else acc) []

myfilterr :: (a -> Bool) -> [a] -> [a]
myfilterr p = foldr (\x acc -> if p x then x : acc else acc) []

-- 8.3.3
myfoldl :: (a -> b -> a) -> a -> [b] -> a
myfoldl f z xs = foldr (\x g a -> g (f a x)) id xs z

-- 8.3.4
bubbleSort :: [Int] -> [Int]
bubbleSort [] = []
bubbleSort xs = bubble xs (length xs)
  where
    bubble xs 0 = xs
    bubble xs n = bubble (pass xs) (n - 1)
    pass [x] = [x]
    pass (x:y:ys)
      | x > y     = y : pass (x:ys)
      | otherwise = x : pass (y:ys)

-- 8.3.5
quickSort :: [Int] -> [Int]
quickSort [] = []
quickSort (x:xs) = quickSort [y | y <- xs, y <= x]
                 ++ [x] ++
                 quickSort [y | y <- xs, y > x]
