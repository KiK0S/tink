module Main where
	
data Treap x y = Empty | Treap (Treap x y) x y (Treap x y) 
		deriving Show


getleft Empty = Empty
getleft (Treap l x y r) = l
getright Empty = Empty
getright (Treap l x y r) = r
split Empty x  = do
	return [Empty, Empty]
split (Treap l x y r) val = do
		if x <= val
			then do
				[a, b] <- (split r val)
				return [(Treap l x y a), b]
			else do
				[a, b] <- (split l val)
				return [a, (Treap b x y r)]
merge Empty t = t
merge t Empty = t
merge (Treap ll xl yl rl) (Treap lr xr yr rr)
		| yl > yr = (Treap ll xl yl (merge rl (Treap lr xr yr rr)))
		| otherwise = (Treap (merge (Treap ll xl yl rl) lr) xr yr rr)

getmin :: Treap Int Int -> String
getmax :: Treap Int Int -> String

emp Empty = True
emp t = False

getmin Empty = "none"
getmin (Treap l x y r) 
		| emp l = (show x :: String) 
		| otherwise = getmin l
getmax Empty = "none"
getmax (Treap l x y r) 
		| emp r = (show x :: String) 
		| otherwise = getmax r


myinsert t x = do 
	[l, r] <- split t (x - 1) 
	[m, r'] <- split r x
	let l' = merge l (Treap Empty x (mod (13 * x * x * x * x * x * x + 179 * x * x * 34 * x - 678 * x + 192 * x * x) 1000000000)  Empty)
	let t' = merge l' r'
	return t'

myerase t x = do
	[l, r] <- split t (x - 1)
	[m, r'] <- split r x
	return (merge l r')

prev t x = do
	[l, r] <- split t (x - 1)
	putStrLn (getmax l)
	return t

next t x = do
	[l, r] <- split t x
	putStrLn (getmin r)
	return t

wr t
	| emp t = "false"
	| otherwise = "true"

exists t x = do
	[l, r] <- split t (x - 1)
	[m, r'] <- split r x
	putStrLn (wr m)
	return t


rev [] a = a
rev (x : xs) a = rev xs (x : a)
rev' x = rev x []
spli [] a = a
spli (x : xs) (a : as)
			| x == '\n' = spli xs ([] : (a : as))
			| otherwise = (spli xs ((x : a) : as))

spl a (' ' : xs) = [a, xs]
spl a (x : xs) = spl (x : a) xs

process t tp x
	| tp == "exists" = exists t x
	| tp == "next" = next t x
	| tp == "prev" = prev t x
	| tp == "insert" = myinsert t x
	| tp == "delete" = myerase t x

query [] t = do 
	return ()

query ("" : xs) t = do
	(query xs t)

query (s : xs) t = do
	let [tp, x] = (spl [] s)
	let tp' = rev' tp
	let x' = (read x::Int)
	t' <- process t tp' x'
	-- putStrLn (show t')
	(query xs t')

main = do
	s <- getContents
	let s' = rev'
	      $ map rev'
	      $ spli s [[]]
	query s' Empty
	return ()