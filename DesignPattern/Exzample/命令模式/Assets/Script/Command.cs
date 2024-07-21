using UnityEngine;

public abstract class Command
{
    public abstract void Execute(GameObject go);
    public abstract void Undo();
}
