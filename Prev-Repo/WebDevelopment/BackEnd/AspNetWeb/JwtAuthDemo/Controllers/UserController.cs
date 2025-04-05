using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace JwtAuthDemo.Controllers
{
    [ApiController]
    [Route("api/[controller]/[action]")]
    public class UserController : ControllerBase
    {
        [HttpGet]
        [Authorize(Permissions.UserCreate)]
        public ActionResult<string> UserCreate() => "UserCreate";

        [HttpGet]
        [Authorize(Permissions.UserUpdate)]
        public ActionResult<string> UserUpdate() => "UserUpdate";

        [HttpGet]
        [Authorize(Permissions.UserDelete)]
        public ActionResult<string> UserDelete() => "UserDelete";
    }
}
