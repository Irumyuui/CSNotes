module fp =
    type Node<'T> =
        | Nil
        | Cons of 'T * Node<'T>

    let lsit = Cons(1, Cons(2, Cons(3, Nil)))

    let rec printList lst =
        match lst with
        | Nil -> ()
        | Cons(x, xs) ->
            printf "%d " x
            printList xs

    printList lsit
    printfn ""


module oop =
    type Node<'T>(value: 'T) =
        member val Value = value with get, set
        member val Next: Node<'T> option = None with get, set

    type ForwardList<'T>() =
        let mutable head: Node<'T> option = None

        member this.Add(value: 'T) =
            let newNode = Node value

            match head with
            | None -> head <- Some newNode
            | Some node ->
                let rec findLast (node: Node<'T>) =
                    match node.Next with
                    | None -> node
                    | Some nextNode -> findLast nextNode

                let lastNode = findLast node
                lastNode.Next <- Some newNode

        member this.Print() =
            let rec printNode (node: Node<'T>) =
                printf "%A " node.Value

                match node.Next with
                | None -> ()
                | Some nextNode -> printNode nextNode

            match head with
            | None -> printfn "Empty list"
            | Some node ->
                printNode node
                printfn ""

    let list = ForwardList<int>()
    list.Add(1)
    list.Add(2)
    list.Add(3)
    list.Print()
