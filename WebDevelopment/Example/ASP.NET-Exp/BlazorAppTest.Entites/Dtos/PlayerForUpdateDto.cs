using System.ComponentModel;
using System.ComponentModel.DataAnnotations;

namespace BlazorAppTest.Entites.Dtos;

public class PlayerForUpdateDto
{
    [Description("账号")]
    [Required(ErrorMessage = "{0}不能为空")]
    [StringLength(20, ErrorMessage = "{0}长度不能大于50")]
    public string? Account { get; set; }

    [Description("账号类型")]
    [Required(ErrorMessage = "{0}不能为空")]
    [StringLength(10, ErrorMessage = "{0}长度不能大于10")]
    public string? AccountType { get; set; }
}