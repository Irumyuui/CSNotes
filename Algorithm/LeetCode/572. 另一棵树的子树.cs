public class Solution
{
    public bool IsSubtree(TreeNode root, TreeNode subRoot)
    {
        static bool Dfs(TreeNode? node, TreeNode? subNode) => (node, subNode) switch
        {
            (not null, not null) => node.val == subNode.val && Dfs(node.left, subNode.left) && Dfs(node.right, subNode.right),
            (null, null) => true,
            _ => false,
        };

        var q = new Queue<TreeNode>(2000);
        q.Enqueue(root);
        while (q.Count > 0)
        {
            var node = q.Dequeue();
            if (Dfs(node, subRoot)) return true;
            if (node.left is not null) q.Enqueue(node.left);
            if (node.right is not null) q.Enqueue(node.right);
        }

        return false;
    }
}