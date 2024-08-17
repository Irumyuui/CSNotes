using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class PlayrUI : MonoBehaviour
{
    [SerializeField]
    private TextMeshProUGUI promptText;

    public void UpdateText(string promptMessage)
    {
        promptText.text = promptMessage;
    }
}
