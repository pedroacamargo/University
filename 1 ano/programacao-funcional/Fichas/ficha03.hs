--1)

-- anotações --
{-
    fst -> couple first element
    snd -> couple second element
    tail -> array last element
-}

isValid :: Hora -> Bool
isValid (H x y) | x >= 0 && x < 24 && y >= 0 && y < 60 = True
                 | otherwise = False

isGreater :: Hora -> Hora -> Bool
isGreater (H h1 m1) (H h2 m2) | h1 > h2 = False
                              | h1 < h2 = True
                              | h1 == h2 && m1 > m2 = False
                              | otherwise = True

convertToMinutes :: Hora -> Int
convertToMinutes(H h m) = (h * 60) + m

convertToHours :: Int -> Hora
convertToHours m = H (div m 60) (mod m 60)

diffBetween :: Hora -> Hora -> Int
diffBetween (H h1 m1) (H h2 m2) = abs (convertToMinutes (H h1 m1) - convertToMinutes (H h2 m2))

addMinutes :: Int -> Hora -> Hora
addMinutes x (H h1 m1) = convertToHours (convertToMinutes (H h1 m1) + x)

viagem :: Viagem
viagem = [(H 9 30, H 10 25), (H 11 20, H 12 45), (H 13 30, H 14 45)]
etapa :: Etapa
etapa = (H 13 40, H 15 0)
etapaInvalida :: Etapa
etapaInvalida = (H 70 0, H 40 9)

data Hora = H Int Int
        deriving Show

type Etapa = (Hora,Hora)
type Viagem = [Etapa]


--a)
isStageValid :: Etapa -> Bool
isStageValid (H h1 m1, H h2 m2) | h1 > h2 = False
                                | h1 == h2 && m1 > m2 = False
                                | otherwise = isValid (H h1 m1) && isValid (H h2 m2)

verificaEtapa :: Etapa -> Bool
verificaEtapa (h1,h2) = isGreater h1 h2

--b)
isTravelValid :: Viagem -> Bool
isTravelValid [] = True
isTravelValid [(e1,e2)] = isStageValid (e1,e2)
isTravelValid ((H h1 m1,H h2 m2):(H h3 m3,H h4 m4):t) = isStageValid (H h1 m1,H m2 h2)
                                                     && isStageValid (H h2 m2,H h3 m3) 
                                                     && isTravelValid ((H h3 m3,H h4 m4):t)

valiViagem :: Viagem -> Bool
valiViagem [] = True
valiViagem [x] = verificaEtapa x
valiViagem (e1:e2:t) = verificaEtapa e1 && verificaEtapa (snd e1, fst e2) && valiViagem (e2:t) 

--c) obra de arte
simpTravel :: Viagem -> Etapa
simpTravel ((H h1 m1, H h2 m2):t) = (H h1 m1, snd (last t))

--d)
travelTime :: Viagem -> Int
travelTime [] = 0
travelTime ((h1,h2):t) = diffBetween h1 h2 + travelTime t

--e)
waitTime :: Viagem -> Int
waitTime [] = 0
waitTime [(h1,h2)] = 0
waitTime ((h1,h2):(h3,h4):t) = diffBetween h2 h3 + waitTime ((h3,h4):t)

--f)
totalTravelTime :: Viagem -> Int
totalTravelTime v = travelTime v + waitTime v

-------------------------------------------------------------------------------------------------------------------
--2)
data Ponto = Cartesiano Double Double | Polar Double Double -- Polar: Origin distance / angle x axis
            deriving (Show,Eq)

data Figura = Circulo Ponto Double
            | Rectangulo Ponto Ponto
            | Triangulo Ponto Ponto Ponto
            deriving (Show,Eq)

type Poligonal = [Ponto]

ponto1 :: Ponto
ponto1 = Cartesiano (-1) 0
ponto2 :: Ponto
ponto2 = Polar 1 pi



posx :: Ponto -> Double
posx (Cartesiano x y) = x

posy :: Ponto -> Double
posy (Cartesiano x y) = y

raio :: Ponto -> Double
raio (Cartesiano x y) = sqrt (x^2 + y^2)

