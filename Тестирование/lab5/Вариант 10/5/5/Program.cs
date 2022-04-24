using _5;

int cellsToAttack = QueenAttack.QueenAttackCells();
if (cellsToAttack != -1)
{
    Console.WriteLine("Количество клеток для атаки: " + cellsToAttack);
}
else
{
    Console.WriteLine("Вы ввели некорректные данные");
}
return 1;