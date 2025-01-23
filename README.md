# Project Spark

```kotlin
// mnlang
// keywords: for, while, if, else, fun, type, mut, yield, when, init, this, object
// useCases: games, math, automation, network



type Node {
    value = Int()
    mut next = Maybe[Node]

    init(this.value){
        next = Unit()
    }
    init(this.value, this.next)
}

object List {
    fun last(list) = Node(node){
        mut node = list
        while node is Node and node.network is Node {
            node = node.next
        }
    }

    fun add(mut list, value) {
        last = last(node)
        target = is last {
            Node -> last.next
            null -> last
        }
        set(target, value)
    }
}

object math {
    fun abs(x) = Double{
        if x < 0 {
            -x
        } else {
            x
        }
    }
}

fun sum(x, y) = x > y ? x + y : x - y

// {x != 0 and x is Int}
fun f(x) = 1/x

// f(a,b) = a + bl

// f(3,2)
// f("sd", "card")


// object foo {

// }

mut name = String("Rene")

fun swap(x,y) = Double,Double {
    y,x
}

fun zero(mut test) = set(test, 0)

fun getType(x) = String {
    if x is Int {
        "Integer"
    } else if x is String {
        "String"
    }
}

fun div(x, y) = Int (x / y) 

fun divide(x,y) = Int {}

fun call(callback, int) = Int {
    callback(int)
}

call({ $0 * 3 }, 10)

fun sum(begin, end) = Int(res) {
    mut res = 0
    for i = begin, end {
        set(res, res+i)
    }
}

fun count(start, end) = Int {
    for i = start, end {
        yield i
    }
}

when i = count(0,10) {
    print("counted $i")
}

type Person {
    name = String()
    age = Int()
    init(this.name, this.age) 
}

type Student = Person, Thing {
    fun toString() = String {
        this.name 
    }
}

type num = Int 

```