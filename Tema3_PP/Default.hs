module Default where

import Lambda
import Binding

-- Variables (for convenience)
vx = Var "x"
vy = Var "y"
vz = Var "z"
vf = Var "f"
vg = Var "g"
vh = Var "h"
vm = Var "m"
vn = Var "n"

-- Basic combinators
m = Abs "x" $ App vx vx
i = Abs "x" $ vx
k = Abs "x" $ Abs "y" $ vx
ki = Abs "x" $ Abs "y" $ vy
c = Abs "x" $ Abs "y" $ Abs "z" $ App (App vx vz) vy
y = Abs "f" $ App fix fix
  where fix = Abs "x" $ App vf (App vx vx)

-- 4.1. Boolean encodings
bTrue = k  -- returneaza primul argument identic cu k-combinator
bFalse = ki  -- returneza al doilea argument identic cu ki-combinator
bAnd = Abs "x" $ Abs "y" $ App (App vx vy) vx  -- daca x e TRUE atunci returneaza y, daca x e FALSE atunci returneaza x
bOr = Abs "x" $ Abs "y" $ App (App vx vx) vy -- daca x e TRUE atunci returneaz x, daca x e FALSE atunci returneaza y
bNot = Abs "x" $ App (App vx bFalse) bTrue  -- daca x e TRUE atunci returneaza bFalse, altfel returneaza bTrue
bXor = Abs "x" $ Abs "y" $ App (App bOr (App (App bAnd (App vx (App bNot vy))) (App (App bNot vx) vy))) bFalse -- daca exact unul dintre x si y e TRUE returneaza bTrue, altfel daca ambele sunt TRUE/FALSE returneaza bFalse

-- 4.2. Pair encodings
pair = Abs "x" $ Abs "y" $ Abs "f" $ App (App vf vx) vy  -- creaza o pereche reprezentata ca o functie care accepta un argument f si aplica f la cele 2 valori al perechii
first = Abs "x" $ App vx bTrue  -- extractia primei componente
second = Abs "x" $ App vx bFalse  -- extractia celei de-a doua componente

-- 4.3. Natural number encodings
n0 = Abs "f" $ i  -- Zero e reprezentat ca o functie care primeste o functie f si returneaza argumentul sau neschimbat identic cu i-combinator
n1 = Abs "f" $ Abs "x" $ App vf vx  -- Unu e reprezentat ca o functie care primeste o functie f si un argument x si apoi aplica f la x (f(x))
n2 = Abs "f" $ Abs "x" $ App vf (App vf vx)  -- Doi este reprezentat la fel ca unu, doar ca functia f este aplicata de 2 ori la x (f(f(x)))

nSucc = Abs "n" $ Abs "f" $ Abs "x" $ App vf (App (App vn vf) vx)  -- Primeste un numar natural n si returneaza succesorul sau. Se aplica functia f la x, unde f este aplicata la n si la x (f(n(x)))
nPred = Abs "n" $ Abs "f" $ Abs "x" $ App (App (App vn (Abs "g" $ Abs "h" $ App vh (App vg vf))) (Abs "y" $ vx)) (Abs "y" $ vy)  -- Se aplica n pe prima functie anonima care inverseza operatia de incrementare. Pe urma, aplicam x pe functia rezultata si returnam rezultatul.

nAdd = Abs "m" $ Abs "n" $ Abs "f" $ Abs "x" $ App (App vm vf) (App (App vn vf) vx)  -- Se aplica functia f de m ori pe x, apoi aplica functia de n ori pe rezultatul anterior
nSub = Abs "m" $ Abs "n" $ App (App vn nPred) vm  -- Se aplica functia de predecesor pe n apoi pe m
nMult = Abs "m" $ Abs "n" $ Abs "f" $ App vm (App vn vf)  -- Se aplica f de n ori pe m

-- Default Context
defaultContext :: Context
defaultContext = 
    [ ("M", m)
    , ("I", i)
    , ("K", k)
    , ("KI", ki)
    , ("C", c)
    , ("Y", y)
    , ("TRUE", bTrue)
    , ("FALSE", bFalse)
    , ("AND", bAnd)
    , ("OR", bOr)
    , ("NOT", bNot)
    , ("XOR", bXor)
    , ("PAIR", pair)
    , ("FST", first)
    , ("SND", second)
    , ("N0", n0)
    , ("N1", n1)
    , ("N2", n2)
    , ("SUCC", nSucc)
    , ("PRED", nPred)
    ,("ADD", nAdd)
    , ("SUB", nSub)
    , ("MULT", nMult)
    ]
