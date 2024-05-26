module Parser (parseLambda, parseLine) where

import Control.Monad
import Control.Applicative

import Data.Char (isAlpha, isAlphaNum, isUpper, isDigit)
import Lambda
import Binding

newtype Parser a = Parser { parse :: String -> Maybe (a, String) }

-- Functorul permite aplicarea unei functii asupra rezultatului unui parser, fara a modifica parserul in sine (un tip care implementeaza fmap)
instance Functor Parser where
    fmap transform (Parser parser) = Parser $ \input -> case parser input of
        Just (result, rest) -> Just (transform result, rest)
        Nothing -> Nothing

-- Permite secventierea parserelor, adica rularea unui parser si utilizarea rezultatului sau pentru a determina urmatorul parser de aplicat
instance Monad Parser where
    return x = Parser $ \input -> Just (x, input)
    (Parser parser) >>= nextParserFunction = Parser $ \input -> case parser input of
        Just (result, rest) -> parse (nextParserFunction result) rest
        Nothing -> Nothing

-- Permite combinarea rezultatelor mai multor parsere
instance Applicative Parser where
    pure x = Parser $ \input -> Just (x, input) -- introduce o valoare intr-un context de parsare fara a consuma nicio parte a inputului
    (Parser parserF) <*> (Parser parserA) = Parser $ \input -> case parserF input of -- aplica un parser care contine o functie la un alt parser care contine un argument
        Just (function, rest) -> case parserA rest of  -- aplica parserA pe rest
            Just (argument, rest') -> Just (function argument, rest')
            Nothing -> Nothing
        Nothing -> Nothing

-- Permite incercarea unui parser si, in caz de esec, incercarea altui parser
instance Alternative Parser where
    empty = Parser (const Nothing) -- este un parser care nu reuseste niciodata. Este util atunci cand avem nevoie de un parser care sa nu consume niciun input si sa nu returneze niciun rezultat valid
    (Parser parserA) <|> (Parser parserB) = Parser $ \input -> parserA input <|> parserB input

-- PARSERE PENTRU CARACTERE, STRINGURI, SPATII SI VARIABILE

-- Parseaza un caracter specific
char :: Char -> Parser Char
char c = Parser $ \input -> case input of
    (x:xs) | x == c -> Just (c, xs)
    _ -> Nothing

-- Parseaza un sir de caractere
string :: String -> Parser String
string [] = Parser $ \input -> Just ([], input)
string (c:cs) = Parser $ \input -> case input of
    (x:xs) | x == c -> do
        (rest, finalInput) <- parse (string cs) xs
        return (c:rest, finalInput)
    _ -> Nothing

-- Parseaza un caracter alfabetic
alpha :: Parser Char
alpha = Parser $ \input -> case input of
    (x:xs) | isAlpha x -> Just (x, xs)
    _ -> Nothing

-- Parseaza un caracter alfanumeric
alphaNum :: Parser Char
alphaNum = Parser $ \input -> case input of
    (x:xs) | isAlphaNum x -> Just (x, xs)
    _ -> Nothing

-- Parseaza un caracter majuscula
uppercase :: Parser Char
uppercase = Parser $ \input -> case input of
    (x:xs) | isUpper x -> Just (x, xs)
    _ -> Nothing

-- Parseaza o cifra
digit :: Parser Char
digit = Parser $ \input -> case input of
    (x:xs) | isDigit x -> Just (x, xs)
    _ -> Nothing

-- Combina parserele pentru a parsa un caracter majuscula sau o cifra
uppercaseOrDigit :: Parser Char
uppercaseOrDigit = uppercase <|> digit

-- Parseaza o variabila, care incepe cu un caracter alfabetic si posibil urmat de mai multe caractere alfanumerice
variable :: Parser String
variable = do
    first <- alpha
    rest <- many alphaNum
    return (first : rest)

-- Parseaza un spatiu
space :: Parser Char
space = char ' '

-- Parseaza mai multe spatii
spaces :: Parser String
spaces = many space

-- PARSERE PENTRU EXPRESII LAMBDA

-- Parseaza o variabila si o converteste intr-o expresie "Var"
varParser :: Parser Lambda
varParser = Var <$> variable

-- Parseaza o aplicatie de functii lambda
appParser :: Parser Lambda
appParser = do
    char '('
    e1 <- lambdaParser
    space
    e2 <- lambdaParser
    char ')'
    return (App e1 e2)

-- Parseza o abstractizare
absParser :: Parser Lambda
absParser = do
    char '\\'
    x <- variable
    char '.'
    e <- lambdaParser
    return (Abs x e)

-- Parseaza un macro
macroParser :: Parser Lambda
macroParser = do
    x <- some uppercaseOrDigit
    return (Macro x)

-- Parseaza o linie de binding
bindingParser :: Parser Line
bindingParser = do
    x <- variable
    spaces
    char '='
    spaces
    e <- lambdaParser
    return (Binding x e)

-- Combinatie de parsere care incearca fiecare tip din expresie in ordine
lambdaParser :: Parser Lambda
lambdaParser = macroParser <|> varParser <|> appParser <|> absParser

-- Parseaza o expresie lambda completa dintr-un sir de caractere
parseLambda :: String -> Lambda
parseLambda input = case parse (lambdaParser <* spaces) input of --parseaza o expresie lambda si apoi ignora spatiile care urmeaza imediat dupa acestea
    Just (e, "") -> e
    _ -> error "Invalid input for parsing!"

-- Parseaza o linie de evaluare a unei expresii lambda
evalParser :: Parser Line
evalParser = Eval <$> lambdaParser

-- Parseaza o linie de binding sau o linie de evaluare, returnand un Line (sau eroare)
parseLine :: String -> Either String Line
parseLine input = case parse (bindingParser <|> evalParser) input of
    Just (line, "") -> Right line
    _ -> Left "Invalid input for parsing!"