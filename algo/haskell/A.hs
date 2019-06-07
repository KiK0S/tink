module Main where

split (' ' : xs) b = [b, xs]
split (x : xs) b = split xs (x : b)
rev "" a = a
rev (x : xs) a = rev xs (x : a)

main = do
	s <- getLine
	let [a', b] = split s ""
	let a = rev a' ""
	-- putStrLn a
	-- putStrLn b
	let ab = (read a::Int)
	let bb = (read b::Int)
	putStrLn (show (ab + bb))