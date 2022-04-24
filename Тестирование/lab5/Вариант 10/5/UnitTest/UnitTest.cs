using Microsoft.VisualStudio.TestTools.UnitTesting;
using Position = _5.Position;
using QueenAttack = _5.QueenAttack;

namespace UnitTest
{
    [TestClass]
    public class UnitTestQueenAttack
    {
        [TestMethod]
        public void FirstTest()
        {
            int n = 4;
            Position queen = new(4, 4);
            Position[] barriers = System.Array.Empty<Position>();
            int countCells = QueenAttack.CellSearchForAttack(n, queen, barriers);
            Assert.IsTrue(countCells == 9);
        }

        [TestMethod]
        public void SecondTest()
        {
            int n = 5;
            Position queen = new(4, 3);
            Position[] barriers = new Position[3];
            barriers[0] = new(5, 5);
            barriers[1] = new(4, 2);
            barriers[2] = new(2, 3);
            int countCells = QueenAttack.CellSearchForAttack(n, queen, barriers);
            Assert.IsTrue(countCells == 10);
        }

        [TestMethod]
        public void ThirdTest()
        {
            int n = 1;
            Position queen = new(1, 1);
            Position[] barriers = System.Array.Empty<Position>();
            int countCells = QueenAttack.CellSearchForAttack(n, queen, barriers);
            Assert.IsTrue(countCells == 0);
        }
    }
}