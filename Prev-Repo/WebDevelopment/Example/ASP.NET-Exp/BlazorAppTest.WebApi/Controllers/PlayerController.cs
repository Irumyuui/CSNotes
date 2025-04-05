using BlazorAppTest.Contracts;
using BlazorAppTest.Entites;
using BlazorAppTest.Entites.Dtos;
using BlazorAppTest.Entites.RequestFeatures;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;

namespace BlazorAppTest.WebApi.Controllers;

[Route("api/player")]
[ApiController]
public class PlayerController : ControllerBase
{
    private readonly IRepositoryWrapper _repository;

    private readonly AutoMapper.IMapper _mapper;

    private readonly ILogger<PlayerController> _logger;

    public PlayerController(IRepositoryWrapper repository, AutoMapper.IMapper mapper, ILogger<PlayerController> logger)
    {
        _repository = repository;
        _mapper = mapper;
        _logger = logger;
    }

    [HttpGet("all")]
    public async Task<IActionResult> GetAllPlayersAsync()
    {
        try {

            var players = await _repository.Player.GetPlayersAsync();
            var result = _mapper.Map<IEnumerable<PlayerDto>>(players);

            return Ok(result);

        } catch (Exception e) {
            _logger.LogError($"{e.Message}");
            return StatusCode(500);
        }
    }

    [HttpGet]
    public async Task<IActionResult> GetAllPlayersAsync([FromQuery] PlayerParameter parameter)
    {
        if (!parameter.ValidDateCreatedRange)
            return BadRequest("Begin date time is greater than end date time.");

        try {

            var players = await _repository.Player.GetPlayersAsync(parameter);

            Response.Headers.Append("X-Pagination", JsonConvert.SerializeObject(players.MetaData));

            var result = _mapper.Map<IEnumerable<PlayerDto>>(players);

            return Ok(result);

        } catch (Exception e) {
            _logger.LogError($"{e.Message}");
            return StatusCode(500);
        }
    }

    [HttpGet("{id}", Name = "PlayerById")]
    public async Task<IActionResult> GetPlayerByIdAsync(Guid id)
    {
        try {
            var player = await _repository.Player.GetPlayerByIdAsync(id);
            if (player is null)
                return NotFound();

            return Ok(_mapper.Map<PlayerDto>(player));

        } catch (Exception e) {
            _logger.LogError(e.Message);
            return StatusCode(500);
        }
    }

    [HttpGet("{id}/character")]
    public async Task<IActionResult> GetPlayerByIdWithcharacterAsync(Guid id)
    {
        try {
            var player = await _repository.Player.GetPlayerWithCharactersAsync(id);
            if (player is null)
                return NotFound();

            return Ok(_mapper.Map<PlayerWithCharactersDto>(player));

        } catch (Exception e) {
            _logger.LogError(e.Message);
            return StatusCode(500);
        }
    }

    [HttpPost]
    public async Task<IActionResult> CreatePlayerAsync([FromBody] PlayerForCreationDto? player)
    {
        try {

            if (!ModelState.IsValid || player is null)
                return BadRequest("Error for request data.");

            var playerEntiry = _mapper.Map<Player>(player);

            _repository.Player.Create(playerEntiry);
            await _repository.SaveAsync();

            var createdPlayer = _mapper.Map<PlayerDto>(playerEntiry);
            return CreatedAtRoute(
                    "PlayerById", new { id = createdPlayer.Id }, createdPlayer
                );

        } catch (Exception e) {
            _logger.LogError(e.Message);
            return StatusCode(500);
        }
    }

    [HttpPut("{id}")]
    public async Task<IActionResult> UpdatePlayerAsync(Guid id, [FromBody] PlayerForUpdateDto? player)
    {
        try {

            if (player is null)
                return BadRequest($"{nameof(Player)} is not valid");

            if (!ModelState.IsValid)
                return BadRequest("Error for request data.");

            var playerEntity = await _repository.Player.GetPlayerByIdAsync(id);
            if (playerEntity is null)
                return NotFound("Could not found target player");

            _mapper.Map(player, playerEntity);

            _repository.Player.Update(playerEntity);
            await _repository.SaveAsync();

            return NoContent();

        } catch (Exception e) {
            _logger.LogError(e.Message);
            return StatusCode(500);
        }
    }

    [HttpDelete("{id}")]
    public async Task<IActionResult> DeletePlayerAsync(Guid id)
    {
        try {

            var player = await _repository.Player.GetPlayerByIdAsync(id);

            if (player is null)
                return BadRequest($"{nameof(Player)} is not found");

            if (player.Characters.Count != 0)
                return BadRequest("Error to delete player");

            _repository.Player.Delete(player);
            await _repository.SaveAsync();

            return Ok();

        } catch (Exception e) {
            _logger.LogError(e.Message);
            return StatusCode(500);
        }
    }
}
