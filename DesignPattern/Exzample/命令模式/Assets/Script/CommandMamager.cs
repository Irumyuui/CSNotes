using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CommandManager : MonoSingleton<CommandManager>
{
    private readonly List<Command> _commandList = new();

    public void Start()
    {
        Debug.Log("Start");
    }

    protected override void Awake()
    {
        Debug.Log("Awake");
        base.Awake();
    }

    public void AddCommand(Command command)
    {
        _commandList.Add(command);
        Debug.Log(command.GetType().Name);
        Debug.Log(_commandList.Count);
    }

    public void Undo()
    {
        if (_commandList.Count > 0)
        {
            _commandList[^1]?.Undo();
            _commandList.RemoveAt(_commandList.Count - 1);
        }
    }

    public IEnumerator UndoStart()
    {
        while (_commandList.Count > 0)
        {
            yield return new WaitForSeconds(0.2f);
            Undo();
        }
    }
}
