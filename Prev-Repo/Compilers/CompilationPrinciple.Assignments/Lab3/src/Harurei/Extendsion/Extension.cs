using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace Hakurei.Extension;

public static class HashSetExtension
{
    public static bool HasIntersection<T>(this HashSet<T> self, HashSet<T>? that)
    {
        if (that is null)
            return false;

        foreach (var item in self)
            if (that.Contains(item))
            {
                return true;
            }

        return false;
    }
}
