using UnityEngine;

public class CubeMoveForwardCommand : Command
{
    public float MoveSpeed { get; set; }

    private GameObject _cube;

    public override void Execute(GameObject go)
    {
        _cube = go;
        _cube.transform.Translate(Vector3.forward * MoveSpeed);
    }

    public override void Undo()
    {
        _cube?.transform?.Translate(Vector3.back * MoveSpeed);
    }
}

public class CubeMoveLeftCommand : Command
{
    public float MoveSpeed { get; set; }

    private GameObject _cube;

    public override void Execute(GameObject go)
    {
        _cube = go;
        _cube.transform.Translate(Vector3.left * MoveSpeed);
    }

    public override void Undo()
    {
        _cube?.transform?.Translate(Vector3.right * MoveSpeed);
    }
}

public class CubeMoveRightCommand : Command
{
    public float MoveSpeed { get; set; }

    private GameObject _cube;

    public override void Execute(GameObject go)
    {
        _cube = go;
        _cube.transform.Translate(Vector3.right * MoveSpeed);
    }

    public override void Undo()
    {
        _cube?.transform?.Translate(Vector3.left * MoveSpeed);
    }
}

public class CubeMoveBackCommand : Command
{
    public float MoveSpeed { get; set; }

    private GameObject _cube;

    public override void Execute(GameObject go)
    {
        _cube = go;
        _cube.transform.Translate(Vector3.back * MoveSpeed);
    }

    public override void Undo()
    {
        _cube?.transform?.Translate(Vector3.forward * MoveSpeed);
    }
}