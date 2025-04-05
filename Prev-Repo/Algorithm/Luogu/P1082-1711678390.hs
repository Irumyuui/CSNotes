module Main where
import Data.Char (ord)
import qualified GHC.TypeLits as Data
import qualified Data.List as Data.Text

int ::  String -> Integer
int s = int' s (toInteger 0)
        where int' :: String -> Integer -> Integer
              int' [] n = n
              int' (c:cs) n = int' cs $ n * 10 + toInteger (ord c - ord '0')

exgcd :: Integral a => a -> a -> (a, a, a)
exgcd a b | b == 0 = (a, 1, 0)
          | otherwise = let (d, x, y) = exgcd b (a `mod` b)
                         in (d, y, x - (a `div` b) * y)

main :: IO ()
main = do
    [a, b] <- map int . Data.Text.words <$> getLine
    let (d, x, y) = exgcd a b
     in print $ ((x `rem` b) + b) `rem` b

