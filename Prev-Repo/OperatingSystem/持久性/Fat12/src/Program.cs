using Fat12;
using ConsoleTables;

#if DEBUG
Console.WriteLine($"Args: {string.Join(' ', args)}");
#endif

#region StartRegion
if (args.Length != 1) {
	Console.Write("Use: fsh ");
	Console.ForegroundColor = ConsoleColor.Red;
	Console.WriteLine("/dev/sda1");
	return -1;
}

var diskName = args[0];

if (!File.Exists(diskName)) {
	Console.ForegroundColor = ConsoleColor.Red;
	Console.WriteLine("Please check disk name is right. \n");
	return -1;
}
#endregion

// Load Disk
var disk = new DiskManager(diskName);

// Load Message
Console.ForegroundColor = ConsoleColor.Green;
Console.WriteLine($"Loaded Disk: {disk.DiskName}.");
Console.ResetColor();

#if DEBUG
for (int i = 0; i < 32; i++) {
	Console.Write($"{disk.Disk.FatList1.Data[i]:x2}");
}
Console.WriteLine();
for (int i = 0; i < 10; i++) {
	Console.WriteLine($"{disk.Disk.FatList1[i]:x3} {i * 3 / 2} {i * 3 / 2 + 1} {disk.Disk.FatList1.Data[i * 3 / 2]:x2} {disk.Disk.FatList1.Data[i * 3 / 2 + 1]:x2}");
}
Console.WriteLine();
#endif


// 当前文件夹
var shellFolder          = disk.GetRootDirectoryFolderList();
var shellDictionaryEntry = disk.Disk.RootDictionaryEntry;
// 当前路径
var shellPath   = new List<string>() { "~" };

// 命令列表
var comAction = new Dictionary<string, Action<List<string>, int>>();

#if DEBUG	

comAction.Add("Calc-FLB", (list, _) => {
	                          var n = int.Parse(list[1]);
	                          Console.WriteLine("First Logic Block: {0} Addr: {1}", n, disk.Disk.BPB.GetClusterStartBytePosition(n));
                          });

comAction
	.Add("DEBUG-RDE",
	     (_, _) => {
		     GetFileDictionaryPrintTable(disk.Disk.RootDictionaryEntry, EPrintTableMode.Debug).Write();
	     });

comAction
	.Add("DEBUG-AllFAT",
	     (_, _) => {
		     for (int i = 0; i < disk.Disk.FatList1.Length; i++) {
			     var next = disk.Disk.FatList1[i];
			     Console.WriteLine($"[{i}] => 0x{next}");
		     }
	     });
comAction.Add("DEBUG-BPB", (_, _) => {
	                           Console.WriteLine(disk.Disk.BPB);
                           });
#endif


#region CommandActionRegion 
// in this position, add your action. ^_^
comAction
	.Add("show",
	     (ls, _) => {
		     if (ls.Count == 1) {
			     ColorPrintLine($"[Error] Support: BPB FAT1 FAT2 RDE RDE-ALL NOW-DE NOW-DE-ALL.", ConsoleColor.Red);
			     return;
		     }
		     if (ls.Count != 2) {
			     ColorPrintLine($"[Error] {string.Join(' ', ls)}.", ConsoleColor.Red);
			     return;
		     }

		     switch (ls[1]) {
			     case "BPB":
				     disk.Disk.BPB.GetPrintConsoleTable().Write();
				     break;
			     case "FAT1": {
				     ColorPrintLine("FAT1", ConsoleColor.DarkCyan);
				     disk.Disk.FatList1.ToStringList().ForEach(Console.WriteLine);
				     break;
			     }
			     case "FAT2": {
				     ColorPrintLine("FAT2", ConsoleColor.DarkCyan);
				     disk.Disk.FatList1.ToStringList().ForEach(Console.WriteLine);
				     break;
			     }
			     case "RDE":
				     GetFileDictionaryPrintTable(disk.Disk.RootDictionaryEntry).Write();
				     break;
			     case "RDE-ALL":
				     GetFileDictionaryPrintTable(disk.Disk.RootDictionaryEntry, EPrintTableMode.Debug).Write();
				     break;
			     case "NOW-DE":
				     GetFileDictionaryPrintTable(shellDictionaryEntry).Write();
				     break;
			     case "NOW-DE-ALL":
				     GetFileDictionaryPrintTable(shellDictionaryEntry, EPrintTableMode.Debug).Write();
				     break;
			     default:
				     ColorPrintLine($"[Error] {string.Join(' ', ls)}.", ConsoleColor.Red);
				     break;
		     }
	     });

