module Binding where

import Lambda
import Data.Maybe (fromMaybe)

type Context = [(String, Lambda)]

data Line = Eval Lambda 
          | Binding String Lambda deriving (Eq)

instance Show Line where
    show (Eval l) = show l
    show (Binding s l) = s ++ " = " ++ show l

-- 3.1.
simplifyCtx :: Context -> (Lambda -> Lambda) -> Lambda -> Either String [Lambda]
simplifyCtx context stepType expr = do
    substitutedExpression <- substituteMacros context expr
    return (simplify stepType substitutedExpression)
    where
        -- Functie auxiliara pentru substituirea macro-urilor din context
        substituteMacros :: Context -> Lambda -> Either String Lambda
        substituteMacros context (Var x) = return (Var x)
        substituteMacros context (App e1 e2) = App <$> substituteMacros context e1 <*> substituteMacros context e2
        substituteMacros context (Abs x e) = Abs x <$> substituteMacros context e
        substituteMacros context (Macro x) = case lookup x context of
            Just x -> return x
            Nothing -> Left "Undefiend Macro!"

normalCtx :: Context -> Lambda -> Either String [Lambda]
normalCtx ctx = simplifyCtx ctx normalStep

applicativeCtx :: Context -> Lambda -> Either String [Lambda]
applicativeCtx ctx = simplifyCtx ctx applicativeStep
