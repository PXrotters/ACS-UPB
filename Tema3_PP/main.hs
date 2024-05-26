import System.IO
import Data.List (intercalate)

import Lambda
import Parser
import Binding 
import Default


main :: IO ()
main = interpreter defaultContext

interpreter :: Context -> IO ()
interpreter ctx = do
    putStr "λ> "
    hFlush stdout

    input <- getLine
    case input of
        ":q" -> return ()

        ":r" -> interpreter defaultContext

        ":ctx" -> do
            printList ctx
            interpreter ctx

        _ -> case parseLine input of
            Left err -> do
                putStrLn $ "Error: " ++ err
                interpreter ctx

            Right (Binding s l) -> do
                interpreter ((s, l) : ctx)

            Right (Eval l) -> do
                case normalCtx ctx l of
                    Left err -> do
                        putStrLn $ "Error: " ++ err
                        interpreter ctx

                    Right l -> do
                        printList l
                        interpreter ctx

printList :: (Show a) => [a] -> IO ()
printList s = putStrLn $ intercalate "\n" $ map show s