comAction.Add("tldr",
              (ls, _) => {
	              if (ls.Count != 1) {
		              ColorPrintLine($"[Error] {ls[0]}.", ConsoleColor.Red);
		              return;
	              }

	              Console.WriteLine("Command support list: ");
	              comAction
		              .Select(x => x.Key)
		              .Order()
		              .ToList()
		              .ForEach(x => Console.WriteLine($"  --> {x}"));
              });

// 清屏
comAction.Add("clear",
              (ls, _)
	              => {
	              if (ls.Count != 1) {
		              ColorPrintLine($"[Error] {ls[0]}.", ConsoleColor.Red);
	              } else {
		              Console.Clear();
	              }
              });

// 查看当前目录
comAction
	.Add("ls",
	     (ls, _)
		     => {
		     switch (ls.Count) {
			     case > 2:
				     ColorPrintLine($"[Error] {string.Join(' ', ls)}.", ConsoleColor.Red);
				     return;
			     case 1: {
				     var itemList = shellFolder
					     .Select(x => (x.Item1.GetAttributeType(),
					                   x.Item1.IsDirectory()
						                   ? x.Item1.GetFileNameWithoutExtensionUtf8String()
						                   : x.Item1.GetFileNameWithoutExtensionUtf8String() + "." + x.Item1.GetExtensionUtf8String()))
					     .OrderBy(x => x.Item1)
					     .ToList();

				     for (var i = 0; i < itemList.Count(); i++) {
					     if (i > 0)
						     Console.Write(' ');
					     ColorPrint(itemList[i].Item2,
					                itemList[i].Item1 is FileControlBlockAttributeType.Directory
						                ? ConsoleColor.Green
						                : ConsoleColor.White);
				     }
				     Console.WriteLine();
				     break;
			     }
			     default: {
				     if (ls[1] == "-T") {
					     GetFileDictionaryList(shellFolder)
						     .ForEach(x => {
							              Console.ForegroundColor =
								              x.Item1 == FileControlBlockAttributeType.Directory
									              ? ConsoleColor.Cyan
									              : ConsoleColor.White;
							              Console.WriteLine(x.Item2);
						              });
					     Console.ResetColor();
				     } else {
					     ColorPrintLine($"[Error] {string.Join(' ', ls)}.", ConsoleColor.Red);
				     }

				     break;
			     }
		     }
	     });

// cd
comAction.Add("cd",
              (ls, _) => {
	              if (ls.Count != 2) {
		              ColorPrintLine($"[Error] {string.Join(' ', ls)}.", ConsoleColor.Red);
		              return;
	              }

	              var nextDirName = ls[1].ToUpper();
	              switch (nextDirName) {
		              case ".":
			              return;
		              case "..":
			              switch (shellPath.Count) {
				              case 1:
					              return;
				              case 2:
					              shellPath.RemoveBack();
					              disk.GetRootDirectoryFolderList(ref shellFolder);
					              shellDictionaryEntry = disk.Disk.RootDictionaryEntry;
					              return;
			              }

			              break;
	              }
	              
	              int? target = null;
	              foreach (var x in shellFolder) {
		              if (x.Item1.GetFileNameWithoutExtensionUtf8String() != nextDirName) {
			              continue;
		              }
		              target = x.Item1.FirstLogicalCluster;
		              break;
	              }

	              if (target == null) {
		              ColorPrintLine($"[Error] no such directory like {nextDirName}.", ConsoleColor.Red);
	              } else {
		              if (nextDirName == "..") {
						  shellPath.RemoveBack();
		              } else {
			              shellPath.Add(nextDirName);
		              }
		              shellDictionaryEntry = disk.ReloadFileDictionaryList((int)target, ref shellFolder);
	              }
              });

