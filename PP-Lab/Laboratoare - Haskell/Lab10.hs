-- 10.1.1
data MatchResult = Win | Loss | Draw
  deriving (Show, Eq)

data Player = Player {
  name :: String,
  elo :: Float,
  matchHistory :: [MatchResult]
} deriving (Show, Eq)

data Tree a = Node a (Tree a) (Tree a) | Leaf a
  deriving (Show)

-- 10.1.2
instance Show MatchResult where
    show Win = "Win"
    show Loss = "Loss"
    show Draw = "Draw"

instance Show Player where
    show (Player name elo matchHistory) =
        "Player{name=" ++ name ++ ", elo=" ++ show elo ++ ", matchHistory=" ++ show matchHistory ++ "}"

-- 10.1.3
addResult :: MatchResult -> Player -> Player
addResult result player = player { matchHistory = result : matchHistory player }

-- 10.1.4
points :: MatchResult -> Float
points Win = 1.0
points Loss = 0.0
points Draw = 0.5

-- 10.1.5
score :: Player -> Float
score player = sum (map points (matchHistory player))

-- 10.1.6
instance Ord Player where
    (<=) p1 p2 = score p1 <= score p2

-- 10.1.7
playGame :: Player -> Player -> (Player, Player)
playGame p1 p2
  | elo p1 > elo p2 = (addResult Win p1, addResult Loss p2)
  | elo p1 < elo p2 = (addResult Loss p1, addResult Win p2)
  | otherwise = (addResult Draw p1, addResult Draw p2)

playGameWithWinner :: Player -> Player -> (Player, (Player, Player))
playGameWithWinner p1 p2
  | elo p1 >= elo p2 = (p1, (addResult Win p1, addResult Loss p2))
  | otherwise = (p2, (addResult Loss p1, addResult Win p2))

-- 10.1.8
playAll :: Player -> [Player] -> (Player, [Player])
playAll player [] = (player, [])
playAll player (p:ps) =
    let (updatedPlayer, updatedOpponent) = playGame player p
        (finalPlayer, updatedRest) = playAll updatedPlayer ps
    in (finalPlayer, updatedOpponent : updatedRest)

-- 10.1.9
playGroup :: [Player] -> [Player]
playGroup [] = []
playGroup (p:ps) =
    let (updatedPlayer, updatedOpponents) = playAll p ps
    in updatedPlayer : playGroup updatedOpponents

selectPlayers :: [Player] -> Int -> ([Player], [Player])
selectPlayers players m = splitAt m (reverse $ sort players)

playGroups :: [[Player]] -> Int -> ([Player], [Player])
playGroups groups m =
    let playedGroups = map playGroup groups
        selectedPlayers = concatMap (`selectPlayers` m) playedGroups
    in (fst $ unzip selectedPlayers, snd $ unzip selectedPlayers)

-- 10.1.10
playElimination :: [Player] -> Tree Player
playElimination [p] = Leaf p
playElimination players =
    let paired = pairUp players
        matchResults = map (uncurry playGameWithWinner) paired
        winners = map fst matchResults
        trees = map (uncurry Node) (zip winners (map snd matchResults))
    in playElimination (map root trees)
  where
    pairUp [] = []
    pairUp (x:y:xs) = (x, y) : pairUp xs
    root (Node p _ _) = p
    root (Leaf p) = p

-- 10.1.11
eliminationResults :: Tree Player -> [Player]
eliminationResults (Leaf p) = [p]
eliminationResults (Node p l r) = p : (eliminationResults l ++ eliminationResults r)

-- 10.1.12
runTournament :: [Player] -> Int -> Int -> [Player]
runTournament players n m =
    let groups = splitIntoGroups m players
        (selected, _) = playGroups groups n
        eliminationTree = playElimination selected
    in eliminationResults eliminationTree
  where
    splitIntoGroups _ [] = []
    splitIntoGroups size lst = take size lst : splitIntoGroups size (drop size lst)

players :: [Player]
players = [
    Player {name = "Jill Todd", elo = 69.32222, matchHistory = []},
    Player {name = "Cara Wong", elo = 68.451675, matchHistory = []},
    Player {name = "Travis Dunlap", elo = 49.667397, matchHistory = []},
    Player {name = "Adam Mills", elo = 65.36233, matchHistory = []},
    Player {name = "Josephine Barton", elo = 14.974056, matchHistory = []},
    Player {name = "Erica Mendez", elo = 27.466717, matchHistory = []},
    Player {name = "Derrick Simmons", elo = 11.790775, matchHistory = []},
    Player {name = "Paula Hatch", elo = 80.039635, matchHistory = []},
    Player {name = "Patricia Powers", elo = 61.08892, matchHistory = []},
    Player {name = "Luke Neal", elo = 65.933014, matchHistory = []},
    Player {name = "Jackie Stephenson", elo = 86.00121, matchHistory = []},
    Player {name = "Bernice Nixon", elo = 2.8692048, matchHistory = []},
    Player {name = "Brent Cobb", elo = 39.80139, matchHistory = []},
    Player {name = "Bobbie Sanderson", elo = 81.07552, matchHistory = []},
    Player {name = "Zachary Conner", elo = 63.88572, matchHistory = []},
    Player {name = "Shawn Landry", elo = 7.68082, matchHistory = []},
    Player {name = "Mabel Gentry", elo = 88.13421, matchHistory = []},
    Player {name = "Enrique Ali", elo = 9.568502, matchHistory = []},
    Player {name = "Clara McLaughlin", elo = 60.83427, matchHistory = []},
    Player {name = "Jacqueline Connell", elo = 60.091232, matchHistory = []},
    Player {name = "Jared Morgan", elo = 49.84152, matchHistory = []},
    Player {name = "Lorraine Castaneda", elo = 34.701054, matchHistory = []},
    Player {name = "Robin Hurd", elo = 78.33226, matchHistory = []},
    Player {name = "Vince Dunlap", elo = 63.634525, matchHistory = []},
    Player {name = "Elaine Winter", elo = 34.86934, matchHistory = []},
    Player {name = "Bennie Godfrey", elo = 73.81608, matchHistory = []},
    Player {name = "Gale Britton", elo = 16.05768, matchHistory = []},
    Player {name = "Jeanne Mathis", elo = 34.603416, matchHistory = []},
    Player {name = "Aida Greenwood", elo = 8.308169, matchHistory = []},
    Player {name = "Christian Witt", elo = 80.397675, matchHistory = []},
    Player {name = "Cecelia Dyer", elo = 80.657974, matchHistory = []},
    Player {name = "Edwin Gallagher", elo = 14.976497, matchHistory = []}]

main :: IO ()
main = print $ runTournament players 2 4
