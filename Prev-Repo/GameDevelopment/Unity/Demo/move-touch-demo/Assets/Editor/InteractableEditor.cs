using UnityEditor;

[CustomEditor(typeof(Interactable), true)]
public class InteractableEditor : Editor
{
    public override void OnInspectorGUI()
    {
        var interactable = (Interactable)target;
        if (target.GetType() == typeof(EventOnlyInteractable))
        {
            interactable.promptMessage = EditorGUILayout.TextField("Prompt Message", interactable.promptMessage);
            EditorGUILayout.HelpBox("EventOnlyInteract can only use UnityEvents.", MessageType.Info);

            if (interactable.GetComponent<InteractionEvent>() == null)
            {
                interactable.useEvents = true;
                interactable.gameObject.AddComponent<InteractionEvent>();
            }
            
            return;
        }
        
        var interactableEvent = interactable.GetComponent<InteractionEvent>();
        base.OnInspectorGUI();
        if (interactable.useEvents)
        {
            if (interactableEvent == null)
            {
                interactable.gameObject.AddComponent<InteractionEvent>();
            }
        }
        else
        {
            if (interactableEvent != null)
            {
                DestroyImmediate(interactableEvent);
            }
        }
    }
}
