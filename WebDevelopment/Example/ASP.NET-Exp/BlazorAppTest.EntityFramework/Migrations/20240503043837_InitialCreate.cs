using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace BlazorAppTest.EntityFramework.Migrations
{
    /// <inheritdoc />
    public partial class InitialCreate : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AlterDatabase()
                .Annotation("MySql:CharSet", "utf8mb4");

            migrationBuilder.CreateTable(
                name: "Players",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "char(36)", nullable: false, collation: "ascii_general_ci"),
                    Account = table.Column<string>(type: "varchar(50)", maxLength: 50, nullable: false)
                        .Annotation("MySql:CharSet", "utf8mb4"),
                    AccountType = table.Column<string>(type: "varchar(10)", maxLength: 10, nullable: false)
                        .Annotation("MySql:CharSet", "utf8mb4"),
                    DateCreated = table.Column<DateTime>(type: "datetime(6)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Players", x => x.Id);
                })
                .Annotation("MySql:CharSet", "utf8mb4");

            migrationBuilder.CreateTable(
                name: "Characters",
                columns: table => new
                {
                    Id = table.Column<Guid>(type: "char(36)", nullable: false, collation: "ascii_general_ci"),
                    NickName = table.Column<string>(type: "varchar(20)", maxLength: 20, nullable: false)
                        .Annotation("MySql:CharSet", "utf8mb4"),
                    Classes = table.Column<string>(type: "varchar(20)", maxLength: 20, nullable: false)
                        .Annotation("MySql:CharSet", "utf8mb4"),
                    Level = table.Column<int>(type: "int", nullable: false),
                    DateCreated = table.Column<DateTime>(type: "datetime(6)", nullable: false),
                    PlayerId = table.Column<Guid>(type: "char(36)", nullable: false, collation: "ascii_general_ci")
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Characters", x => x.Id);
                    table.ForeignKey(
                        name: "FK_Characters_Players_PlayerId",
                        column: x => x.PlayerId,
                        principalTable: "Players",
                        principalColumn: "Id",
                        onDelete: ReferentialAction.Cascade);
                })
                .Annotation("MySql:CharSet", "utf8mb4");

            migrationBuilder.InsertData(
                table: "Players",
                columns: new[] { "Id", "Account", "AccountType", "DateCreated" },
                values: new object[,]
                {
                    { new Guid("190a9b07-fe75-4c33-94e8-060c0c314b7e"), "1", "Free", new DateTime(2024, 5, 3, 12, 38, 36, 375, DateTimeKind.Local).AddTicks(8954) },
                    { new Guid("24ead4b9-ceac-41c4-adae-f783e882670b"), "2", "DeFree", new DateTime(2024, 5, 3, 12, 38, 36, 375, DateTimeKind.Local).AddTicks(9129) }
                });

            migrationBuilder.InsertData(
                table: "Characters",
                columns: new[] { "Id", "Classes", "DateCreated", "Level", "NickName", "PlayerId" },
                values: new object[,]
                {
                    { new Guid("2ba6cf0c-57ba-4a4f-854a-6560e49e8a36"), "CC", new DateTime(2024, 5, 3, 12, 38, 36, 376, DateTimeKind.Local).AddTicks(346), 3, "C", new Guid("24ead4b9-ceac-41c4-adae-f783e882670b") },
                    { new Guid("56326a91-1aa7-4c9e-8f97-1aaffb588017"), "BB", new DateTime(2024, 5, 3, 12, 38, 36, 376, DateTimeKind.Local).AddTicks(330), 2, "B", new Guid("190a9b07-fe75-4c33-94e8-060c0c314b7e") },
                    { new Guid("594e6962-c855-488b-906e-c54e0b469153"), "AA", new DateTime(2024, 5, 3, 12, 38, 36, 376, DateTimeKind.Local).AddTicks(186), 1, "A", new Guid("190a9b07-fe75-4c33-94e8-060c0c314b7e") },
                    { new Guid("7f3fb197-efa8-4797-bda0-91e1845a4988"), "DD", new DateTime(2024, 5, 3, 12, 38, 36, 376, DateTimeKind.Local).AddTicks(348), 4, "D", new Guid("24ead4b9-ceac-41c4-adae-f783e882670b") }
                });

            migrationBuilder.CreateIndex(
                name: "IX_Characters_NickName",
                table: "Characters",
                column: "NickName",
                unique: true);

            migrationBuilder.CreateIndex(
                name: "IX_Characters_PlayerId",
                table: "Characters",
                column: "PlayerId");

            migrationBuilder.CreateIndex(
                name: "IX_Players_Account",
                table: "Players",
                column: "Account",
                unique: true);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Characters");

            migrationBuilder.DropTable(
                name: "Players");
        }
    }
}
