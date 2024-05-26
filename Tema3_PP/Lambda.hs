module Lambda where

import Data.List (nub, (\\))  --nub -> eliminarea duplicatelor
                              --(\\) -> diferenta intre 2 liste

data Lambda = Var String
            | App Lambda Lambda
            | Abs String Lambda
            | Macro String

-- Modul de afisare
instance Show Lambda where
    show (Var x) = x
    show (App e1 e2) = "(" ++ show e1 ++ " " ++ show e2 ++ ")"
    show (Abs x e) = "λ" ++ x ++ "." ++ show e
    show (Macro x) = x

instance Eq Lambda where -- Eq defineste cum sa fie comparate valorile de tip Lambda
    -- Aceasta permite sa comparam 2 expresii lambda pentru egalitate 
    e1 == e2 = eq e1 e2 ([],[],[]) where 
      eq (Var x) (Var y) (env,xb,yb) = elem (x,y) env || (not $ elem x xb || elem y yb)
      eq (App e1 e2) (App f1 f2) env = eq e1 f1 env && eq e2 f2 env
      eq (Abs x e) (Abs y f) (env,xb,yb) = eq e f ((x,y):env,x:xb,y:yb)
      eq (Macro x) (Macro y) _ = x == y
      eq _ _ _ = False

-- 1.1.
vars :: Lambda -> [String]
vars (Var x) = [x]
vars (App e1 e2) = nub (vars e1 ++ vars e2)
vars (Abs x e) = nub (x : vars e)
vars (Macro x) = [x]

-- 1.2.
freeVars :: Lambda -> [String]
freeVars (Var x) = [x]
freeVars (App e1 e2) = nub (freeVars e1 ++ freeVars e2)
freeVars (Abs x e) = freeVars e \\ [x]
freeVars (Macro x) = [x]

-- 1.3.
newVar :: [String] -> String
-- filtreaza lista infList, pastrand doar acele string-uri care nu se afla in lista xs.
-- Dupa filtrare, se aplica functia head pentru a obtine primul element din lista rezultata, adica cel mai mic string lexicografic care nu apare in lista xs
newVar xs = head $ filter (`notElem` xs) infList where 
  -- definim o lista infinita care continee toate stringurile de lungime 1 urmate de toate stringurile de lungime 2, de lungime 3 etc
  infList = [[x] | x <- ['a'..'z']] ++ [x:xs | xs <- infList, x <- ['a'..'z']]

-- 1.4.
isNormalForm :: Lambda -> Bool
isNormalForm (Var x) = True -- cazul cand expresia este o variabila, care e in forma normala
isNormalForm (App (Abs x e1) e2) = False -- cazul cand expresia este o aplicatie de functii in care primul argument este o abstractizare lambda. O expresie nu este in forma normala daca este o aplicatie de functii in care primul argument este o abstractizare lambda
isNormalForm (App e1 e2) = isNormalForm e1 && isNormalForm e2 -- cazul cand expresia este o aplicatie de functii intre doua sub-expresii e1 si e2. Functia verifica recursiv daca ambele sub-expresii e1 si e2 sunt in forma normala
isNormalForm (Abs x e) = isNormalForm e -- verifica recursiv daca corpul abstractizarii e este in forma normala
isNormalForm (Macro x) = True -- cazul cand expresia este un macro, care e in forma normala

-- 1.5.
reduce :: String -> Lambda -> Lambda -> Lambda
reduce x e1 e2 = substitute x e1 e2 where
  substitute :: String -> Lambda -> Lambda -> Lambda
  substitute string (Var x) expr
    | string == x = expr
    | otherwise = (Var x)
  substitute string (App e1 e2) expr = App (substitute string e1 expr) (substitute string e2 expr)
  substitute string (Abs x e) expr
    | string == x = Abs x e
    | x `elem` freeVars expr = Abs y (substitute string (substitute x e (Var y)) expr)
    | otherwise = Abs x (substitute string e expr)
    where y = newVar (vars (Abs x e) ++ vars expr)
  substitute string (Macro x) expr = Macro x

-- 1.6.
normalStep :: Lambda -> Lambda
normalStep (App (Abs x e1) e2) = reduce x e1 e2
normalStep (App e1 e2) = if isNormalForm e1
  then App e1 (normalStep e2)
  else App (normalStep e1) e2
normalStep (Abs x e) = Abs x (normalStep e)
normalStep (Macro x) = Macro x
normalStep x = x

-- 1.7.
applicativeStep :: Lambda -> Lambda
applicativeStep (App (Abs x e1) e2) = if isNormalForm e2
  then reduce x e1 e2
  else App (Abs x e1) (applicativeStep e2)
applicativeStep (App e1 e2) = if isNormalForm e1
  then App e1 (applicativeStep e2)
  else App (applicativeStep e1 ) e2
applicativeStep (Abs x e) = Abs x (applicativeStep e)
applicativeStep (Macro x) = Macro x
applicativeStep x = x

-- 1.8.
simplify :: (Lambda -> Lambda) -> Lambda -> [Lambda]
simplify stepType expr = go [expr] where
  go steps@(current:_) = if isNormalForm current
    then reverse steps
    else go (stepType current : steps)

normal :: Lambda -> [Lambda]
normal = simplify normalStep

applicative :: Lambda -> [Lambda]
applicative = simplify applicativeStep