angulo :: Ponto -> Double
angulo (Cartesiano x y) | x == 0 && y == 0 = 0
                        | x == 0 && y > 0 = pi/2
                        | x == 0 && y < 0 = -(pi/2)
                        | x > 0 && y == 0 = 0
                        | x < 0 && y == 0 = pi
                        | x > 0 = atan (y/x)
                        | x < 0 && y < 0 = atan(y/x) - pi
                        | x < 0 && y >= 0 = atan(y/x) + pi

dist' :: Ponto -> Ponto -> Double
dist' (Cartesiano x1 y1) (Cartesiano x2 y2) = sqrt (((x1 - x2) ^ 2) + (y1 - y2) ^ 2)

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

--a)
lengthPoligonal :: Poligonal -> Double
lengthPoligonal (p1:p2:t) = dist' p1 p2 + lengthPoligonal (p2:t)
lengthPoligonal [] = 0

--b)
closedPoligonal :: Poligonal -> Bool
closedPoligonal l = if (dist' (head l) (last l)) == 0 then True else False

--c)
triangula :: Poligonal -> [Figura]
triangula (p1:p2:p3:t) = (Triangulo p1 p2 p3) : triangula t
triangula _ = []

--d)
areaPoligonal :: Poligonal -> Double
areaPoligonal l = aux (triangula l)
                  where aux :: [Figura] -> Double
                        aux [] = 0
                        aux (x:xs) = area  x + aux xs

--e) deu trabalho mas funciona
mover :: Poligonal -> Ponto -> Poligonal
mover ((Cartesiano x1 y1):t) (Cartesiano x2 y2) = aux' ((Cartesiano x1 y1):t) (Cartesiano x2 y2) x2 y2
                                        where aux' :: Poligonal -> Ponto -> Double -> Double -> Poligonal
                                              aux' a (Cartesiano x2 y2) x3 y3 = (Cartesiano x2 y2) : aux'' a x3 y3 
                                              aux' [] _ _ _ = []
mover p _ = p

aux'' :: Poligonal -> Double -> Double -> Poligonal
aux'' ((Cartesiano x1 y1):t) x2 y2 = (Cartesiano (x1+x2) (y1+y2)) : aux'' t x2 y2
aux'' [] _ _ = []

polinomioExemplo :: Poligonal
polinomioExemplo = [(Cartesiano 1 1),(Cartesiano 2 2),(Cartesiano 3 3)]

--f)
zoom :: Double -> Poligonal -> Poligonal
zoom e [] = []
zoom e ((Cartesiano x y):t) = (Cartesiano (e*x) (e*y)) : zoom e t

-------------------------------------------------------------------------------------------------------------------
--3)
data Contacto = Casa Integer | Trab Integer | Tlm Integer | Email String deriving Show

type Nome = String
type Agenda = [(Nome, [Contacto])]

listadecontatos :: [Contacto]
listadecontatos = [Casa 939944323, Trab 221312222, Tlm 2225000985, Email "pedroaugennes@gmail.com", Tlm 1239597733]


--a)
acrescEmail :: Nome -> String -> Agenda -> Agenda
acrescEmail nome email agenda = agenda ++ [(nome, [Email email])]

--b) You can see the definitions of map (\x ->) at University/1 ano/programacao-funcional/haskell-functions/map.hs
verEmails :: Nome -> Agenda -> Maybe [String]
verEmails nome [(nom, cont)] = if nome == nom then Just (map (\x -> case x of Email e -> e) cont) else Nothing
verEmails nome ((nom,cont): agenda) = if nome == nom then verEmails nome [(nom,cont)] else verEmails nome agenda

--c)
consTelefs :: [Contacto] -> [Integer]
consTelefs (h:t) = case h of
                Tlm a ->  a : consTelefs t
                Casa b -> b : consTelefs t
                Trab c -> c : consTelefs t
                _ -> consTelefs t
consTelefs [] = []

--d) dado um nome e agenda, retorna o numero de telefone da casa (caso exista)
casa :: Nome -> Agenda -> Maybe Integer
casa nome [(name, (contato:t))] = if nome == name then case contato of
                                                    Casa x -> Just x 
                                                    otherwise -> casa nome [(name,t)]
                                                  else Nothing
casa nome ((name, contato):t2) = if nome == name then casa nome [(name, contato)] else casa nome t2

