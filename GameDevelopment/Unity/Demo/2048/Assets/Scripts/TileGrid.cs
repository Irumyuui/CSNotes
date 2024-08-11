using Unity.Mathematics;
using UnityEngine;

public class TileGrid : MonoBehaviour
{
    public TileRow[] rows { get; private set; }
    public TileCell[] cells { get; private set; }

    public int Size => cells.Length;
    public int Height => rows.Length;
    public int Width => Size / Height;

    private void Awake()
    {
        rows = GetComponentsInChildren<TileRow>();
        cells = GetComponentsInChildren<TileCell>();
    }

    private void Start()
    {
        for (int y = 0; y < rows.Length; y++)
        {
            for (int x = 0; x < rows[y].cells.Length; x++)
            {
                rows[y].cells[x].coordinates = new Vector2Int(x, y);
            }
        }
    }

    public TileCell GetRandomEmptyCell()
    {
        int index = UnityEngine.Random.Range(0, cells.Length);
        int startIndex = index;

        while (cells[index].Occupied)
        {
            index = (index + 1) % cells.Length;
            if (startIndex == index)
            {
                return null;
            }
        }

        return cells[index];
    }

    public TileCell GetCell(int x, int y) =>
        x >= 0 && x < Width && y >= 0 && y < Height ? rows[y].cells[x] : null;

    public TileCell GetCell(Vector2Int coordinates) =>
        GetCell(coordinates.x, coordinates.y);

    public TileCell GetAdjacentCell(TileCell cell, Vector2Int direction)
    {
        var coordinates = cell.coordinates;
        coordinates.x += direction.x;
        coordinates.y -= direction.y;
        return GetCell(coordinates);
    }
}
