import Data.Char
import Data.List

{- 
length l: o n´umero de elementos da lista l
• head l: a cabe¸ca da lista (n˜ao vazia) l
• tail l: a cauda da lista (n˜ao vazia) l
• last l: o ´ultimo elemento da lista (n˜ao vazia) l
• sqrt x: a raiz quadrada de x
• div x y: a divis˜ao inteira de x por y
• mod x y: o resto da divis˜ao inteira de x por y
-}

-------------------------------------------------------------------------------------------------------

-- 1)

--a)
perimetro :: Float -> Float
perimetro r = (r + r) * pi

--b)
dist :: (Double, Double) -> (Double, Double) -> Double
dist (x1, y1) (x2, y2) = sqrt ((x2 - x1)^2 + (y2 - y1)^2)

--c)
primUlt :: [a] -> (a, a)
primUlt (h:t) = (h, last (h:t))

--d)
multiplo :: Int -> Int -> Bool
multiplo m n | mod m n == 0 = True
             | otherwise = False

--e)
truncaImpar :: [Int] -> [Int]
truncaImpar l | mod (length l) 2 == 0 = l
              | otherwise = tail l

--f)
max2 :: Int -> Int -> Int
max2 x y | x > y = x
         | x < y = y

--g)
max3 :: Int -> Int -> Int -> Int
max3 x y z | (max2 x y) > z = max x y
           | otherwise = z

max3' :: Int -> Int -> Int -> Int
max3' x y z = max2 (max2 x y) z

-------------------------------------------------------------------------------------------------------

--2)
--a)
nRaizes :: Double -> Double -> Double -> Int
nRaizes x y z | delta1 < 0 = 0
                    | delta1 == 0 = 1 
                    | delta1 > 0 = 2
                    where delta1 = (y^2)-4*x*z

--b)
raizes :: Float -> Float -> Float -> [Float]
raizes a b c | delta < 0  = []
             | delta == 0 = [r]
             | delta > 0  = [r1, r2]
             where delta = (b^2 - 4 * a * c)
                   r = (- (b))/ (2 * a)
                   r1 = ((-b) + sqrt delta) / (2 * a)
                   r2 = ((-b) - sqrt delta) / (2 * a)

-------------------------------------------------------------------------------------------------------

--3)
type Hora = (Int, Int)
meiaNoiteEUmQuarto :: Hora
meiaNoiteEUmQuarto = (0, 15)
duasMenosUmQuarto :: Hora
duasMenosUmQuarto = (13, 45)

--a)
isValid :: Hora -> Bool
isValid (x, y) | (x < 24 && x >= 0) && (y >= 0 && y < 60) = True
               | otherwise = False

--b)
-- compare left with right
isGreater :: Hora -> Hora -> Bool
isGreater (h1, m1) (h2, m2) | h1 > h2 || h1 == h2 && m1 > m2 = True
                            | otherwise = False

--c)
convertToMinutes :: Hora -> Int
convertToMinutes (h, m) = h * 60 + m

--d)
convertToHours :: Int -> Hora
convertToHours x = (div x 60, mod x 60)

--e)
diffBetween :: Hora -> Hora -> Int
diffBetween h1 h2 = abs((convertToMinutes h1) - (convertToMinutes h2))

--f)
addMinutes :: Int -> Hora -> Hora
addMinutes x (h, m) = convertToHours ((convertToMinutes (h, m)) + x)

-------------------------------------------------------------------------------------------------------

--4)
data Hora' = H Int Int deriving (Show,Eq)

meiaNoiteEUmQuarto' :: Hora'
meiaNoiteEUmQuarto' = H 0 15
duasMenosUmQuarto' :: Hora'
duasMenosUmQuarto' = H 13 45

--a)
isValid' :: Hora' -> Bool
isValid' (H x y) | x >= 0 && x < 24 && y >= 0 && y < 60 = True
                 | otherwise = False

--b)
isGreater' :: Hora' -> Hora' -> Bool
isGreater' (H h1 m1) (H h2 m2) | h1 > h2 || h1 == h2 && m1 > m2 = True
                               | otherwise = False

--c)
convertToMinutes' :: Hora' -> Int
convertToMinutes'(H h m) = (h * 60) + m

--d)
convertToHours' :: Int -> Hora'
convertToHours' m = H (div m 60) (mod m 60)

--e)
diffBetween' :: Hora' -> Hora' -> Int
diffBetween' (H h1 m1) (H h2 m2) = abs (convertToMinutes' (H h1 m1) - convertToMinutes' (H h2 m2))

--f)
addMinutes' :: Int -> Hora' -> Hora'
addMinutes' x (H h1 m1) = convertToHours' (convertToMinutes' (H h1 m1) + x)

-------------------------------------------------------------------------------------------------------

--5)
data Semaforo = Verde | Amarelo | Vermelho deriving (Show,Eq)

--a)
next :: Semaforo -> Semaforo
next Verde = Amarelo
next Amarelo = Vermelho
next Vermelho = Verde

--b)
stop :: Semaforo -> Bool
stop Vermelho = True
stop _ = False

--c)
safe :: Semaforo -> Semaforo -> Bool
safe Vermelho _ = True
safe _ Vermelho = True
safe _ _ = False