comAction.Add("bat",
              ((list, _) => {
	               if (list.Count != 3) {
		               // ColorPrintLine("");
		               ColorPrintLine($"[Error] {string.Join(' ', list)}.", ConsoleColor.Red);
		               return;
	               }

	               var tagCoding = list[2];
	               if (tagCoding != "utf-8" && tagCoding != "ascii") {
		               ColorPrintLine($"[Error] {tagCoding}.", ConsoleColor.Red);
		               return;
	               }
	               
	               var     tagFile  = list[1].ToUpper();
	               ushort? isItHas  = null;
	               uint?    fileSize = null;
	               foreach (var item in shellFolder) {
		               var attr = item.Item1.GetAttributeType();
		               if (attr is not FileControlBlockAttributeType.Regular)
			               continue;
		               var fileName = item.Item1.GetFileNameWithoutExtensionUtf8String() + "." + item.Item1.GetExtensionUtf8String();
		               if (tagFile != fileName) {
			               continue;
		               }
		               isItHas  = item.Item1.FirstLogicalCluster;
		               fileSize = item.Item1.FileSize;
		               break;
	               }

	               if (isItHas == null 
	                   || FileAllocationTableItem
		                   .GetFileAllocationTableItemState(isItHas.Value)
		                   .IsUsed() == false ) {
		               ColorPrintLine($"[Error] no such file like {tagFile}.", ConsoleColor.Red);
		               return;
	               }

	               var itemList
		               = new List<FileAllocationTableItem>(30)
		                 { FileAllocationTableItem.GetFileAllocationTableItem(isItHas.Value) };
	               while (itemList.Last().GetFileAllocationTableItemState().IsFileEnd() == false) {
		               var next     = itemList.Last().GetNextItemIndex();
		               var nextItem = disk.Disk.FatList1[next];
		               itemList.Add(nextItem);
		               if (nextItem.IsUsed() == false) {
			               throw new
				               FatListException($"Is the disk is broken? Item list: {string.Join(' ', itemList)}");
		               }
	               }

	               var fileBytes = new List<byte>((int)fileSize!.Value);
	               foreach (var item in itemList) {
		               if (item.IsFileEnd()) {
			               break;
		               }
		               var next      = item.GetNextItemIndex();
		               var itemBytes = disk.ReadClusterBytes(next);
		               foreach (var @byte in itemBytes) {
			               if (fileBytes.Count == fileSize) {
				               break;
			               }
			               fileBytes.Add(@byte);
		               }

		               if (fileBytes.Count == fileSize) {
			               break;
		               }
	               }
	               
	               var output = tagCoding == "utf-8"
		                        ? System.Text.Encoding.UTF8.GetString(fileBytes.ToArray())
		                        : System.Text.Encoding.ASCII.GetString(fileBytes.ToArray());
	               
	               Console.WriteLine(output);
               }));
#endregion

#if DEBUG

comAction
	.Select(x => x.Key)
	.ToList()
	.ForEach(x => comAction[x] += (list, _) => {
		                              Console.WriteLine($"Call Command: {x}; Command list: {string.Join(' ', list)}");
	                              });

#endif

#region ShellDeathLoopRegion
// Death Loop
while (true) {
	ColorPrint("[Cirno] ", ConsoleColor.DarkGreen);
	
	if (shellPath.Count > 1) {
		ColorPrint(string.Join('/', shellPath.SkipLast(1)) + "/", ConsoleColor.DarkGray);
	}
	ColorPrint(shellPath.Last(), ConsoleColor.Cyan);
	ColorPrint(" => ", ConsoleColor.Green);
	
	var line = Console.ReadLine() ?? "";
	var com  = line.Split().Where(x => x != "").ToList();
	
	if (!com.Any()) {
		continue;
	}

	if (com[0] == "exit") {
		Console.WriteLine("[Console] exit. ");
		break;
	}

	if (comAction.TryGetValue(com[0], out var action)) {
		action(com, 1);
	} else {
		Console.ForegroundColor = ConsoleColor.Yellow;
		Console.Write("[Error] ");
		Console.ForegroundColor = ConsoleColor.Red;
		Console.WriteLine($": command not found: {line}");
		Console.ResetColor();
	}
}
#endregion

