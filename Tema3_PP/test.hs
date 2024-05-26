import System.Environment

import Tests.Test
import Tests.LambdaTest
import Tests.ParserTest
import Tests.BindingTest
import Tests.DefaultTest

main :: IO ()
main = do
    args <- getArgs
    case args of
        ["lambda"] -> runTest lambdaTests
        ["parser"] -> runTest parserTests
        ["binding"] -> runTest bindingTests
        ["default"] -> runTest defaultTests
        [] -> allTests
        _ -> putStrLn "Invalid arguments"

runTest :: IO (Int, Int) -> IO ()
runTest test = do
    (points, max_points) <- test
    putStrLn $ "Total: " ++ show points ++ "/" ++ show max_points

allTests :: IO ()
allTests = do
    (lambda_points, max_lambda_points) <- lambdaTests
    (parser_points, max_parser_points) <- parserTests
    (binding_points, max_binding_points) <- bindingTests
    (default_points, max_default_points) <- defaultTests
    let total = lambda_points + parser_points + binding_points + default_points
    let max_points = max_lambda_points + max_parser_points + max_binding_points + max_default_points
    putStrLn $ "Total: " ++ show total ++ "/" ++ show max_points