-------------------------------------------------------------------------------------------------------
--6)
data Ponto = Cartesiano Double Double | Polar Double Double -- Polar: Origin distance / angle x axis
            deriving (Show,Eq)

ponto1 :: Ponto
ponto1 = Cartesiano (-1) 0
ponto2 :: Ponto
ponto2 = Polar 1 pi


--a)
posx :: Ponto -> Double
posx (Cartesiano x y) = x
posx (Polar d a) = d * (cos a)

--b)
posy :: Ponto -> Double
posy (Cartesiano x y) = y
posy (Polar d a) = d * (sin a)

--c)
raio :: Ponto -> Double
raio (Polar d a) = d
raio (Cartesiano x y) = sqrt (x^2 + y^2)

--d)
angulo :: Ponto -> Double
angulo (Polar d a) = a
angulo (Cartesiano x y) | x == 0 && y == 0 = 0
                        | x == 0 && y > 0 = pi/2
                        | x == 0 && y < 0 = -(pi/2)
                        | x > 0 && y == 0 = 0
                        | x < 0 && y == 0 = pi
                        | x > 0 = atan (y/x)
                        | x < 0 && y < 0 = atan(y/x) - pi
                        | x < 0 && y >= 0 = atan(y/x) + pi

--e)
dist' :: Ponto -> Ponto -> Double
dist' (Cartesiano x1 y1) (Cartesiano x2 y2) = sqrt (((x1 - x2) ^ 2) + (y1 - y2) ^ 2)
dist' (Polar d1 a1) (Polar a2 d2) = sqrt((px1-px2)^2+(py1-py2)^2)
                                   where 
                                   px1 = d1 * cos a1
                                   px2 = d2 * cos a2
                                   py1 = d1 * sin a1
                                   py2 = d2 * sin a2


-------------------------------------------------------------------------------------------------------
--7)
data Figura = Circulo Ponto Double
            | Rectangulo Ponto Ponto
            | Triangulo Ponto Ponto Ponto
            deriving (Show,Eq)

--a)
poligono :: Figura -> Bool
poligono (Circulo (Cartesiano x y) z) = if z > 0 then True else False
poligono (Rectangulo a b) = if (posx a) /= (posx b) && (posy a) /= (posy b) then True else False
poligono (Triangulo a b c) | (x+y > z) || (x+z > y) || (y + z > x) = True
                           | otherwise = False
                           where 
                              x = dist' a b
                              y = dist' a c
                              z = dist' b c

--b)
vertices :: Figura -> [Ponto]
vertices (Circulo (Cartesiano _ _) _) = []
vertices (Rectangulo (Cartesiano x1 y1) (Cartesiano x2 y2)) = [(Cartesiano x1 y1), (Cartesiano x1 y2), (Cartesiano x2 y2), (Cartesiano x2 y1)]
vertices (Triangulo a b c) = [a,b,c]

--c)
area :: Figura -> Double
area (Triangulo p1 p2 p3) =
            let a = dist' p1 p2
                b = dist' p2 p3
                c = dist' p3 p1
                s = (a+b+c) / 2 
            in sqrt (s*(s-a)*(s-b)*(s-c))
area (Circulo (Cartesiano x y) r) = (r^2) * pi
area (Rectangulo a b) | posx a > posx b = (posx a - posx b) * (posy a - posy b)
                      | otherwise = (posx b - posx a) * (posy b - posy a)


--d)
perimetro' :: Figura -> Double
perimetro' (Circulo c r) = 2 * r * pi
perimetro' (Rectangulo (Cartesiano x1 y1) (Cartesiano x2 y2)) = dist' (Cartesiano x1 y1) (Cartesiano x1 y2) + dist' (Cartesiano x1 y1) (Cartesiano x2 y1) + dist' (Cartesiano x2 y1) (Cartesiano x2 y2) + dist' (Cartesiano x2 y2) (Cartesiano x1 y2)
perimetro' (Triangulo a b c) = let p1 = dist' a b
                                   p2 = dist' b c
                                   p3 = dist' c a
                               in  p1 + p2 + p3 

perimetro'' :: Figura -> Double
perimetro'' (Circulo a r) = 2 * pi * r
perimetro'' (Rectangulo a b) = 2 * (((abs (posx a)) + (abs(posx b))) + ((abs (posy a)) + (abs(posy b))))
perimetro'' (Triangulo a b c) = let p1 = dist' a b
                                    p2 = dist' b c
                                    p3 = dist' c a
                                in p1 + p2 + p3 

-------------------------------------------------------------------------------------------------------
--8)
--a)
isLower :: Char -> Bool
isLower x = if ord(x) >= 97 && ord(x) <= 122 then True else False

--b)
isDigit :: Char -> Bool
isDigit x = if ord(x) >= 48 && ord(x) <= 57 then True else False

--c)
isAlpha :: Char -> Bool
isAlpha x = if ord(x) >= 65 && ord(x) <= 90 || ord(x) >= 97 && ord(x) <= 122 then True else False

--d)
toUpper :: Char -> Char
toUpper x | Data.Char.isLower x == True = chr (ord(x) - 32)
          | otherwise = x

intToDigit :: Int -> Char
intToDigit x = if elem x [0..9] then chr( ord('0') + x) else error ""

digitToInt :: Char -> Int
digitToInt x = if isAlpha x == True then (ord x - ord '0') else error ""