-------------------------------------------------------------------------------------------------------------------
--4)
type Dia = Int
type Mes = Int
type Ano = Int
type Nome' = String

data Data = D Dia Mes Ano deriving Show

type TabDN = [(Nome',Data)]

listaDeAmigos :: TabDN
listaDeAmigos = [("Pedro Augusto Camargo", D 25 3 2004), ("Costanzo Bruno Annichini", D 7 1 2002)]

--a)
procura :: Nome' -> TabDN -> Maybe Data
procura n [] = Nothing
procura n ((nome,date):t) = if n == nome then Just date else procura n t

--b)
idade :: Data -> Nome' -> TabDN -> Maybe Int
idade _ _ [] = Nothing
idade (D d1 m1 a1) nome ((nom,(D d2 m2 a2 )):t) | nome /= nom = idade (D d1 m1 a1) nome t
                                                  | a1 < a2 || (a1 == a2 && m1 < m2) = Just 0
                                                  | m1 < m2 || (m1 == m2 && d1 < d2) = Just (a1-a2-1)
                                                  | otherwise = Just (a1-a2)

--c)
anterior :: Data -> Data -> Bool
anterior (D d1 m1 a1) (D d2 m2 a2) | a1 < a2 = True
                                   | a1 == a2 && m1 < m2 = True
                                   | a1 == a2 && m1 == m2 && d1 < d2 = True
                                   | otherwise = False

--d)
ordena :: TabDN -> TabDN
ordena [] = []
ordena ((name,date):t) = aux''' [(name,date)] (ordena t)
                    where aux''' :: TabDN -> TabDN -> TabDN
                          aux''' [(nom,dat)] [] = [(nom,dat)]
                          aux''' [(nom,dat)] ((n,d):t) = if anterior dat d == False then (n,d) : aux''' [(nom,dat)] t else (nom,dat) : aux''' [(n,d)] t  

--e) apresenta o nome e idade das pessoas, numa dada data, por ordem crescente da idade das pessoas
porIdade:: Data -> TabDN -> [(Nome,Int)]
porIdade _ [] = []
porIdade (D d1 m1 a1) ((nome,(D d2 m2 a2)):t) = auxx nome (a1 - a2) t (D d1 m1 a1)
                                            where auxx :: Nome' -> Int -> TabDN -> Data -> [(Nome,Int)]
                                                  auxx n i [] _ = [(n,i)]
                                                  auxx n i ((nome,(D d1 m1 a1)):t) (D d2 m2 a2) | (a2 - a1) < i = (nome, a2-a1) : auxx n i t (D d2 m2 a2)
                                                                                                | otherwise = (n,i) : auxx nome (a2 - a1) t (D d2 m2 a2)

-------------------------------------------------------------------------------------------------------------------
--5)

data Movimento = Credito Float | Debito Float 
                deriving Show

data Data' = D' Int Int Int 
            deriving Show

data Extracto = Ext Float [(Data', String, Movimento)]
                deriving Show

--a)
extValor :: Extracto -> Float -> [Movimento]
extValor (Ext x []) _ = []
extValor (Ext x ((_,_,Debito y):t)) z = if z > y then (Debito y) : extValor (Ext x t) z else extValor (Ext x t) z
extValor (Ext x ((_,_,Credito y):t)) z = if z > y then (Credito y) : extValor (Ext x t) z else extValor (Ext x t) z

--b)
filtro :: Extracto -> [String] -> [(Data',Movimento)]
filtro (Ext x []) s = []
filtro (Ext x ((d,s,m):t)) s2 = if elem s s2 then (d,m) : filtro (Ext x t) s2 else filtro (Ext x t) s2

--c)
creDeb :: Extracto -> (Float,Float)
creDeb (Ext x lista) = (cred lista, deb lista)
                    where cred :: [(Data',String,Movimento)] -> Float
                          cred [] = 0
                          cred ((d,s,Credito x):t) = x + cred t
                          cred ((d,s,Debito x):t) = cred t
                          deb :: [(Data',String,Movimento)] -> Float
                          deb [] = 0
                          deb ((d,s,Credito x):t) = deb t
                          deb ((d,s,Debito x):t) = x + deb t

--d)
saldo :: Extracto -> Float
saldo (Ext si resto) = si + d - c
                       where (d,c) = creDeb (Ext si resto)