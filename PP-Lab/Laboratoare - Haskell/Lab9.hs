--  9.1.1
nats :: [Integer]
nats = [0, 1..]

--  9.1.2
-- 1, 3, 5, 7, ...
odds :: [Integer]
odds = [1, 3..]

-- 0, 1, 4, 9, ...
squares :: [Integer]
squares = [n^2 | n <- [0..]]

-- 9.1.3
fibs :: [Integer]
fibs = 0 : 1 : zipWith (+) fibs(tail fibs)

-- 9.2.1
data BTree = Node Int BTree BTree | Nil
 
data PrintInfo = PrintInfo {
    len :: Int,
    center :: Int,
    text :: [String]
}
 
pp :: BTree -> PrintInfo
pp Nil = PrintInfo 3 2 ["Nil"]
pp (Node x l r) = seq check PrintInfo nlen ncenter ntext
  where
    check = if (length (show x)) > nlen then error "Nice try" else ()
    pp_l = pp l
    pp_r = pp r
    nlen = len pp_l + len pp_r + 1
    ncenter = len pp_l + 1
    ntext = aligned_x : center_line : dotted_line : down_lines : combined_lines
      where
        aligned_x = replicate (ncenter - (div (length (show x)) 2) - 1) ' ' ++ show x
        center_line = replicate (ncenter - 1) ' ' ++ "|"
        dotted_line = replicate (center pp_l - 1) ' ' ++ 
                      replicate (nlen - center pp_l - center pp_r + 2) '-'
        down_lines = replicate (center pp_l - 1) ' ' ++ "|" ++
                     replicate (nlen - center pp_l - center pp_r) ' ' ++ "|"
        combined_lines = zipPad "" (combine) (text pp_l) (text pp_r)
          where
            zipPad :: a -> (a -> a -> a) -> [a] -> [a] -> [a]
            zipPad pad f [] [] = []
            zipPad pad f [] (y:ys) = y : zipPad pad f [pad] ys
            zipPad pad f (x:xs) [] = x : zipPad pad f xs [pad]
            zipPad pad f (x:xs) (y:ys) = f x y : zipPad pad f xs ys
            combine l r = l ++ replicate (len pp_l - length l + 1) ' ' ++ r
 
instance Show BTree where
    show = unlines . text . pp
 
tree :: BTree
tree = Node 1 (Node 2 Nil Nil) (Node 3 Nil Nil)

-- Infinite binary tree data type
data StreamBTree = StreamNode Int StreamBTree StreamBTree
sbtree = StreamNode 1 sbtree sbtree

-- Function to slice an infinite tree into a finite tree up to a given depth k
sliceTree :: Int -> StreamBTree -> BTree
sliceTree k (StreamNode v l r)
  | k <= 0    = Nil
  | otherwise = Node v (sliceTree (k - 1) l) (sliceTree (k - 1) r)

-- 9.2.2
repeatTree :: Int -> StreamBTree
repeatTree k = StreamNode k (repeatTree k) (repeatTree k)

-- 9.2.3
generateTree :: Int -> (Int -> Int) -> (Int -> Int) -> StreamBTree
generateTree k leftF rightF = StreamNode k (generateTree (leftF k) leftF rightF) (generateTree (rightF k) leftF rightF)

-- 9.3.1
build :: (Double -> Double) -> Double -> [Double]
build g a0 = a0 : build g (g a0)

naturals :: [Double]
naturals = build (+1) 0

-- 9.3.2
-- 0, 1, 0, 1, 0, 1, 0, ...
alternatingBinary :: [Double]
alternatingBinary = build (\x -> 1 - x) 0

-- 0, -1, 2, -3, 4, -5, ...
alternatingCons = build (\x -> -x - 1) 0
 
-- 1, -2, 4, -8, 16, ...
alternatingPowers :: [Double]
alternatingPowers = build (\x -> -2 * x) 1

-- 9.3.3
select :: Double -> [Double] -> Double
select e (x1:x2:xs)
    | abs (x1 - x2) < e = x1
    | otherwise = select e (x2:xs)

sampleStream :: [Double]
sampleStream = [1, 1.1, 1.2, 1.25, 1.27, 1.272, 1.273]

-- 9.3.4
fibRatios :: [Double]
fibRatios = zipWith (/) (map fromIntegral (tail fibs)) (map fromIntegral fibs)


phiApprox :: Double -> Double
phiApprox e = select e fibRatios

goldenRatioApprox :: Double
goldenRatioApprox = phiApprox 0.00001
