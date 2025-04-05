# 协程

> 我不知道为什么明明这个是协程，但是把这个东西归到 `thread` 类型中去。

对于 `lua` ，其中的 `thread` 是一个有栈的、非对称的协程。因为是有栈协程的实现，因此对于任意的 `function` 类型，都可以视作为一个协程。

```lua
local function foo()
    print("foo")
end

-- 创建一个协程
local coro_handle = coroutine.create(foo)
```

注意，这里没有启动协程，只是创建了一个协程。

如何启动？ `resume` 一下它就可以了。

```lua
-- 启动协程
coroutine.resume(coro_handle)  -- 输出 "foo"
```

要注意的是，`coroutine.resume` 是带有返回值的，因此这里可以承接一下返回值，第一个返回值是 `boolean` 类型的结果，标志协程是开始还是已经结束了。

```lua
local state = coroutine.resume(coro_handle)
print(state)   -- true or false
```

此时也可以使用 `coroutine.status` 来获取协程的状态，这将返回一个 `string`。

```lua
coroutine.status(coro_handle)  -- "dead" or "suspended" or "running"
```

在函数内部可以直接 `coroutine.yield` 来暂停当前协程，并切换到调用该协程的位置（可能是另外一个协程），也可以提供参数，这将作为返回值处理。

```lua
local foo = function()
    coroutine.yield(123);
    print("foo")
end

local coro = coroutine.create(foo)

local state, result =  coroutine.resume(coro)
print(state, result)  -- true 123
```

基本上 `lua` 协程最主要的挂起和恢复这俩操作就这样了，接下来是使用协程实现一个简单的生产者和消费者模型。

```lua
local function producer()
    for i = 0, 3 do
        print("send " .. i)
        coroutine.yield(i)
    end
    print("send end")
end

local function consumer(value)
    repeat
        print("receive " .. value)
        value = coroutine.yield()
    until (not value)
    print("receive end")
end

local producer_coro = coroutine.create(producer)
local consumer_coro = coroutine.create(consumer)

repeat
    local status, product_value = coroutine.resume(producer_coro)
    if not status then
        break
    end
    coroutine.resume(consumer_coro, product_value)
until false

print("done")
```

如果熟悉 `c++20` 中的 `std::generator` 的话，那么可以发现，其实这个 `yield` 还可以充当迭代器的作用，或者说是一个类似于 `rust` 中的 `next` 这个函数。

比如下面，就是可以借助返回一个函数的方式，包装一下，变成迭代器。

```lua
local function permgen(a, n)
    n = n or #a
    if n <= 1 then
        coroutine.yield(a)
    else
        for i = 1, n do
            a[n], a[i] = a[i], a[n]
            permgen(a, n - 1)
            a[n], a[i] = a[i], a[n]
        end
    end
end

local function permutations(a)
    local coro = coroutine.create(function ()
        permgen(a)
    end)
    return function()
        local code, result = coroutine.resume(coro)
        return result
    end
end

for p in permutations{1, 2, 3} do
    print(table.concat(p, ", "))
end
```