# JSON Web Tokens (JWT)

目前最流行的跨域认证方案为 JSON Web Tokens (JWT)，在 HTTP 请求中，头部添加一个 `Authorization` 字段，值为 `Bearer` 加上 JWT 字符串，即可作为凭据。

```http
GET /api/data
Authorization: Bearer {这里是 jwt}
```

## JWT 过程

JWT 作为认证方式，就是服务器在认证用户信息之后，根据用户信息生成一个 JSON 对象，大概长这样。

```json
{
    "Name": "Cirno",
    "Role": "Baka",
    "ExpriedTime": "114514",
    "xxx": "xxx",
    ...
}
```

服务器把这个 JSON 对象加密一下，然后发给客户端，客户端处理需要进行身份验证操作的时候就像刚刚那样子，把 JWT 字符串加到 `Authorization` 字段中，发送给服务器，服务器只需要验证这串 JWT 是否有效即可，不需要暂存什么状态了，然后这样就可以处理身份验证了。

> 但是这样带来一个问题：token 随便请求就可以了，那么服务器怎么知道这个 token 是在哪里的呢？随便带上就又可以了，那么这样的 token 还是得在 server 端存储，回到 session 的路子上了。

## 服务端生成 JWT

当然这只是一个示例，具体的话得传入用户信息来动态生成。

```csharp
using Microsoft.IdentityModel.Tokens;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;

namespace JwtAuthDemo.Utils;

public class JwtHelper(IConfiguration configuration)
{
    public string CreateToken()
    {
        // 1. 定义需要使用到的Claims
        var claims = new[]
        {
            new Claim(ClaimTypes.Name, "u_admin"), //HttpContext.User.Identity.Name
            new Claim(ClaimTypes.Role, "r_admin"), //HttpContext.User.IsInRole("r_admin")
            new Claim(JwtRegisteredClaimNames.Jti, "admin"),
            new Claim("Username", "Admin"),
            new Claim("Name", "超级管理员")
        };

        // 2. 从 appsettings.json 中读取SecretKey
        var secretKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(configuration["Jwt:SecretKey"] ?? throw new ArgumentException("Jwt:SecretKey is null")));

        // 3. 选择加密算法
        var algorithm = SecurityAlgorithms.HmacSha256;

        // 4. 生成Credentials
        var signingCredentials = new SigningCredentials(secretKey, algorithm);

        // 5. 根据以上，生成token
        var jwtSecurityToken = new JwtSecurityToken(
            configuration["Jwt:Issuer"],     //Issuer
            configuration["Jwt:Audience"],   //Audience
            claims,                          //Claims,
            DateTime.Now,                    //notBefore
            DateTime.Now.AddSeconds(30),    //expires
            signingCredentials               //Credentials
        );

        // 6. 将token变为string
        var token = new JwtSecurityTokenHandler().WriteToken(jwtSecurityToken);

        return token;
    }
}
```

### 客户端保存 JWT

客户端保存可以很多种方式，可以是直接存在 Cookie 里面，那么就能自动发送了，问题是无法跨域。

当然客户端也可以选择存储在 localStorage 里面，这是可以的，只需要请求的时候带上这个 token 就可以了。
