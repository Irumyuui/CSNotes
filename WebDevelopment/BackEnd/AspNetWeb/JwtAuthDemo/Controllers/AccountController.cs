using JwtAuthDemo.Utils;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace JwtAuthDemo.Controllers;

[ApiController]
[Route("api/[controller]/[action]")]
public class AccountController(ILogger<AccountController> logger, JwtHelper jwtHelper) : ControllerBase
{
    [HttpGet]
    public ActionResult<string> GetToken() => jwtHelper.CreateToken();

    [HttpGet]
    [Authorize]
    public ActionResult<string> GetAuthTest()
    {
        //logger.LogWarning($"{HttpContext?.User?.Identity?.Name ?? "null"}");
        return "Get auth!";
    }
}
