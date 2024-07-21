using System.Runtime.InteropServices;
using UnityEngine;

public class CubeMove : MonoBehaviour
{
    private readonly CubeMoveForwardCommand _forwardCommand = new();
    private readonly CubeMoveBackCommand _backCommand = new();
    private readonly CubeMoveLeftCommand _leftCommand = new();
    private readonly CubeMoveRightCommand _rightCommand = new();

    private GameObject _cube;
    private KeyCode[] _keyCodes;

    public float _moveSpeed = 0.2f;

    void Start()
    {
        _cube = GameObject.Find("Cube");
        _keyCodes = new[] {
            KeyCode.W,
            KeyCode.S,
            KeyCode.A,
            KeyCode.D,
            KeyCode.R,
        };

        _forwardCommand.MoveSpeed = _moveSpeed;
        _backCommand.MoveSpeed = _moveSpeed;
        _leftCommand.MoveSpeed = _moveSpeed;
        _rightCommand.MoveSpeed = _moveSpeed;
    }

    void Update()
    {
        CubeInputHandler();
    }

    private void CubeInputHandler()
    {
        if (Input.GetKey(_keyCodes[4]))
        {
            StartCoroutine(CommandManager.Instance.UndoStart());
            //CommandManager.Instance.Undo();
        }

        if (Input.GetKey(_keyCodes[0]))
        {
            _forwardCommand.Execute(_cube);
            CommandManager.Instance.AddCommand(_forwardCommand);
        }

        if (Input.GetKey(_keyCodes[1]))
        {
            _backCommand.Execute(_cube);
            CommandManager.Instance.AddCommand(_backCommand);
        }

        if (Input.GetKey(_keyCodes[2]))
        {
            _leftCommand.Execute(_cube);
            CommandManager.Instance.AddCommand(_leftCommand);
        }

        if (Input.GetKey(_keyCodes[3]))
        {
            _rightCommand.Execute(_cube);
            CommandManager.Instance.AddCommand(_rightCommand);
        }
    }
}