return 0;

#region SupportRegion

// Print Like a Tree
void DfsGetFileDictionaryList(
	in List<(FileControlBlock, int)> rootList, 
	in int spaceCnt, 
	ref List<(FileControlBlockAttributeType, string)> output
	) 
{
	if (rootList == null) 
		throw new ArgumentNullException(nameof(rootList));
	
	foreach (var x in rootList) {
		var attr = x.Item1.GetAttributeType();

		switch (attr) {
			case FileControlBlockAttributeType.Directory when x.Item1.GetFileNameWithoutExtensionUtf8String() is ".." or ".":
				continue;
			case FileControlBlockAttributeType.Directory: {
				output.Add((attr, $"{new string(' ', spaceCnt)}{x.Item1.GetFileNameWithoutExtensionUtf8String()}"));
				var nextList = disk!.GetFileDictionaryList(x.Item1.FirstLogicalCluster) 
				               ?? throw new ArgumentNullException($"disk!.GetFileDictionaryList(x.Item1.FirstLogicalCluster)");
				
				if (nextList == null) 
					throw new ArgumentNullException(nameof(nextList));
				
				DfsGetFileDictionaryList(nextList, spaceCnt + 4, ref output);
				break;
			}
			default:
				output
					.Add((attr, $"{new string(' ', spaceCnt)}{x.Item1.GetFileNameWithoutExtensionUtf8String()}.{x.Item1.GetExtensionUtf8String()}"));
				break;
		}
	}		
}

List<(FileControlBlockAttributeType, string)> GetFileDictionaryList(in List<(FileControlBlock, int)> rootList) {
	if (rootList == null) 
		throw new ArgumentNullException(nameof(rootList));
	
	List<(FileControlBlockAttributeType, string)> ls = new();
	DfsGetFileDictionaryList(rootList, 1, ref ls);
	
	return ls;
}

void ColorPrint(in string output, in ConsoleColor color) {
	Console.ForegroundColor = color;
	Console.Write(output);
	Console.ResetColor();
}

void ColorPrintLine(in string output, in ConsoleColor color) {
	Console.ForegroundColor = color;
	Console.WriteLine(output);
	Console.ResetColor();
}

ConsoleTable GetFileDictionaryPrintTable(in DictionaryForFileControlBlockByte dictionaryList, in EPrintTableMode mode = EPrintTableMode.Release) {
	if (dictionaryList == null) 
		throw new ArgumentNullException(nameof(dictionaryList));

	var consoleTables = new ConsoleTable(new ConsoleTableOptions {
		                                                             Columns = new[] {
			                                                                       "File Name", "Extenders",
			                                                                       "Attribution", "Size",
			                                                                       "Last Write Date",
			                                                                       "Last Write Time",
			                                                                       "First Logic Cluster"
		                                                                       },
		                                                             NumberAlignment = Alignment.Right
	                                                             });

	for (int i = 0; i < dictionaryList.Length; i++) {
		var item = dictionaryList[i];
		if (mode is EPrintTableMode.Release) {
			if (item.IsEmptyFile())
				continue;
			if (item.IsEmptyFileWithLater())
				break;
		}
		consoleTables.AddRow(item.GetStrings().Select(x => x.Trim().TrimEnd()).Select(x => (object)x).ToArray());
	}

	return consoleTables;
}

/// <summary>
/// 扩展方法
/// </summary>
public static class IsNeededExtensions {
	public static void RemoveBack<T>(this List<T> self) {
		if (self == null) 
			throw new ArgumentNullException(nameof(self));

		self.RemoveAt(self.Count - 1);
	}
}

public class FatListException : Exception {
	public FatListException() : base() {
		this.HResult = -2146233086;
	}

	public FatListException(string? message)
		: base(message) {
		this.HResult = -2146233086;
	}
}

/// <summary>
/// print
/// </summary>
public enum EPrintTableMode {
	Debug,
	Release
}

#endregion
