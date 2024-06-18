import scala.annotation.targetName
// 6.1.1
extension (s: String) {
  @targetName("MOVE_LEFT")
  def <<(n: Int): String = s.drop(n)
  @targetName("MOVE_RIGHT")
  def >>(n: Int): String = s.take(s.length - n)
}
println("odersky" << 2)
println("odersky" >> 2)

// 6.1.2
extension (s: String) {
  @targetName("SHIFT_LEFT")
  def <<<(n: Int): String = {
    val len = s.length
    s.drop(n % len) + s.take(n % len)
  }
  @targetName("SHIFT_RIGHT")
  def >>>(n: Int): String = {
    val len = s.length
    s.takeRight(n % len) + s.dropRight(n % len)
  }
}
println("odersky" <<< 2)
println("odersky" >>> 2)

// 6.1.3
extension (s1: String) {
  @targetName("REMOVAL")
  def -(s2: String): String = s1.replace(s2, "")
}
println("Implement the ''-'' operator between two strings that removes occurrences of the second string from the first one:" - "th")

// 6.1.4
extension (s: String) {
  @targetName("SWITCH")
  def unary_~ : String = s.map {
    case c if c.isUpper => c.toLower
    case c if c.isLower => c.toUpper
    case c => c
  }
}
println(~"xXx1337ScAlAcOdErxXx")

// 6.1.5
extension (s1: String) {
  @targetName("STRCMP")
  def <=>(s2: String): Int = {
    val result = s1.compare(s2)
    if (result < 0) -1 else if (result > 0) 1 else 0
  }
}
println("haskell" <=> "java")
println("scala" <=> "java")
println("scala" <=> "scala")

// 6.1.6
extension (s: String) {
  @targetName("SPLIT")
  def /(n: Int): List[String] = s.grouped(n).toList
}
println("scalable language" / 3)

// 6.2
trait Player {
  override def toString: String
}
case object One extends Player {
  override def toString: String = "X"
}
case object Two extends Player {
  override def toString: String = "0"
}
case object Empty extends Player {
  override def toString: String = "."
}

type Line = List[Player]
type BoardList = List[Line]

// 6.2.4
case class Board(b: BoardList) {
  override def toString: String = b.map(_.mkString).mkString("\n")
}

// 6.2.1
def makeBoard(s: String): Board = {
  def toPos(c: Char): Player = c match {
    case 'X' => One
    case '0' => Two
    case _ => Empty
  }
  val boardList: BoardList = s.split("\n").toList.map(_.toList.map(toPos))
  Board(boardList)
}
val boardString = "X...0\n0X.0.\n..X0.\n...X.\n.0..X"
val board = makeBoard(boardString)
println(board)

// 6.2.2
def isFree(board: Board, x: Int, y: Int): Boolean = board.b(x)(y) == Empty
println(isFree(board, 0, 1))
println(isFree(board, 0, 0))

// 6.2.3
def complement(p: Player): Player = p match {
  case One => Two
  case Two => One
  case Empty => Empty
}
println(complement(One))
println(complement(Two))

// 6.2.5
def getColumns(board: Board): Board = {
  val transposed = board.b.transpose
  Board(transposed)
}
println(getColumns(board))

// 6.2.6
def getFstDiag(board: Board): Line = {
  (for (i <- board.b.indices) yield board.b(i)(i)).toList
}

def getSndDiag(board: Board): Line = {
  (for (i <- board.b.indices) yield board.b(i)(board.b.length - 1 - i)).toList
}
println(getFstDiag(board))
println(getSndDiag(board))

// 6.2.7
def getAboveFstDiag(board: Board): List[Line] = {
  (for (k <- 1 until board.b.length) yield (for (i <- 0 until board.b.length - k) yield board.b(i)(i + k)).toList).toList
}

def getBelowFstDiag(board: Board): List[Line] = {
  (for (k <- 1 until board.b.length) yield (for (i <- k until board.b.length) yield board.b(i)(i - k)).toList).toList
}

def getAboveSndDiag(board: Board): List[Line] = {
  (for (k <- 1 until board.b.length) yield (for (i <- 0 until board.b.length - k) yield board.b(i)(board.b.length - 1 - (i + k))).toList).toList
}

def getBelowSndDiag(board: Board): List[Line] = {
  (for (k <- 1 until board.b.length) yield (for (i <- k until board.b.length) yield board.b(i)(board.b.length - 1 - (i - k))).toList).toList
}
println(getAboveFstDiag(board))
println(getBelowFstDiag(board))
println(getAboveSndDiag(board))
println(getBelowSndDiag(board))

// 6.2.8
def winner(board: Board, p: Player): Boolean = {
  def checkLine(line: Line): Boolean = line.sliding(5).exists(_.forall(_ == p))
  val rows = board.b
  val cols = getColumns(board).b
  val diags = List(getFstDiag(board), getSndDiag(board)) ++ getAboveFstDiag(board) ++ getBelowFstDiag(board) ++ getAboveSndDiag(board) ++ getBelowSndDiag(board)

  (rows ++ cols ++ diags).exists(checkLine)
}
println(winner(board, One))
println(winner(board, Two))

// 6.2.9
def update(board: Board, p: Player)(ln: Int, col: Int): Board = {
  val updatedLine = board.b(ln).updated(col, p)
  val updatedBoard = board.b.updated(ln, updatedLine)
  Board(updatedBoard)
}
val newBoard = update(board, One)(2, 2)
println(newBoard)

// 6.2.10
def next(board: Board, p: Player): List[Board] = {
  for {
    i <- board.b.indices
    j <- board.b(i).indices
    if isFree(board, i, j)
  } yield update(board, p)(i, j)
}.toList
val nextMoves = next(board, One)
nextMoves.foreach(println)
