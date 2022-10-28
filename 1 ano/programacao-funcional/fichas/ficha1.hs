import Data.Char

-- my drafts

--digitar no cmd  > [x*2| x<-[1..10]]

-- end of my drafts

perimetro :: Float -> Float
perimetro r = (r + r) * pi

dist :: (Double, Double) -> (Double, Double) -> Double
dist (x,y) (x2,y2) = sqrt ((x2 - x)^2 + (y2 - y)^2)

primUlt :: [a] -> (a, a)
primUlt l = (head l, last l)

multiplo :: Int -> Int -> Bool
multiplo x y = mod x y == 0 

truncaImpar :: [a] -> [a]
truncaImpar l = if mod (length l) 2 /= 0 then tail l
                else l

max2 :: Int -> Int -> Int
max2 x y = if x > y then x else y

max2b :: Int -> Int -> Int
max2b x y | x > y = x
          | otherwise = y

max3 :: Int -> Int -> Int -> Int
max3 x y z = max2 (max2 x y) z

nRaizes :: Double -> Double -> Double -> Double
nRaizes a b c = (-(b) + sqrt (b ^ 2 - (4 * a * c))) / 2 * a

-- raizes :: Double -> Double -> Double -> [Double] --

type Hora = (Int, Int)
meiaNoiteEUmQuarto :: Hora
meiaNoiteEUmQuarto = (0, 15)
duasMenosUmQuarto :: Hora
duasMenosUmQuarto = (13, 45)

horaValida :: Hora -> Bool
horaValida (h, m) = h > 0 && h < 24 && m >= 0 && m < 60

-- True -> 1° é antes do que a segunda
comparaHora :: Hora -> Hora -> Bool
comparaHora (h, m) (h2, m2) =  h > h2 || h == h2 && m > m2

horaParaMinutos :: Hora -> Int
horaParaMinutos (h, m) = h * 60 + m

minutoParaHora :: Int -> Hora
minutoParaHora m = (div m 60, mod m 60)

diferencaHoras :: Hora -> Hora -> Int
diferencaHoras h1 h2 = abs((horaParaMinutos h1) - (horaParaMinutos h2))

adicionaMinutos :: Int -> Hora -> Hora
adicionaMinutos m h = minutoParaHora (m + horaParaMinutos h)

-- EX04

-- FIM EX04

-- ex05

data Semaforo = Verde
              | Amarelo
              | Vermelho
              deriving (Show, Eq)

next :: Semaforo -> Semaforo
next Verde = Amarelo
next Amarelo = Vermelho
next Vermelho = Verde

stop :: Semaforo -> Bool
stop Vermelho = True
stop Amarelo = False
stop Verde = False

safe :: Semaforo -> Semaforo -> Bool
safe _ Vermelho = True
safe Vermelho _ = True
safe _ _ = False

-- fim 05

-- ex 06

data Ponto = Cartesiano Double Double
           | Polar Double Double
           deriving(Show, Eq)

data Figura = Circulo Ponto Double
            | Retangulo Ponto Ponto
            | Triangulo Ponto Ponto Ponto
            deriving(Show, Eq)

circ :: Figura
circ = Circulo(Cartesiano 0 0) 2.3

rect :: Figura
rect = Retangulo (Cartesiano 0 0) (Cartesiano 2 2)

poligono :: Figura -> Bool
poligono (Circulo h r) = False
poligono _ = True


vertices :: Figura -> [Ponto]
vertices (Circulo p r) = []
vertices (Triangulo v1 v2 v3) = [v1, v2, v3]
vertices (Retangulo(Cartesiano a b) (Cartesiano x y)) = [Cartesiano a b 
                                                        ,Cartesiano a y
                                                        ,Cartesiano x y
                                                        ,Cartesiano x b]

dist' :: Ponto -> Ponto -> Double
dist' (Cartesiano x1 y1) (Cartesiano x2 y2) = sqrt ((x2 - x1)^2 + (y2 - y1)^2)

--fim 06


area :: Figura -> Double
area (Triangulo p1 p2 p3) =
    let a = dist' p1 p2
        b = dist' p2 p3
        c = dist' p3 p1
        s = (a+b+c) / 2 -- semi-perimetro
    in sqrt (s*(s-a)*(s-b)*(s-c)) -- formula de Heron
area (Circulo _ r) = pi * r ^ 2
area (Retangulo (Cartesiano a b) (Cartesiano x y)) = 
    let v1 = Cartesiano a b
        v2 = Cartesiano a y
        v3 = Cartesiano x y
        a2 = dist' v1 v2
        l = dist' v2 v3
    in a2 * l

-- fim 07

-- ex 08

isLower :: Char -> Bool
isLower c = ord c >= 97 && ord c <= 122

isDigit :: Char -> Bool
isDigit n = ord n >= 48 && ord n <= 57


toUpper :: Char -> Char
toUpper c = chr((ord c) - 32)

intToDigit :: Int -> Char
intToDigit d = chr d

digitToInt :: Char -> Int
digitToInt c = ord c