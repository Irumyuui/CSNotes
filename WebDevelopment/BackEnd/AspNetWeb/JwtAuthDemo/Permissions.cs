using Microsoft.AspNetCore.Authorization;

namespace JwtAuthDemo;

public static class Permissions
{
    public const string User = "User";
    public const string UserCreate = $"{User}.Create";
    public const string UserDelete = $"{User}.Delete";
    public const string UserUpdate = $"{User}.Update";
}

public class PermissionAuthorizationRequirement : IAuthorizationRequirement
{
    public PermissionAuthorizationRequirement(string name) => Name = name;

    public string Name { get; set; }
}

public class PermissionAuthorizationHandler : AuthorizationHandler<PermissionAuthorizationRequirement>
{
    protected override Task HandleRequirementAsync(AuthorizationHandlerContext context, PermissionAuthorizationRequirement requirement)
    {
        var permissions = context.User.Claims.Where(claim => claim.Type == "Permission")
                                            .Select(claim => claim.Value)
                                            .ToList();

        if (permissions.Any(permission => permission.StartsWith(requirement.Name)))
        {
            context.Succeed(requirement);
        }

        return Task.CompletedTask;
    }
}