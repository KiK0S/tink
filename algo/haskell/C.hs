module Main where

data Segtree a = Leaf a | Segtree (Segtree a) a (Segtree a)
	deriving Show
build tl tr | tl == tr = (Leaf 0)
			| otherwise = Segtree (build tl (div (tl + tr) 2)) 0 (build ((div (tl + tr) 2) + 1) tr)

update (Leaf t) tl tr l r x
			| (l <= tl && tr <= r) = Leaf (t + x)
			| otherwise = Leaf t
update (Segtree a b c) tl tr l r x 
			| (tl > r) || (l > tr) = Segtree a b c
			| (l <= tl) && (tr <= r) = Segtree a (b + x) c
			| otherwise = Segtree (update a tl (div (tl + tr) 2) l r x) b (update c ((div (tl + tr) 2) + 1) tr l r x)

get (Leaf t) tl tr pos = t
get (Segtree a b c) tl tr pos
			| pos <= (div (tl + tr) 2) = b + (get a tl (div (tl + tr) 2) pos)
			| otherwise = b + (get c ((div (tl + tr) 2) + 1) tr pos)


rev [] a = a
rev (x : xs) a = rev xs (x : a)
rev' x = rev x []
split [] a = a
split (x : xs) (a : as)
			| x == ' ' = split xs ([] : (a : as))
			| otherwise = (split xs ((x : a) : as))

process_update [a, b, c] t n = do
	let a' = read a::Int
	let b' = read b::Int
	let c' = read c::Int
	return (update t 0 (n - 1) (a' - 1) (b' - 1) c')

process_get [a] t n = do
	let a' = read a::Int
	putStr(show (get t 0 (n - 1) (a' - 1)))
	putStr(" ")
	return t

process (x : xs) t n
			| x == "a" = (process_update xs t n)
			| otherwise = (process_get xs t n)

query :: Int -> Segtree Int -> Int -> IO (Segtree Int)
query 0 t n = do
	return t

query q t n = do
	s <- getLine
	let s' = rev' 
		   $ map ((flip rev) "")
		   $ split s [[]]
	t' <- process s' t n
	(query (q - 1) t' n)

read_array q t [] n = t
read_array q t (x : xs) n = (read_array (q + 1) (update t 0 n q q x) xs n)

main = do
	s <- getLine
	let n = (read s::Int)
	let t = build 0 (n - 1)
	s <- getLine
	let s' = rev' 
		   $ map (read :: String -> Int)
		   $ map ((flip rev) "")
		   $ split s [[]] 
	let t' = read_array 0 t s' (n - 1)
	s <- getLine
	let q = (read s::Int)
	tmp <- query q t' n
	return ()