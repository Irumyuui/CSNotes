int Dow(int year, int month, int day)
{
    ReadOnlySpan<int> days = [0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4];
    year -= month < 3 ? 1 : 0;
    return (year + year / 4 - year / 100 + year / 400 + days[month - 1] + day) % 7;
}