﻿using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Authorization;
using Microsoft.Extensions.Options;

namespace JwtAuthDemo;

public class TestAuthorizationPolicyProvider(IOptions<AuthorizationOptions> options) : DefaultAuthorizationPolicyProvider(options), IAuthorizationPolicyProvider
{
    public new Task<AuthorizationPolicy> GetDefaultPolicyAsync()
        => base.GetDefaultPolicyAsync();

    public new Task<AuthorizationPolicy?> GetFallbackPolicyAsync()
        => base.GetFallbackPolicyAsync();

    public new Task<AuthorizationPolicy?> GetPolicyAsync(string policyName)
    {
        if (policyName.StartsWith(Permissions.User))
        {
            var policy = new AuthorizationPolicyBuilder(JwtBearerDefaults.AuthenticationScheme);
            policy.AddRequirements(new PermissionAuthorizationRequirement(policyName));
            return Task.FromResult<AuthorizationPolicy?>(policy.Build());
        }
        return base.GetPolicyAsync(policyName);
    }
}
