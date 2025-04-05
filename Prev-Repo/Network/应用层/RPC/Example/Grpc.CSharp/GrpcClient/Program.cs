using Grpc.Net.Client;
using GrpcGreeterClient;

const string applicationUrl = "http://localhost:5241";

using var channel = GrpcChannel.ForAddress(applicationUrl);
var client = new Greeter.GreeterClient(channel); 
var reply = await client.SayHelloAsync(new HelloRequest { Name = "GreeterClient" });

Console.WriteLine("Greeting: " + reply.Message);

