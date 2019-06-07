module Main where

input 0 = do
	return ()
input a = do
	s <- getLine
	let x = (read s::Int)
	tmp <- input (a - 1)
	putStrLn(show(x))
	return ()

main = do
	s <- getLine
	let n = (read s::Int)
	input n